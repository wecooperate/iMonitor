//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __Internal_H__
#define __Internal_H__
//******************************************************************************
#include "ntdll.h"
#include "DynamicFunction.h"
//******************************************************************************
#define DYNAMIC_FUNCTION_MAP_NTDLL(name) DYNAMIC_FUNCTION_MAP(name, STATUS_NOT_IMPLEMENTED)
//******************************************************************************
BEGIN_DYNAMIC_FUNCTION_MAP(mod_ntdll, "ntdll.dll")
	DYNAMIC_FUNCTION_MAP_NTDLL(ZwQuerySystemInformation)
	DYNAMIC_FUNCTION_MAP_NTDLL(ZwQueryInformationProcess)
	DYNAMIC_FUNCTION_MAP_NTDLL(ZwQueryInformationThread)
	DYNAMIC_FUNCTION_MAP_NTDLL(ZwQueryObject)
	DYNAMIC_FUNCTION_MAP_NTDLL(ZwWow64QueryInformationProcess64)
	DYNAMIC_FUNCTION_MAP_NTDLL(ZwWow64ReadVirtualMemory64)
	DYNAMIC_FUNCTION_MAP_NTDLL(RtlGetVersion)
	DYNAMIC_FUNCTION_MAP_NTDLL(RtlNtStatusToDosError)
END_DYNAMIC_FUNCTION_MAP()
//******************************************************************************
inline HRESULT HResultFromStatus(NTSTATUS Status)
{
	return mod_ntdll::RtlNtStatusToDosError(Status);
}
//******************************************************************************
#endif
