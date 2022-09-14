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
#include "PathLocate.h"
//******************************************************************************
HRESULT cxPathLocate::Locate(LPCTSTR Path)
{
	if (!Path)
		return E_INVALIDARG;

	WOW64AutoDisableFileRedirection _0_;

	if (0 == _tcsncmp(Path, _T("HKEY"), _tcslen(_T("HKEY"))))
		return LocateRegistry(Path);

	return LocateFile(Path);
}
//******************************************************************************
HRESULT cxPathLocate::LocateFile(LPCTSTR Path)
{
	if (!Path)
		return E_INVALIDARG;

	if (PathIsDirectory(Path)) {
		if (ShellExecute(NULL, _T("explore"), Path, NULL, NULL, SW_SHOW) < (HINSTANCE)32)
			return HResultFromLastError();

		return S_OK;
	}

	CString str;
	str.Format(_T("/select, \"%s\""), Path);

	if (ShellExecute(NULL, _T("open"), _T("explorer.exe"), str, NULL, SW_SHOW) < (HINSTANCE)32)
		return HResultFromLastError();

	return S_OK;
}
//******************************************************************************
HRESULT cxPathLocate::LocateRegistry(LPCTSTR Path)
{
	if (!Path)
		return E_INVALIDARG;

	HANDLE process_handle = NULL;
	HWND regedit_wnd = NULL;

	regedit_wnd = FindWindow(_T("RegEdit_RegEdit"), NULL);

	if (regedit_wnd == NULL) {
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi = {};
		TCHAR name[] = _T("regedit.exe");

		if (!CreateProcess(NULL, name, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
			return HResultFromLastError();

		CloseHandle(pi.hThread);
		process_handle = pi.hProcess;
		WaitForInputIdle(process_handle, INFINITE);

		regedit_wnd = FindWindow(_T("RegEdit_RegEdit"), NULL);
	}

	HRESULT hr = E_FAIL;

	do {
		if (regedit_wnd == NULL)
			break;

		SetForegroundWindow(regedit_wnd);
		SetFocus(regedit_wnd);

		regedit_wnd = FindWindowEx(regedit_wnd, 0, _T("SysTreeView32"), NULL);

		if (regedit_wnd == NULL)
			break;

		if (process_handle == NULL) {
			ULONG pid = 0;
			GetWindowThreadProcessId(regedit_wnd, &pid);
			process_handle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);

			if (process_handle == NULL)
				break;
		}

		SetForegroundWindow(regedit_wnd);
		SetFocus(regedit_wnd);

		for (int i = 0; i < 32; i++) {
			SendMessage(regedit_wnd, WM_KEYDOWN, VK_LEFT, 0);
			WaitForInputIdle(process_handle, INFINITE);
		}

		SendMessage(regedit_wnd, WM_KEYDOWN, VK_RIGHT, 0);
		WaitForInputIdle(process_handle, INFINITE);

		CString str = Path;

		for (int i = 0; i < str.GetLength(); i++) {
			UCHAR ch = str[i];

			if (ch == '\\') {
				SendMessage(regedit_wnd, WM_KEYDOWN, VK_RIGHT, 0);
				WaitForInputIdle(process_handle, INFINITE);
			} else {
				ch = toupper(ch);
				SendMessage(regedit_wnd, WM_CHAR, ch, 0);
				WaitForInputIdle(process_handle, INFINITE);
			}
		}

		SetForegroundWindow(regedit_wnd);
		SetFocus(regedit_wnd);

		hr = S_OK;
	} while (false);

	if (process_handle)
		CloseHandle(process_handle);

	return hr;
}
//******************************************************************************
