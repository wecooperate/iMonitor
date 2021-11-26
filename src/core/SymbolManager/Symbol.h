//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __Symbol_H__
#define __Symbol_H__
//******************************************************************************
// clang-format off
//******************************************************************************
class cxSymbol 
{
public:
	cxSymbol						(ULONGLONG Address, ULONG ProcessId, ULONGLONG Time = 0);

public:
	CString		GetSymbol			(void) const;
	bool		IsKernelAddress		(void) const;

public:
	CString		m_ModulePath;
	CString		m_ModuleName;
	ULONGLONG	m_Address			= 0;
	ULONGLONG	m_ModuleBase		= 0;
	ULONG		m_ModuleOffset		= 0;
	ULONG		m_SymbolOffset		= 0;
	CString		m_PDBPath;
	CString		m_SymbolName;
	CString		m_DecoratedSymbolName;
	CString		m_SourceFilePath;
	ULONG		m_SourceFileLine	= 0;
};
//******************************************************************************
#endif
