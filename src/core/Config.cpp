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
#include "Config.h"
#include "Core/MSGManager/MSGConfig.h"
//******************************************************************************
#define CONFIG_SECTION "global"
//******************************************************************************
cxConfig::cxConfig(void)
{
	for (int i = 0; i < _countof(m_SwitchTable); i++)
		m_SwitchTable[i] = false;

	IsEnableCapture = true;
}
//******************************************************************************
template<typename T, typename TBinary>
void LoadConfigFromBinary(T* arr, size_t count, const TBinary& config)
{
	T* data = (T*)config.c_str();

	for (size_t i = 0; i < config.size(); i++) {
		if (i >= count) {
			break;
		}
		arr[i] = data[i];
	}
}
//******************************************************************************
void cxConfig::LoadConfig(IConfig* Config)
{
	if (!Config)
		return;

	auto& msg_config = g_MSGConfig->m_Configs;
	auto& msg_group_config = g_MSGConfig->m_GroupConfigs;

	LoadConfigFromBinary(m_SwitchTable, _countof(m_SwitchTable), Config->GetSectionBinary(CONFIG_SECTION, "switch"));
	LoadConfigFromBinary(msg_config, _countof(msg_config), Config->GetSectionBinary(CONFIG_SECTION, "msg_config"));
	LoadConfigFromBinary(msg_group_config, _countof(msg_group_config), Config->GetSectionBinary(CONFIG_SECTION, "msg_group_config"));
}
//******************************************************************************
void cxConfig::SaveConfig(IConfig* Config)
{
	if (!Config)
		return;

	auto& msg_config = g_MSGConfig->m_Configs;
	auto& msg_group_config = g_MSGConfig->m_GroupConfigs;

	Config->SetSectionBinary(CONFIG_SECTION, "switch", (PBYTE)&m_SwitchTable, sizeof(m_SwitchTable));
	Config->SetSectionBinary(CONFIG_SECTION, "msg_config", (PBYTE)&msg_config, sizeof(msg_config));
	Config->SetSectionBinary(CONFIG_SECTION, "msg_group_config", (PBYTE)&msg_group_config, sizeof(msg_group_config));
}
//******************************************************************************
bool cxConfig::GetSwitch(emUserConfigSwitch Switch)
{
	return m_SwitchTable[Switch];
}
//******************************************************************************
void cxConfig::SetSwitch(emUserConfigSwitch Switch, bool Enable)
{
	m_SwitchTable[Switch] = Enable;
}
//******************************************************************************
bool cxConfig::IsMSGEnable(ULONG Type)
{
	return g_MSGConfig->IsEnable(Type);
}
//******************************************************************************
bool cxConfig::IsMSGGroupEnable(ULONG GroupType)
{
	return g_MSGConfig->IsGroupEnable(GroupType);
}
//******************************************************************************
void cxConfig::SetIsUniqueMessage(bool enable)
{
	g_MSGConfig->m_IsUniqueMessage = enable;
}
//******************************************************************************
void cxConfig::SetMSGGroupEnable(ULONG GroupType, bool Enable)
{
	g_MSGConfig->SetGroupEnable(GroupType, Enable);
}
//******************************************************************************
