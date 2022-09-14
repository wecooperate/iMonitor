//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __WOW64_H__
#define __WOW64_H__
//******************************************************************************
class cxWOW64
{
#define g_WOW64 SINGLETON_(cxWOW64)

public:
	bool IsWOW64Process(void);
	bool IsWOW64Process(HANDLE ProcessHandle);

	void* DisableFileRedirection(void);
	void RevertFileRedirection(void* OldValue);
	void EnableFileRedirection(void);
};
//******************************************************************************
class WOW64AutoDisableFileRedirection
{
public:
	WOW64AutoDisableFileRedirection()
	{
		m_OldValue = g_WOW64->DisableFileRedirection();
	}

	~WOW64AutoDisableFileRedirection()
	{
		g_WOW64->RevertFileRedirection(m_OldValue);
	}

private:
	PVOID m_OldValue;
};
//******************************************************************************
#endif
