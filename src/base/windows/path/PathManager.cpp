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
#include "PathManager.h"
//******************************************************************************
#include <shlobj.h>
//******************************************************************************
cxPath::operator CString(void)
{
	return m_strPath;
}
//******************************************************************************
cxPath::operator LPCTSTR(void)
{
	return m_strPath;
}
//******************************************************************************
CString cxPath::GetString(void)
{
	return m_strPath.GetString();
}
//******************************************************************************
CString cxPath::GetFileName(void)
{
	return PathFindFileName(m_strPath);
}
//******************************************************************************
cxPath cxPathManager::GetCanonicalizePath(LPCTSTR lpPath)
{
	TCHAR lpPathFix[MAX_PATH] = {};

	PathCanonicalize(lpPathFix, lpPath);

	return cxPath(lpPathFix);
}
//******************************************************************************
cxPath cxPathManager::GetMainDirectory(void)
{
	TCHAR lpPath[MAX_PATH] = {};

	GetModuleFileName(NULL, lpPath, MAX_PATH - 1);
	PathRemoveFileSpec(lpPath);
	PathAddBackslash(lpPath);

	return GetCanonicalizePath(lpPath);
}
//******************************************************************************
cxPath cxPathManager::GetMainPath(LPCTSTR lpFileName)
{
	TCHAR lpPath[MAX_PATH] = {};

	GetModuleFileName(NULL, lpPath, MAX_PATH - 1);

	if (!lpFileName)
		return GetCanonicalizePath(lpPath);

	PathRemoveFileSpec(lpPath);
	PathAppend(lpPath, lpFileName);

	return GetCanonicalizePath(lpPath);
}
//******************************************************************************
cxPath cxPathManager::GetCurrentDirectory(void)
{
	TCHAR lpPath[MAX_PATH] = {};

	GetModuleFileName((HMODULE)&__ImageBase, lpPath, MAX_PATH - 1);
	PathRemoveFileSpec(lpPath);
	PathAddBackslash(lpPath);

	return GetCanonicalizePath(lpPath);
}
//******************************************************************************
cxPath cxPathManager::GetCurrentPath(LPCTSTR lpFileName)
{
	TCHAR lpPath[MAX_PATH] = {};

	GetModuleFileName((HMODULE)&__ImageBase, lpPath, MAX_PATH - 1);

	if (!lpFileName)
		return GetCanonicalizePath(lpPath);

	PathRemoveFileSpec(lpPath);
	PathAppend(lpPath, lpFileName);

	return GetCanonicalizePath(lpPath);
}
//******************************************************************************
cxPath cxPathManager::GetTempDirectory(void)
{
	TCHAR lpPath[MAX_PATH] = {};

	::GetTempPath(MAX_PATH - 1, lpPath);
	PathAddBackslash(lpPath);

	return cxPath(lpPath);
}
//******************************************************************************
cxPath cxPathManager::GetWindowDirectory(void)
{
	TCHAR lpPath[MAX_PATH] = {};

	::GetWindowsDirectory(lpPath, MAX_PATH - 1);
	PathAddBackslash(lpPath);

	return cxPath(lpPath);
}
//******************************************************************************
cxPath cxPathManager::GetSpecialDirectory(int csidl)
{
	TCHAR lpPath[MAX_PATH] = {};

	SHGetSpecialFolderPath(NULL, lpPath, csidl, TRUE);
	PathAddBackslash(lpPath);

	return cxPath(lpPath);
}
//******************************************************************************
