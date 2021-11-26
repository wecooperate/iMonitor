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
#include "MSGProcessModule.h"
//******************************************************************************
ULONG cxMSGProcessModule::GetOffset(ULONGLONG Address)
{
	if (m_BaseAddress == 0)
		return 0;

	return (ULONG)(Address - m_BaseAddress);
}
//******************************************************************************
cxMSGProcessModule::operator bool(void)
{
	return !m_Path.IsEmpty();
}
//******************************************************************************
