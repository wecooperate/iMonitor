//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __ProcessEnumerator_H__
#define __ProcessEnumerator_H__
//******************************************************************************
#include <TlHelp32.h>
//******************************************************************************
class cxProcessEnumerator : public cxEnumerator_<cxProcessEnumerator>
{
public:
	cxProcessEnumerator			(void);
	~cxProcessEnumerator		(void);

public:
	iterator		begin		(void);
	iterator		next		(void);

public:
	PPROCESSENTRY32 operator->	(void);
	PPROCESSENTRY32 operator&	(void);

private:
	HANDLE			m_Snapshot	= NULL;
	PROCESSENTRY32	m_Entry		= {sizeof(m_Entry)};
};
//******************************************************************************
class cxProcessInternalEnumerator : public cxEnumerator_<cxProcessInternalEnumerator>
{
public:
	cxProcessInternalEnumerator	(void);
	~cxProcessInternalEnumerator(void);

public:
	iterator		begin		(void);
	iterator		next		(void);

public:
	PSYSTEM_PROCESS_INFORMATION operator->		(void);
	PSYSTEM_PROCESS_INFORMATION operator&		(void);

private:
	PSYSTEM_PROCESS_INFORMATION	m_Information	= NULL;
	PSYSTEM_PROCESS_INFORMATION	m_Ptr			= NULL;
};
//******************************************************************************
#endif
