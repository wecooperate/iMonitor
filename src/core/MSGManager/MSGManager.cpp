//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "MSGManager.h"
#include "MSGConfig.h"
#include "RuleManager/SimpleRule.h"
//******************************************************************************
cxMSGManager::~cxMSGManager(void)
{
	Stop();
}
//******************************************************************************
HRESULT cxMSGManager::Start(void)
{
	g_RuleManager->RegisterDelegate(this);

	m_Looper = g_Looper->CreateLooper(ILooper::kUILooper, "MSG");

	m_UpdateTimerId = m_Looper->SetTimer(
		[this]() {
			UpdateMSGCount();
		},
		GetNextUpdateTime());

	return m_Monitor.InternalStart(this);
}
//******************************************************************************
void cxMSGManager::Stop(void)
{
	m_Monitor.Stop();

	if (m_Looper) {
		m_Looper->Cancel(m_UpdateTimerId);
		g_RuleManager->UnregisterDelegate(this);
	}

	m_Looper.reset();

	RemoveAll();
}
//******************************************************************************
void cxMSGManager::OnCallback(cxMSGHeader* Header, cxMSGAction* Action)
{
	cxMSG msg(Header);

	OnPreMSG(&msg);

	// 	auto msg = new cxMSG(Header);
	//
	// 	m_Looper->PostRunnable([this, msg]() {
	// 		OnPreMSG(msg);
	// 		delete msg;
	// 	});
}
//******************************************************************************
void cxMSGManager::OnPreMSG(cxMSG* msg)
{
	switch (msg->m_Type) {
	case emMSGProcessCreate:
		g_MSGProcessManager->OnProcessCreate(msg);
		break;

	case emMSGProcessExit:
		g_MSGProcessManager->OnProcessExit(msg);
		break;

	case emMSGImageLoad:
		g_MSGProcessManager->OnLoadModule(msg);
		break;
	}

	InsertMSG(msg);

	//
	// Insert ProcessStart + ThreadStart
	//

	if (msg->m_Type == emMSGProcessCreate) {
		msg->m_Type = emMSGProcessStart;
		msg->m_CurrentProcessId = msg->m_Data[proto::ProcessCreate::emFieldProcessId];
		msg->m_CurrentThreadId = 0;
		cxMSGProcess* process = msg->GetProcess();
		msg->m_Data[emMSGFieldCurrentProcessName] = g_MSGData->InsertString(process->m_ProcessName);
		msg->m_Data[emMSGFieldCurrentProcessPath] = g_MSGData->InsertString(process->m_ProcessPath);
		msg->m_Data[emMSGFieldCurrentProcessCommandline] = g_MSGData->InsertString(process->m_Commandline);
		InsertMSG(msg);
	} else if (msg->m_Type == emMSGThreadCreate) {
		msg->m_Type = emMSGThreadStart;
		msg->m_CurrentProcessId = msg->m_Data[proto::ThreadCreate::emFieldProcessId];
		msg->m_CurrentThreadId = msg->m_Data[proto::ThreadCreate::emFieldThreadId];
		cxMSGProcess* process = msg->GetProcess();
		msg->m_Data[emMSGFieldCurrentProcessName] = g_MSGData->InsertString(process->m_ProcessName);
		msg->m_Data[emMSGFieldCurrentProcessPath] = g_MSGData->InsertString(process->m_ProcessPath);
		msg->m_Data[emMSGFieldCurrentProcessCommandline] = g_MSGData->InsertString(process->m_Commandline);
		InsertMSG(msg);
	}
}
//******************************************************************************
void cxMSGManager::InsertMSG(cxMSG* msg)
{
	AUTO_LOCK(m_Lock);

	if (g_MSGConfig->m_IsUniqueMessage) {
		for (ULONG i = 0; i < m_MSGs.GetCount(); i++) {
			if (msg->m_Type == m_MSGs.Get(i)->m_Type)
				return;
		}
	}

	cxMSG* cur_msg = m_MSGs.Alloc();

	if (!cur_msg)
		return;

	*cur_msg = *msg;

	if (m_SeqIndex == -1)
		m_SeqIndex = 0;

	cur_msg->m_SeqId = ++m_SeqIndex;

	if (IsIncluded(cur_msg)) {
		PULONG index = m_IncludedMSGs.Alloc();

		if (!index)
			return;

		cur_msg->m_Index = *index = m_MSGs.GetCount() - 1;
	}
}
//******************************************************************************
void cxMSGManager::UpdateMSGCount(bool Reset)
{
	OnMSGCountUpdate(Reset, m_IncludedMSGs.GetCount());

	if (!m_Looper)
		return;

	auto next_time = GetNextUpdateTime();

	if (next_time != m_UpdateInterval) {
		m_UpdateInterval = next_time;
		m_Looper->ResetTimer(m_UpdateTimerId, next_time);
	}
}
//******************************************************************************
ULONG cxMSGManager::GetNextUpdateTime(void)
{
	auto count = m_IncludedMSGs.GetCount();

	if (count > 100 * 10000)
		return emMinUpdateInterval * 4;

	if (count > 10 * 10000)
		return emMinUpdateInterval * 3;

	if (count > 10000)
		return emMinUpdateInterval * 2;

	return emMinUpdateInterval;
}
//******************************************************************************
cxMSG* cxMSGManager::GetMSG(int Index) const
{
	PULONG index = m_IncludedMSGs.Get(Index);

	if (!index)
		return NULL;

	return m_MSGs.Get(*index);
}
//******************************************************************************
void cxMSGManager::StartCapture(void)
{
	cxMSGUserSetMSGConfig config;

	for (const auto& it : g_MSGConfig->GetConfigItems()) {
		if (!it.Enable)
			continue;

		config.Config[it.Type] = emMSGConfigPost | emMSGConfigIncludeKernelEvent;
		config.Fields[it.Type] = ~(
			BIT(emMSGFieldCurrentProcessCreateTime) |
			BIT(emMSGFieldCurrentProcessPath) |
			BIT(emMSGFieldCurrentProcessCommandline));
	}

	m_Monitor.InControl(config);
}
//******************************************************************************
void cxMSGManager::StopCapture(void)
{
	cxMSGUserSetMSGConfig config;

	for (const auto& it : g_MSGConfig->GetConfigItems()) {
		config.Config[it.Type] = 0;
	}

	m_Monitor.InControl(config);
}
//******************************************************************************
bool cxMSGManager::IsIncluded(cxMSG* msg)
{
	return g_RuleManager->IsEnable(msg);
}
//******************************************************************************
ULONG cxMSGManager::GetIncludedCount(void)
{
	return m_IncludedMSGs.GetCount();
}
//******************************************************************************
ULONG cxMSGManager::GetTotalCount(void)
{
	return m_MSGs.GetCount();
}
//******************************************************************************
void cxMSGManager::RemoveAll(void)
{
	AUTO_LOCK(m_Lock);

	m_IncludedMSGs.RemoveAll();
	m_MSGs.RemoveAll();

	m_SeqIndex = -1;

	UpdateMSGCount(true);
}
//******************************************************************************
void cxMSGManager::OnRuleChanged(bool Increase)
{
	m_Looper->PostRunnable([this]() {
		AUTO_LOCK(m_Lock);
		m_IncludedMSGs.ResetCount();

		m_RuleApplyIndex = 0;
		OnRuleBeginApply();

		for (ULONG i = 0; i < m_MSGs.GetCount(); i++) {
			m_RuleApplyIndex = i;

			cxMSG* msg = m_MSGs.Get(i);

			if (IsIncluded(msg)) {
				PULONG index = m_IncludedMSGs.Alloc();

				if (!index)
					break;

				msg->m_Index = *index = i;
			}
		}

		UpdateMSGCount(true);

		OnRuleFinishApply();
	});
}
//******************************************************************************
