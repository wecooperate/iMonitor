//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __windows_1D5E7037_28ED_4084_A8F4_EA3FCA0CD6F0__
#define __windows_1D5E7037_28ED_4084_A8F4_EA3FCA0CD6F0__
//******************************************************************************
#pragma warning(disable : 4311)
#pragma warning(disable : 4302)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#pragma warning(disable : 4091)
#pragma warning(disable : 4005)
#pragma warning(disable : 26110)
//******************************************************************************
#ifndef NTDDI_VERSION
#define NTDDI_VERSION NTDDI_WIN7
#endif
//******************************************************************************
#ifndef WINVER
#define WINVER _WIN32_WINNT_WIN7
#endif
//******************************************************************************
#ifndef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_WIN7
#endif
//******************************************************************************
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS _WIN32_WINNT_WIN7
#endif
//******************************************************************************
#ifndef _WIN32_IE
#define _WIN32_IE _WIN32_IE_IE70
#endif
//******************************************************************************
#define _ATL_XP_TARGETING
//******************************************************************************
#ifndef PSAPI_VERSION
#define PSAPI_VERSION 1
#endif
//******************************************************************************
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
//******************************************************************************
#ifdef MFC_SUPPORT
#define __ATLSYNC_H__
#include <afxwin.h>
#include <afxmt.h>
#endif
//******************************************************************************
#include <tchar.h>
#include <windows.h>
#include <WinSvc.h>
#include <locale.h>
#include <ShellAPI.h>
//******************************************************************************
#include <atlbase.h>
#include <atlstr.h>
#include <atlpath.h>
#include <atlsecurity.h>
#include <atlsync.h>
#include <atlcom.h>
//******************************************************************************
BEGIN_NAME_SPACE(global)
//******************************************************************************
inline ULONGLONG MakeULONGLONG(ULONG LowPart, ULONG HighPart)
{
	ULARGE_INTEGER data;
	data.LowPart = LowPart;
	data.HighPart = HighPart;

	return data.QuadPart;
}
//******************************************************************************
inline HRESULT HResultFromLastError(DWORD dwLastError = GetLastError())
{
	return (dwLastError == 0) ? E_FAIL : HRESULT_FROM_WIN32(dwLastError);
};
//******************************************************************************
inline CString StringFromGUID(REFGUID Guid)
{
	LPWSTR str = NULL;
	HRESULT hr = StringFromCLSID(Guid, &str);

	if (hr != S_OK || !str)
		return CString();

	CString strGUID = str;

	CoTaskMemFree(str);

	return strGUID;
}
//******************************************************************************
inline CString StringFromError(ULONG Errcode, DWORD LanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))
{
	if (Errcode == S_OK)
		return _T("Success");

	TCHAR msg[MAX_PATH] = {};

	DWORD len = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		Errcode,
		LanguageId,
		msg,
		MAX_PATH,
		NULL);

	if (len > 3 && len < MAX_PATH)
		msg[len - 3] = 0;

	return msg;
}
//******************************************************************************
inline CString StringFromULONG(ULONG Data)
{
	CString str;
	str.Format(_T("%d"), Data);
	return str;
}
//******************************************************************************
inline CString StringFromCurrentTime(void)
{
	SYSTEMTIME time = {};
	GetLocalTime(&time);
	CString str;
	str.Format(_T("%d-%02d-%02d %02d:%02d:%02d"),
		time.wYear,
		time.wMonth,
		time.wDay,
		time.wHour,
		time.wMinute,
		time.wSecond);
	return str;
}
//******************************************************************************
inline std::string StdStringFromULONG(ULONG Data)
{
	CStringA str;
	str.Format("%d", Data);
	return str.GetString();
}
//******************************************************************************
inline ULONGLONG GetCurrentTime64(void)
{
	ULONGLONG time = 0;
	GetSystemTimeAsFileTime((PFILETIME)&time);
	FileTimeToLocalFileTime((PFILETIME)&time, (PFILETIME)&time);
	return time;
}
//******************************************************************************
inline ULONGLONG GetCurrentTickCount()
{
	typedef ULONGLONG(WINAPI * PFN_GetTickCount64)(void);

	static auto pfn = (PFN_GetTickCount64)GetProcAddress(GetModuleHandle(_T("kernel32")), "GetTickCount64");

	if (pfn)
		return pfn();

	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
//******************************************************************************
inline void EnableDebugPrivilege(void)
{
	CAccessToken token;
	token.GetProcessToken(TOKEN_ALL_ACCESS);
	token.EnablePrivilege(SE_DEBUG_NAME);
}
//******************************************************************************
END_NAME_SPACE()
//******************************************************************************
#endif
