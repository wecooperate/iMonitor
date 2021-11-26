//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __SymbolModule_H__
#define __SymbolModule_H__
//******************************************************************************
// clang-format off
//******************************************************************************
#include <Dbghelp.h>
//******************************************************************************
struct cxSymbolModuleInfo 
{
	LPCTSTR			Path;
	ULONG			SizeOfImage;
	PVOID			DebugData;
	ULONG			DebugDataLength;
};
//******************************************************************************
class cxSymbolModule
{
public:
	bool			Initialize			(LPCTSTR Path);

	bool			LoadModule			(HANDLE SymHandle);
	bool			ForceLoadModule		(HANDLE SymHandle, LPCTSTR PDBPath);
	void			ReleaseModule		(HANDLE SymHandle);

public:
	ULONGLONG		GetModuleBase		(void);
	CString			GetPDBPath			(void);

public:
	bool			LoadDebugData		(void);
	void			ReleaseDebugData	(void);

public:
	bool			IsEqual				(const cxSymbolModule& Module);
	bool			IsEqualDebugData	(const cxSymbolModule& Module);

public:
	CString			m_Path;
	CString			m_Name;
	CString			m_PDBPath;

protected:
	ULONGLONG		m_FileSize			= 0;
	ULONGLONG		m_LastWriteTime		= 0;
	ULONGLONG		m_FastHash			= 0;

	PVOID			m_DebugData			= NULL;
	ULONG			m_DebugDataLength	= 0;
	ULONGLONG		m_DebugDataHash		= 0;

	ULONGLONG		m_ImageBase			= 0;
	ULONG			m_SizeOfImage		= 0;
	ULONGLONG		m_SymbolImageBase	= 0;
};
//******************************************************************************
#endif
