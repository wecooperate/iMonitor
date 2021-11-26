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
#include "UIMessageColumn.h"
//******************************************************************************
UIMessageColumn::UIMessageColumn(const QString& name, int field_index, int width, int align)
{
	m_Name = name;
	m_FieldIndex = field_index;
	m_Width = width;
	m_Align = align;
	m_Visible = true;
}
//******************************************************************************
void UIMessageColumn::SetVisionService(IVisionService* service)
{
	m_VisionService = service;
}
//******************************************************************************
void UIMessageColumn::SetVisible(bool enable)
{
	m_Visible = enable;
}
//******************************************************************************
QString UIMessageColumn::GetName(void)
{
	return m_Name;
}
//******************************************************************************
int UIMessageColumn::GetWidth(void)
{
	return m_Width;
}
//******************************************************************************
int UIMessageColumn::GetAlign(void)
{
	return m_Align;
}
//******************************************************************************
bool UIMessageColumn::IsVisible(void)
{
	return m_Visible;
}
//******************************************************************************
QString UIMessageColumn::GetString(IMessage* msg)
{
	return QStringFrom(msg->GetString(GetFieldIndex(msg)));
}
//******************************************************************************
QColor UIMessageColumn::GetColor(IMessage* msg)
{
	return m_VisionService->GetColor(msg, GetFieldIndex(msg));
}
//******************************************************************************
QColor UIMessageColumn::GetTextColor(IMessage* msg)
{
	return m_VisionService->GetTextColor(msg, GetFieldIndex(msg));
}
//******************************************************************************
QIcon UIMessageColumn::GetIcon(IMessage* msg)
{
	return m_VisionService->GetIcon(msg, GetFieldIndex(msg));
}
//******************************************************************************
QString UIMessageColumn::GetToolTipsText(IMessage* msg)
{
	if (GetFieldIndex(msg) == emMSGFieldDetail)
		return QStringFrom(msg->GetDetail(_T("\n")));

	if (GetFieldIndex(msg) == emMSGFieldCurrentProcessName) {
		cxMSGProcess* process = msg->GetProcess();
		CString str;
		str.Format(_T("Name : %s\nPath : %s\nCommandline : %s"),
			process->m_ProcessName,
			process->m_ProcessPath,
			process->m_Commandline);
		return QStringFrom(str);
	}

	return QString();
}
//******************************************************************************
int UIMessageColumn::GetFieldIndex(IMessage* msg)
{
	return m_FieldIndex;
}
//******************************************************************************
