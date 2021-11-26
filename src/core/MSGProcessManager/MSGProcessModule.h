//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#pragma once
//******************************************************************************
class cxMSGProcessModule
{
public:
	ULONG GetOffset(ULONGLONG Address);

public:
	operator bool(void);

public:
	CString m_Path;
	CString m_Name;
	ULONGLONG m_BaseAddress = 0;
	ULONGLONG m_Size = 0;
	ULONGLONG m_LoadTime = 0;
};
//******************************************************************************
