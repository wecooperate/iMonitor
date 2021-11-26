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
#include "MSGProcessManager.h"
//******************************************************************************
cxMSGProcessManager::cxMSGProcessManager(void)
{
	for (auto& it : cxProcessInternalEnumerator()) {
		if (it->UniqueProcessId == 0)
			continue;

		m_Processes.insert(std::make_pair((ULONG)it->UniqueProcessId, std::make_unique<cxMSGProcess>(&it)));
	}
}
//******************************************************************************
cxMSGProcess* cxMSGProcessManager::GetProcess(ULONG ProcessId, ULONGLONG Time)
{
	AUTO_LOCK(m_Lock);

	cxMSGProcess* process = NULL;

	for (auto it = m_Processes.lower_bound(ProcessId); it != m_Processes.upper_bound(ProcessId); ++it) {
		process = it->second.get();

		if (Time > 0 && process->m_CreateTime > Time)
			continue;

		if (process->m_ExitTime != 0 && process->m_ExitTime < Time)
			continue;

		break;
	}

	if (!process)
		return CreateProcess(ProcessId);

	return process;
}
//******************************************************************************
void cxMSGProcessManager::OnProcessCreate(cxMSG* msg)
{
	AUTO_LOCK(m_Lock);

	cxMSGProcess* process = CreateProcess(msg->m_Data[proto::ProcessCreate::emFieldProcessId]);

	process->FixInformation(
		msg->m_Time,
		msg->m_CurrentProcessId,
		g_MSGData->GetString(msg->m_Data[proto::ProcessCreate::emFieldPath]).Data,
		g_MSGData->GetString(msg->m_Data[proto::ProcessCreate::emFieldCommandline]).Data);
}
//******************************************************************************
void cxMSGProcessManager::OnProcessExit(cxMSG* msg)
{
	AUTO_LOCK(m_Lock);

	cxMSGProcess* process = NULL;

	for (auto it = m_Processes.lower_bound(msg->m_CurrentProcessId); it != m_Processes.upper_bound(msg->m_CurrentProcessId); ++it) {
		process = it->second.get();

		if (process->m_ExitTime != 0)
			continue;

		process->m_ExitTime = msg->m_Time;

		break;
	}
}
//******************************************************************************
void cxMSGProcessManager::OnLoadModule(cxMSG* msg)
{
	cxMSGProcessModule module;
	module.m_LoadTime = msg->m_Time;
	module.m_Path = g_MSGData->GetString(msg->m_Data[proto::ImageLoad::emFieldPath]).Data;
	module.m_Name = PathFindFileName(module.m_Path);
	module.m_BaseAddress = msg->m_Data[proto::ImageLoad::emFieldImageBase];
	module.m_Size = msg->m_Data[proto::ImageLoad::emFieldImageSize];

	AUTO_LOCK(m_Lock);
	cxMSGProcess* process = GetProcess(msg->m_CurrentProcessId, msg->m_Time);
	process->InsertModule(std::move(module));
}
//******************************************************************************
cxMSGProcess* cxMSGProcessManager::CreateProcess(ULONG ProcessId)
{
	auto process = std::make_unique<cxMSGProcess>(ProcessId);
	auto process_ptr = process.get();

	m_Processes.insert(std::make_pair(process->m_ProcessId, std::move(process)));

	return process_ptr;
}
//******************************************************************************
