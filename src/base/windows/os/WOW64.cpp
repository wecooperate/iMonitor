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
#include "WOW64.h"
//******************************************************************************
bool cxWOW64::IsWOW64Process(HANDLE ProcessHandle)
{
	BOOL ret = FALSE;

	mod_kernel32::IsWow64Process(ProcessHandle, &ret);

	return ret == TRUE;
}
//******************************************************************************
bool cxWOW64::IsWOW64Process(void)
{
	static bool ret = IsWOW64Process(GetCurrentProcess());

	return ret;
}
//******************************************************************************
void* cxWOW64::DisableFileRedirection(void)
{
	PVOID ret = NULL;

	mod_kernel32::Wow64DisableWow64FsRedirection(&ret);

	return ret;
}
//******************************************************************************
void cxWOW64::RevertFileRedirection(void* OldValue)
{
	mod_kernel32::Wow64RevertWow64FsRedirection(OldValue);
}
//******************************************************************************
void cxWOW64::EnableFileRedirection(void)
{
	mod_kernel32::Wow64RevertWow64FsRedirection((PVOID)NULL);
}
//******************************************************************************
