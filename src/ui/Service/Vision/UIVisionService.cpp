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
#include "UIVisionService.h"
//******************************************************************************
UIVisionService::UIVisionService(void)
{
	m_ErrorColor = QColor(200, 90, 90);
	m_Colors[emMSGGroupInternal] = QColor();
	m_Colors[emMSGGroupProcess] = QColor(210, 235, 210);
	m_Colors[emMSGGroupFile] = QColor(255, 255, 230);
	m_Colors[emMSGGroupRegistry] = QColor(217, 247, 243);
	m_Colors[emMSGGroupSocket] = QColor(166, 216, 255);

	m_UserIcon = g_res->icon_msg_user;
	m_KernelIcon = g_res->icon_msg_kernel;

	m_Icons[emMSGGroupProcess] = g_res->icon_msg_process;
	m_Icons[emMSGGroupFile] = g_res->icon_msg_file;
	m_Icons[emMSGGroupRegistry] = g_res->icon_msg_registry;
	m_Icons[emMSGGroupSocket] = g_res->icon_msg_network;
}
//******************************************************************************
QColor UIVisionService::GetColor(IMessage* msg, int index)
{
	if (!g_Config->IsEnableColorful)
		return QColor();

	if (index == emMSGFieldStatus && msg->m_Status != 0)
		return m_ErrorColor;

	return m_Colors[msg->GetGroup()];
}
//******************************************************************************
QColor UIVisionService::GetTextColor(IMessage* msg, int index)
{
	if (!g_Config->IsEnableColorful)
		return QColor();

	return QColor();
}
//******************************************************************************
QIcon UIVisionService::GetIcon(IMessage* msg, int index)
{
	if (index == emMSGFieldType)
		return m_Icons[msg->GetGroup()];

	if (index == emMSGFieldCurrentProcessName)
		return GetIcon(msg->GetProcess()->m_Icon);

	return QIcon();
}
//******************************************************************************
QIcon UIVisionService::GetIcon(HICON Icon)
{
	auto it = m_WinIcons.find(Icon);

	if (it != m_WinIcons.end())
		return it->second;

	QIcon ico = QtWin::fromHICON(Icon);

	m_WinIcons[Icon] = ico;

	return ico;
}
//******************************************************************************
QIcon UIVisionService::GetGroupIcon(int Group)
{
	return m_Icons[Group];
}
//******************************************************************************
QIcon UIVisionService::GetCallstackIcon(bool kernel)
{
	return kernel ? m_KernelIcon : m_UserIcon;
}
//******************************************************************************
