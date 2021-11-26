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
#include "UIMessageService.h"
#include "UI/UIManager.h"
//******************************************************************************
void UIMessageService::Initialize(void)
{
	m_StartResult = cxMSGManager::Start();

	m_ColumnManager.Initialize(GetVisionService());
}
//******************************************************************************
void UIMessageService::Uninitialize(void)
{
	UIServiceImpl::Uninitialize();

	cxMSGManager::Stop();
}
//******************************************************************************
void UIMessageService::StartCapture(void)
{
	if (m_StartResult != S_OK) {
		m_StartResult = cxMSGManager::Start();

		if (m_StartResult != S_OK) {
			FireEvent(ServiceEventError(m_StartResult, "LoadDriver Failed"));
		}
	}

	cxMSGManager::StartCapture();
}
//******************************************************************************
void UIMessageService::StopCapture(void)
{
	cxMSGManager::StopCapture();
}
//******************************************************************************
IMessage* UIMessageService::GetItem(int index)
{
	if (index < 0)
		return nullptr;

	return GetMSG(index);
}
//******************************************************************************
void UIMessageService::RemoveAllItems(void)
{
	cxMSGManager::RemoveAll();
}
//******************************************************************************
int UIMessageService::GetTotalCount(void)
{
	return cxMSGManager::GetTotalCount();
}
//******************************************************************************
int UIMessageService::GetRuleApplyIndex(void)
{
	return m_RuleApplyIndex;
}
//******************************************************************************
int UIMessageService::InsertColumn(std::shared_ptr<IMessageColumn> column)
{
	return m_ColumnManager.Insert(column);
}
//******************************************************************************
void UIMessageService::RemoteColumn(std::shared_ptr<IMessageColumn> column)
{
	m_ColumnManager.Remove(column);
}
//******************************************************************************
std::shared_ptr<IMessageColumn> UIMessageService::GetColumn(int index)
{
	if (index < 0)
		return nullptr;

	return m_ColumnManager.GetColumn(index);
}
//******************************************************************************
int UIMessageService::GetColumnCount(void)
{
	return m_ColumnManager.GetColumnCount();
}
//******************************************************************************
int UIMessageService::GetColumnMaxCount(void)
{
	return m_ColumnManager.GetMaxColumnCount();
}
//******************************************************************************
void UIMessageService::OnMSGCountUpdate(bool Reset, ULONG Count)
{
	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
		return;

	g_MainLooper->PostRunnable([this, Reset, Count]() {
		ServiceEventMSGUpdate event;
		event.Reset = Reset;
		event.Count = Count;
		event.TotalCount = GetTotalCount();
		FireEvent(event);
	});
}
//******************************************************************************
void UIMessageService::OnRuleBeginApply()
{
	g_MainLooper->PostRunnable([this]() {
		FireEvent(emServiceEventRuleBeginApply);
	});
}
//******************************************************************************
void UIMessageService::OnRuleFinishApply()
{
	g_MainLooper->PostRunnable([this]() {
		FireEvent(emServiceEventRuleFinishApply);
	});
}
//******************************************************************************
