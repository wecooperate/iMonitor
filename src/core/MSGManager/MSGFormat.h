//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __MSGFormat_H__
#define __MSGFormat_H__
//******************************************************************************
class cxMSGFormat
{
#define g_MSGFormat SINGLETON_(cxMSGFormat)

public:
	CString Format(ULONGLONG Data, ULONG Type);
	CString FormatULONG(ULONG Data, ULONG Type);
	CString FormatULONGLONG(ULONGLONG Data, ULONG Type);

	CString FormatInteger(ULONG Data);
	CString FormatAddress(ULONG Data);
	CString FormatAddress(ULONGLONG Data);
	CString FormatDateTime(ULONGLONG Data);
};
//******************************************************************************
#endif
