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
#include "FileVersion.h"
//******************************************************************************
#pragma comment(lib, "version.lib")
//******************************************************************************
BOOL SafeGetFileVersionInfoEx(
	_In_ DWORD dwFlags,
	_In_ LPCTSTR lptstrFilename,
	_Reserved_ DWORD dwHandle,
	_In_ DWORD dwLen,
	_Out_ LPVOID lpData)
{
	if (mod_version::GetFileVersionInfoExW(dwFlags, lptstrFilename, dwHandle, dwLen, lpData))
		return TRUE;

	return GetFileVersionInfo(lptstrFilename, dwHandle, dwLen, lpData);
}
//******************************************************************************
DWORD SafeGetFileVersionInfoSizeEx(
	_In_ DWORD dwFlags,
	_In_ LPCTSTR lptstrFilename,
	_Out_ LPDWORD lpdwHandle)
{
	DWORD ret = mod_version::GetFileVersionInfoSizeExW(dwFlags, lptstrFilename, lpdwHandle);

	if (ret != -1)
		return ret;

	return GetFileVersionInfoSize(lptstrFilename, lpdwHandle);
}
//******************************************************************************
cxFileVersion::cxFileVersion(LPCTSTR Path, ULONG Flags)
{
	Reset(Path, Flags);
}
//******************************************************************************
cxFileVersion::cxFileVersion(cxFileVersion&& Target)
{
	m_Path = Target.m_Path;
	m_Version = Target.m_Version;
	m_VersionSize = Target.m_VersionSize;
	m_Translation = Target.m_Translation;

	Target.m_Path.Empty();
	Target.m_Version = NULL;
	Target.m_VersionSize = 0;
	Target.m_Translation = 0;
}
//******************************************************************************
cxFileVersion::~cxFileVersion(void)
{
	if (m_Version)
		delete[](char*) m_Version;
}
//******************************************************************************
HRESULT cxFileVersion::Reset(LPCTSTR Path, ULONG Flags)
{
	{
		if (m_Version)
			delete[](char*) m_Version;

		m_Path.Empty();
		m_Version = NULL;
		m_VersionSize = 0;
		m_Translation = 0;
	}

	if (!Path)
		return E_INVALIDARG;

	m_Path = Path;

	m_VersionSize = SafeGetFileVersionInfoSizeEx(Flags, m_Path, NULL);

	if (0 == m_VersionSize)
		return HResultFromLastError();

	m_Version = (PVOID) new char[m_VersionSize];

	if (!m_Version)
		return E_UNEXPECTED;

	if (!SafeGetFileVersionInfoEx(Flags, m_Path, NULL, m_VersionSize, m_Version)) {
		delete[](char*) m_Version;
		m_Version = NULL;
		m_VersionSize = 0;
	}

	UINT len = 0;
	PVOID info = NULL;

	if (VerQueryValue(m_Version, _T("\\VarFileInfo\\Translation"), &info, &len) && len == sizeof(ULONG)) {
		m_Translation = *(PULONG)info;
	}

	return S_OK;
}
//******************************************************************************
CString cxFileVersion::GetStandardVersion(void) const
{
	CString str;

	if (!m_Version)
		return str;

	UINT len = 0;
	PVOID info = NULL;

	if (!VerQueryValue(m_Version, _T("\\"), &info, &len))
		return str;

	if (len != sizeof(VS_FIXEDFILEINFO))
		return str;

	VS_FIXEDFILEINFO* lpinfo = (VS_FIXEDFILEINFO*)info;

	str.Format(_T("%d.%d.%d.%d"),
		((PUSHORT)&lpinfo->dwFileVersionMS)[1],
		((PUSHORT)&lpinfo->dwFileVersionMS)[0],
		((PUSHORT)&lpinfo->dwFileVersionLS)[1],
		((PUSHORT)&lpinfo->dwFileVersionLS)[0]);

	return str;
}
//******************************************************************************
CString cxFileVersion::GetTimestamp(void) const
{
	CString str;

	HANDLE file_handle = INVALID_HANDLE_VALUE;

	do {
		file_handle = CreateFile(
			m_Path,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		if (INVALID_HANDLE_VALUE == file_handle)
			break;

		ULONG len = sizeof(IMAGE_DOS_HEADER);
		IMAGE_DOS_HEADER dos_header = {};

		if (!ReadFile(file_handle, &dos_header, len, &len, NULL))
			break;

		if (len != sizeof(IMAGE_DOS_HEADER))
			break;

		if (dos_header.e_magic != IMAGE_DOS_SIGNATURE)
			break;

		SetFilePointer(file_handle, dos_header.e_lfanew, NULL, FILE_BEGIN);

		len = sizeof(IMAGE_NT_HEADERS);
		IMAGE_NT_HEADERS nt_header = { 0 };

		if (!ReadFile(file_handle, &nt_header, len, &len, NULL))
			break;

		if (len != sizeof(IMAGE_NT_HEADERS))
			break;

		if (nt_header.Signature != IMAGE_NT_SIGNATURE)
			break;

		LONGLONG timestamp = Int32x32To64(nt_header.FileHeader.TimeDateStamp, 10000000) + 116444736000000000;

		SYSTEMTIME time;
		FileTimeToSystemTime((FILETIME*)&timestamp, &time);

		str.Format(_T("%d-%02d-%02d %02d:%02d:%02d"),
			time.wYear,
			time.wMonth,
			time.wDay,
			time.wHour,
			time.wMinute,
			time.wSecond);
	} while (false);

	if (file_handle != INVALID_HANDLE_VALUE)
		CloseHandle(file_handle);

	return str;
}
//******************************************************************************
CString cxFileVersion::GetStringFileInfo(LPCTSTR Type) const
{
	CString str;

	if (!m_Version || !Type)
		return str;

	CString strQuery;

	strQuery.Format(_T("\\StringFileInfo\\%04x%04x\\%s"),
		((PUSHORT)&m_Translation)[0],
		((PUSHORT)&m_Translation)[1],
		Type);

	UINT len = 0;
	PVOID info = NULL;

	if (!VerQueryValue(m_Version, strQuery, &info, &len))
		return str;

	str = CString((LPCTSTR)info, len);

	return str;
}
//******************************************************************************
cxFileVersion::operator bool(void)
{
	return m_Version != NULL;
}
//******************************************************************************
