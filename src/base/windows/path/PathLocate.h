//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __PathLocate_H__
#define __PathLocate_H__
//******************************************************************************
// clang-format off
//******************************************************************************
class cxPathLocate
{
#define	g_PathLocate SINGLETON_(cxPathLocate)

public:
	HRESULT		Locate			(LPCTSTR Path);
	HRESULT		LocateFile		(LPCTSTR Path);
	HRESULT		LocateRegistry	(LPCTSTR Path);
};
//******************************************************************************
#endif
