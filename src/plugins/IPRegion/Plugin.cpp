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
//******************************************************************************
String cxPlugin::GetName(void)
{
	return _T("IPRegion");
}
//******************************************************************************
String cxPlugin::GetDescription(void)
{
	return _T("Parse ip address region");
}
//******************************************************************************
String cxPlugin::GetAuthor(void)
{
	return _T("iMonitor");
}
//******************************************************************************
void cxPlugin::Initialize(PluginContext* Context)
{
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
extern "C" __declspec(dllexport) IPlugin* WINAPI iMonitorCreatePlugin()
{
	return new cxPlugin();
}
//******************************************************************************
