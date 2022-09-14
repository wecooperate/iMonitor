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
#include "PathTransfer.h"
//******************************************************************************
cxPathTransfer::cxPathTransfer(void)
{
	AUTO_LOCK(m_Lock);

	AddDevicePath();
	AddPath();
	AddRegPath();
}
//******************************************************************************
CString cxPathTransfer::Transfer(LPCTSTR Path)
{
	AUTO_LOCK(m_Lock);

	for (auto& it : m_DevicePathTable) {
		if (0 == _tcsnicmp(it.Prefix, Path, it.Prefix.GetLength())) {
			LPCTSTR offset = Path + it.Prefix.GetLength();

			if (*offset == _T('\\') || *offset == _T('/') || *offset == 0) {
				CString strPath = it.Transfer;
				strPath += offset;
				return strPath;
			}
		}
	}

	for (auto& it : m_PathTable) {
		if (0 == _tcsnicmp(it.Prefix, Path, it.Prefix.GetLength())) {
			LPCTSTR offset = Path + it.Prefix.GetLength();

			if (*offset == _T('\\') || *offset == _T('/') || *offset == 0) {
				CString strPath = it.Transfer;
				strPath += offset;
				return strPath;
			}
		}
	}

	return Path;
}
//******************************************************************************
void cxPathTransfer::ResetDevicePath(void)
{
	AUTO_LOCK(m_Lock);

	m_DevicePathTable.clear();

	AddDevicePath();
}
//******************************************************************************
void cxPathTransfer::AddDevicePath(void)
{
	for (TCHAR driver = _T('C'); driver <= _T('Z'); driver++) {
		TCHAR dosPath[4] = { 0 };
		TCHAR devicePath[MAX_PATH + 1] = { 0 };

		dosPath[0] = driver;
		dosPath[1] = _T(':');

		if (0 == QueryDosDevice(dosPath, devicePath, MAX_PATH))
			continue;

		cxPathPair pair;
		pair.Prefix = devicePath;
		pair.Transfer = dosPath;
		m_DevicePathTable.push_back(pair);
	}
}
//******************************************************************************
void cxPathTransfer::AddPathPair(LPCTSTR Prefix, LPCTSTR Transfer)
{
	AUTO_LOCK(m_Lock);

	cxPathPair pair;
	pair.Prefix = Prefix;
	pair.Transfer = Transfer;
	m_PathTable.push_back(pair);
}
//******************************************************************************
void cxPathTransfer::AddPath(void)
{
	TCHAR path[MAX_PATH + 1] = { 0 };

	GetWindowsDirectory(path, MAX_PATH);
	PathRemoveBackslash(path);

	AddPathPair(_T("Windows"), path);
	AddPathPair(_T("Systemroot"), path);
	AddPathPair(_T("\\Windows"), path);
	AddPathPair(_T("\\Systemroot"), path);

	PathAppend(path, _T("System32"));

	AddPathPair(_T("system32"), path);
	AddPathPair(_T("\\system32"), path);

	AddPathPair(_T("\\??"), _T(""));
	AddPathPair(_T("\\Device\\LanmanRedirector"), _T("\\"));
	AddPathPair(_T("\\Device\\Mup"), _T("\\"));
	AddPathPair(_T("\\Device\\Hgfs"), _T("\\"));
}
//******************************************************************************
void cxPathTransfer::AddRegPath(void)
{
	CAccessToken token;
	token.GetProcessToken(TOKEN_ALL_ACCESS);
	CSid sid;
	token.GetUser(&sid);
	CString strSid = sid.Sid();

	CString strHKCU;
	strHKCU.Format(_T("\\Registry\\User\\%s"), strSid);
	AddPathPair(strHKCU, _T("HKEY_CURRENT_USER"));
	strHKCU = _T("\\Registry\\") + strHKCU;
	AddPathPair(strHKCU, _T("HKEY_CURRENT_USER"));

	strHKCU.Format(_T("\\Registry\\User\\%s_Classes"), strSid);
	AddPathPair(strHKCU, _T("HKEY_CLASSES_ROOT"));
	strHKCU = _T("\\Registry\\") + strHKCU;
	AddPathPair(strHKCU, _T("HKEY_CLASSES_ROOT"));

	AddPathPair(_T("\\Registry\\\\Registry\\Machine"), _T("HKEY_LOCAL_MACHINE"));
	AddPathPair(_T("\\Registry\\Machine"), _T("HKEY_LOCAL_MACHINE"));

	AddPathPair(_T("\\Registry\\\\Registry\\User"), _T("HKEY_USERS"));
	AddPathPair(_T("\\Registry\\User"), _T("HKEY_USERS"));
}
//******************************************************************************
