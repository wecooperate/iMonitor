//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __ProcessModuleEnumerator_H__
#define __ProcessModuleEnumerator_H__
//******************************************************************************
#include <TlHelp32.h>
//******************************************************************************
class cxProcessModuleEnumerator : public cxEnumerator_<cxProcessModuleEnumerator>
{
public:
	explicit cxProcessModuleEnumerator	(ULONG ProcessId);
	~cxProcessModuleEnumerator			(void);

public:
	iterator		begin				(void);
	iterator		next				(void);

public:
	PMODULEENTRY32	operator->			(void);

private:
	HANDLE			m_Snapshot			= NULL;
	MODULEENTRY32	m_Entry				= {sizeof(m_Entry)};
};
//******************************************************************************
typedef struct _MODULEENTRY64 
{
	ULONGLONG		modBaseAddr;
	ULONG			modBaseSize;
	TCHAR			szModulePath[MAX_MODULE_NAME32 + 1];
	TCHAR			szExePath[MAX_PATH + 1];

}MODULEENTRY64, *PMODULEENTRY64;
//******************************************************************************
class cxProcessModuleEnumeratorWOW64 : public cxEnumerator_<cxProcessModuleEnumeratorWOW64>
{
public:
	explicit cxProcessModuleEnumeratorWOW64(HANDLE ProcessHandle);

public:
	iterator		begin				(void);
	iterator		next				(void);

private:
	bool			GetModule			(void);

private:
	HANDLE			m_ProcessHandle		= NULL;
	MODULEENTRY64	m_Entry				= {};
	ULONGLONG		m_ListHead			= 0;
	LDR_DATA_TABLE_ENTRY64 m_LdrEntry	= {};
};
//******************************************************************************
#endif
