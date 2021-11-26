//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __MSGStatus_H__
#define __MSGStatus_H__
//******************************************************************************
class cxMSGStatus
{
#define g_MSGStatus SINGLETON_(cxMSGStatus)

public:
	CString GetString(ULONG Status);
	CString GetErrorString(ULONG Status);
};
//******************************************************************************
#endif
