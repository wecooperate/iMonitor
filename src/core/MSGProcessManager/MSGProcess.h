//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __MSGProcess_1_H__
#define __MSGProcess_1_H__
//******************************************************************************
#include "MSGProcessModule.h"
//******************************************************************************
class cxMSGProcess : public cxSafeObject
{
public:
	cxMSGProcess(ULONG ProcessId);
	cxMSGProcess(PSYSTEM_PROCESS_INFORMATION ProcessInfo);
	~cxMSGProcess(void);

public:
	cxMSGProcessModule* GetModule(ULONGLONG Address, ULONGLONG Time = 0);
	void InsertModule(cxMSGProcessModule&& Module);
	void EnumModules(std::function<bool(const cxMSGProcessModule&)> Callback);

private:
	void GetInformation(void);
	void GetBaseInformation(void);
	void GetUserModule(void);
	void GetKernelModule(void);
	void LoadProcessIcon(void);

public:
	void FixInformation(ULONGLONG CreateTime, ULONG ParentProcessId, LPCTSTR Path, LPCTSTR Commandline);

public:
	cxFileVersion m_FileVersion;
	CString m_ProcessName;
	CString m_ProcessPath;
	CString m_Commandline;
	ULONG m_ProcessId = 0;
	ULONG m_ParentProcessId = 0;
	ULONGLONG m_CreateTime = 0;
	ULONGLONG m_ExitTime = 0;
	HICON m_Icon = NULL;

protected:
	cxLock m_Lock;
	std::list<std::unique_ptr<cxMSGProcessModule>> m_Modules;
};
//******************************************************************************
#endif
