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
#include "ProcessModuleEnumerator.h"
//******************************************************************************
cxProcessModuleEnumerator::cxProcessModuleEnumerator(ULONG ProcessId)
{
	m_Snapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32,
		ProcessId);
}
//******************************************************************************
cxProcessModuleEnumerator::~cxProcessModuleEnumerator(void)
{
	if (m_Snapshot)
		CloseHandle(m_Snapshot);
}
//******************************************************************************
cxProcessModuleEnumerator::iterator cxProcessModuleEnumerator::begin(void)
{
	if (!Module32First(m_Snapshot, &m_Entry))
		return iterator();

	return this;
}
//******************************************************************************
cxProcessModuleEnumerator::iterator cxProcessModuleEnumerator::next(void)
{
	if (!Module32Next(m_Snapshot, &m_Entry))
		return iterator();

	return this;
}
//******************************************************************************
PMODULEENTRY32 cxProcessModuleEnumerator::operator->(void)
{
	return &m_Entry;
}
//******************************************************************************
