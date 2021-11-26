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
#include "MSGConfig.h"
//******************************************************************************
// clang-format off
//******************************************************************************
static std::list<cxMSGConfigItem> s_items = {
	{ emMSGProcessCreate,			_T("CreateProcess") },
	{ emMSGProcessStart, 			_T("ProcessStart") },
	{ emMSGProcessExit, 			_T("ProcessExit") },
	{ emMSGProcessOpen, 			_T("OpenProcess") },
	{ emMSGThreadCreate, 			_T("CreateThread") },
	{ emMSGThreadStart, 			_T("ThreadStart") },
	{ emMSGThreadExit, 				_T("ThreadExit") },
	{ emMSGThreadOpen, 				_T("OpenThread") },
	{ emMSGImageLoad, 				_T("LoadImage") },

	{ emMSGFilePostCreate, 			_T("CreateFile") },
	{ emMSGFilePostQueryOpen, 		_T("QueryOpenFile") },
	{ emMSGFileCleanup, 			_T("CloseFile") },
	{ emMSGFilePostCreateSection,	_T("CreateSection") },
	{ emMSGFilePostCreateHardLink, 	_T("CreateHardlink") },
	{ emMSGFilePostRename, 			_T("RenameFile") },
	{ emMSGFilePostDelete, 			_T("DeleteFile") },
	{ emMSGFilePostRead, 			_T("ReadFile") },
	{ emMSGFilePostWrite, 			_T("WriteFile") },

	{ emMSGRegPostDeleteKey, 		_T("DeleteKey") },
	{ emMSGRegPostRenameKey, 		_T("RenameKey") },
	{ emMSGRegPostOpenKey, 			_T("OpenKey") },
	{ emMSGRegPostCreateKey, 		_T("CreateKey") },
	{ emMSGRegPostEnumKey, 			_T("EnumKey") },
	{ emMSGRegPostDeleteValue, 		_T("DeleteValue") },
	{ emMSGRegPostSetValue, 		_T("SetValue") },

	{ emMSGSocketCreate, 			_T("Socket") },
	{ emMSGSocketPostControl, 		_T("SocketControl") },
	{ emMSGSocketPostConnect, 		_T("Connect") },
	{ emMSGSocketSend, 				_T("Send") },
	{ emMSGSocketPostRecv, 			_T("Recv") },
	{ emMSGSocketSendTo, 			_T("SendTo") },
	{ emMSGSocketPostRecvFrom, 		_T("RecvFrom") },
	{ emMSGSocketPostAccept, 		_T("Accept") },
};
//******************************************************************************
// clang-format on
//******************************************************************************
cxMSGConfig::cxMSGConfig(void)
{
	for (int i = 0; i < _countof(m_GroupConfigs); i++)
		m_GroupConfigs[i] = true;

	for (int i = 0; i < _countof(m_Configs); i++)
		m_Configs[i] = true;

	m_GroupConfigs[emMSGGroupInternal] = false;
}
//******************************************************************************
bool cxMSGConfig::IsEnable(ULONG Type)
{
	if (Type > _countof(m_Configs))
		return false;

	if (!m_Configs[Type])
		return false;

	if (!m_GroupConfigs[MSG_GET_GROUP(Type)])
		return false;

	return true;
}
//******************************************************************************
bool cxMSGConfig::IsGroupEnable(ULONG GroupType)
{
	if (GroupType >= _countof(m_GroupConfigs))
		return false;

	return m_GroupConfigs[GroupType];
}
//******************************************************************************
void cxMSGConfig::SetGroupEnable(ULONG GroupType, bool Enable)
{
	if (GroupType >= _countof(m_GroupConfigs))
		return;

	m_GroupConfigs[GroupType] = Enable;
}
//******************************************************************************
void cxMSGConfig::SetEnable(ULONG Type, bool Enable)
{
	if (Type >= _countof(m_Configs))
		return;

	m_Configs[Type] = Enable;
}
//******************************************************************************
const std::list<cxMSGConfigItem>& cxMSGConfig::GetConfigItems(void)
{
	return s_items;
}
//******************************************************************************
