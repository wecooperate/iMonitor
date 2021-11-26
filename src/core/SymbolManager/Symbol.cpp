//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "Symbol.h"
//******************************************************************************
static const auto g_SystemProcessId = 4;
//******************************************************************************
cxSymbol::cxSymbol(ULONGLONG Address, ULONG ProcessId, ULONGLONG Time)
{
	m_Address = Address;

	if (IsKernelAddress())
		ProcessId = g_SystemProcessId;

	cxMSGProcess* process = g_MSGProcessManager->GetProcess(ProcessId, Time);

	if (!process)
		return;

	cxMSGProcessModule* module = process->GetModule(Address, Time);

	if (!module)
		return;

	m_ModulePath = module->m_Path;
	m_ModuleName = module->m_Name;
	m_ModuleBase = module->m_BaseAddress;
	m_ModuleOffset = (ULONG)(Address - module->m_BaseAddress);
}
//******************************************************************************
CString cxSymbol::GetSymbol(void) const
{
	if (m_SymbolName.IsEmpty()) {
		if (m_ModuleName.IsEmpty())
			return CString();

		CString str;
		str.Format(_T("%s + 0x%X"), m_ModuleName, m_ModuleOffset);
		return str;
	}

	CString str;
	str.Format(_T("%s + 0x%X"), m_SymbolName, m_SymbolOffset);
	return str;
}
//******************************************************************************
bool cxSymbol::IsKernelAddress(void) const
{
#ifdef _M_X64
	if (m_Address >= 0xFF00000000000000)
		return true;
#else
	if (m_Address >= 0x80000000)
		return true;
#endif

	return false;
}
//******************************************************************************
