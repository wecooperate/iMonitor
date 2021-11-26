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
#include "UIMessageColumnManager.h"
//******************************************************************************
void UIMessageColumnManager::Initialize(IVisionService* service)
{
	m_VisionService = service;

	Insert("NO.", emMSGFieldSeqId, 60, Qt::AlignRight);
	Insert("Time", emMSGFieldTime, 150);
	Insert("ProcessName", emMSGFieldCurrentProcessName, 160);
	Insert("PID", emMSGFieldCurrentProcessId, 50, Qt::AlignRight);
	Insert("TID", emMSGFieldCurrentThreadId, 50, Qt::AlignRight);
	Insert("Operation", emMSGFieldType, 150);
	Insert("Path", emMSGFieldPath, 600);
	Insert("Result", emMSGFieldStatus, 150);
	Insert("Detail", emMSGFieldDetail, 600);
}
//******************************************************************************
std::shared_ptr<IMessageColumn> UIMessageColumnManager::GetColumn(int index)
{
	return m_VisibleColumns[index];
}
//******************************************************************************
int UIMessageColumnManager::GetColumnCount(void)
{
	return m_VisibleColumns.size();
}
//******************************************************************************
int UIMessageColumnManager::GetMaxColumnCount(void)
{
	return m_Columns.size();
}
//******************************************************************************
int UIMessageColumnManager::Insert(const QString& name, int field_index, int width, int align)
{
	auto column = std::make_shared<UIMessageColumn>(name, field_index, width, align);

	column->SetVisionService(m_VisionService);

	m_Columns.push_back(column);

	if (column->IsVisible())
		m_VisibleColumns.push_back(column);

	return m_Columns.size();
}
//******************************************************************************
int UIMessageColumnManager::Insert(std::shared_ptr<IMessageColumn> column)
{
	m_Columns.push_back(column);

	if (column->IsVisible())
		m_VisibleColumns.push_back(column);

	return m_Columns.size();
}
//******************************************************************************
void UIMessageColumnManager::Remove(std::shared_ptr<IMessageColumn> column)
{
	for (auto it = m_Columns.begin(); it != m_Columns.end(); ++it) {
		if (it->get() == column.get()) {
			m_Columns.erase(it);
			break;
		}
	}

	for (auto it = m_VisibleColumns.begin(); it != m_VisibleColumns.end(); ++it) {
		if (it->get() == column.get()) {
			m_VisibleColumns.erase(it);
			break;
		}
	}
}
//******************************************************************************
