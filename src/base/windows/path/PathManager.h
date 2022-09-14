//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __PathManager_H__
#define __PathManager_H__
//******************************************************************************
// clang-format off
//******************************************************************************
#include <atlpath.h>
#include <ShlObj.h>
//******************************************************************************
class cxPath : public ATL::CPath
{
public:
	using CPath::CPath;

public:
	operator	CString					(void);
	operator	LPCTSTR					(void);

public:
	CString		GetString				(void);
	CString		GetFileName				(void);
};
//******************************************************************************
class cxPathManager
{
#define g_Path SINGLETON_(cxPathManager)

public:
	cxPath		GetCanonicalizePath		(LPCTSTR lpPath);
	cxPath		GetCurrentDirectory		(void);
	cxPath		GetCurrentPath			(LPCTSTR lpFileName = NULL);
	cxPath		GetMainDirectory		(void);
	cxPath		GetMainPath				(LPCTSTR lpFileName = NULL);
	cxPath		GetTempDirectory		(void);
	cxPath		GetWindowDirectory		(void);
	cxPath		GetSpecialDirectory		(int csidl);
};
//******************************************************************************
#endif
