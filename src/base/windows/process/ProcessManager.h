//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __ProcessManager_H__
#define __ProcessManager_H__
//******************************************************************************
class cxProcessManager
{
#define g_ProcessManager SINGLETON_(cxProcessManager)

public:
	HANDLE	Execute(
		LPCTSTR		lpOperation,
		LPCTSTR		lpFile,
		LPCTSTR		lpParameters	= NULL,
		int			nShow			= SW_SHOW
		);

	HANDLE	Create(
		LPCTSTR		lpFile,
		LPCTSTR		lpParameters	= NULL,
		int			nShow			= SW_SHOW
		);

	HANDLE	CreateAsUser(
		HANDLE		TokenHandle,
		LPCTSTR		lpFile,
		LPCTSTR		lpParameters	= NULL,
		int			nShow			= SW_SHOW
		);

	HANDLE	CreateAsSession(
		ULONG		SessionId,
		LPCTSTR		lpFile,
		LPCTSTR		lpParameters	= NULL,
		int			nShow			= SW_SHOW
		);

	HANDLE	CreateAsCurrentConsole(
		LPCTSTR		lpFile,
		LPCTSTR		lpParameters	= NULL,
		int			nShow			= SW_SHOW
		);

	bool	CreateAndWaitAll(
		LPCTSTR		lpFile,
		LPCTSTR		lpParameters	= NULL,
		int			nShow			= SW_SHOW
		);

public:
	CString	MakeCommandline				(LPCTSTR lpFile, LPCTSTR lpParameters);

public:
	CString	GetProcessPath				(HANDLE ProcessHandle);
	CString	GetProcessPath				(ULONG ProcessId);
	CString	GetProcessCommandline		(HANDLE ProcessHandle);
	CString	GetProcessCommandline		(ULONG ProcessId);
	CString	GetProcessCommandlineWOW64	(HANDLE ProcessHandle);
};
//******************************************************************************
#endif
