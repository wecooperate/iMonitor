//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIProcessManager_H__
#define __UIProcessManager_H__
//******************************************************************************
#include "MSGProcess.h"
//******************************************************************************
class cxMSG;
//******************************************************************************
class cxMSGProcessManager
{
#define g_MSGProcessManager SINGLETON_(cxMSGProcessManager)

public:
	cxMSGProcessManager(void);

public:
	cxMSGProcess* GetProcess(ULONG ProcessId, ULONGLONG Time = 0);

public:
	void OnProcessCreate(cxMSG* msg);
	void OnProcessExit(cxMSG* msg);
	void OnLoadModule(cxMSG* msg);

protected:
	cxMSGProcess* CreateProcess(ULONG ProcessId);

private:
	cxLock m_Lock;
	std::multimap<ULONG, std::unique_ptr<cxMSGProcess>> m_Processes;
};
//******************************************************************************
#endif
