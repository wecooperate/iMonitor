//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "Plugin.h"
#include "MessageColumn.h"
#include "Language.h"
//******************************************************************************
static PluginContext* s_Context = nullptr;
//******************************************************************************
String cxPlugin::GetName(void)
{
	return _T("ProcessBehavior");
}
//******************************************************************************
String cxPlugin::GetDescription(void)
{
	return _T("Detect Process Behaviors");
}
//******************************************************************************
String cxPlugin::GetAuthor(void)
{
	return _T("iMonitor");
}
//******************************************************************************
void cxPlugin::Initialize(PluginContext* Context)
{
	s_Context = Context;
}
//******************************************************************************
void cxPlugin::Release(void)
{
	delete this;
}
//******************************************************************************
ULONG cxPlugin::GetColumnCount(void)
{
	return GetColumns().size();
}
//******************************************************************************
IMessageColumn* cxPlugin::GetColumn(ULONG Index)
{
	auto& columns = GetColumns();

	return Index >= columns.size() ? nullptr : columns[Index];
}
//******************************************************************************
void cxPlugin::OnEvent(ULONG Event, PVOID Context)
{
	if (!Context)
		return;

	if (Event == emEventLanguageChange) {
		ChangeLanguage(*(LANGID*)Context);
	}
}
//******************************************************************************
extern "C" __declspec(dllexport) IPlugin* WINAPI iMonitorCreatePlugin()
{
	return new cxPlugin();
}
//******************************************************************************
PluginContext* GetPluginContext(void)
{
	return s_Context;
}
//******************************************************************************
