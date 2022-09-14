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
#include "ProcessEnumerator.h"
//******************************************************************************
cxProcessEnumerator::cxProcessEnumerator(void)
{
	m_Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
}
//******************************************************************************
cxProcessEnumerator::~cxProcessEnumerator(void)
{
	if (m_Snapshot)
		CloseHandle(m_Snapshot);
}
//******************************************************************************
cxProcessEnumerator::iterator cxProcessEnumerator::begin(void)
{
	if (!m_Snapshot)
		return iterator();

	if (!Process32First(m_Snapshot, &m_Entry))
		return iterator();

	return this;
}
//******************************************************************************
cxProcessEnumerator::iterator cxProcessEnumerator::next(void)
{
	if (!Process32Next(m_Snapshot, &m_Entry))
		return iterator();

	return this;
}
//******************************************************************************
PPROCESSENTRY32 cxProcessEnumerator::operator->(void)
{
	return &m_Entry;
}
//******************************************************************************
PPROCESSENTRY32 cxProcessEnumerator::operator&(void)
{
	return &m_Entry;
}
//******************************************************************************
cxProcessInternalEnumerator::cxProcessInternalEnumerator(void)
{
	for (int i = 0; i < 4; i++) {
		ULONG len = 0;

		NTSTATUS status = mod_ntdll::ZwQuerySystemInformation(
			SystemProcessInformation,
			m_Information,
			len,
			&len);

		if (status != STATUS_INFO_LENGTH_MISMATCH || len == 0)
			break;

		m_Information = (PSYSTEM_PROCESS_INFORMATION) new char[len];

		status = mod_ntdll::ZwQuerySystemInformation(
			SystemProcessInformation,
			m_Information,
			len,
			&len);

		if (STATUS_SUCCESS == status)
			break;

		delete[](char*) m_Information;

		m_Information = NULL;
	}
}
//******************************************************************************
cxProcessInternalEnumerator::~cxProcessInternalEnumerator(void)
{
	if (m_Information)
		delete[](char*) m_Information;
}
//******************************************************************************
cxProcessInternalEnumerator::iterator cxProcessInternalEnumerator::begin(void)
{
	if (!m_Information)
		return iterator();

	m_Ptr = m_Information;

	return this;
}
//******************************************************************************
cxProcessInternalEnumerator::iterator cxProcessInternalEnumerator::next(void)
{
	if (!m_Ptr || !m_Ptr->NextEntryOffset)
		return iterator();

	m_Ptr = (PSYSTEM_PROCESS_INFORMATION)((ULONG_PTR)m_Ptr + m_Ptr->NextEntryOffset);

	return this;
}
//******************************************************************************
PSYSTEM_PROCESS_INFORMATION cxProcessInternalEnumerator::operator->(void)
{
	return m_Ptr;
}
//******************************************************************************
PSYSTEM_PROCESS_INFORMATION cxProcessInternalEnumerator::operator&(void)
{
	return m_Ptr;
}
//******************************************************************************
