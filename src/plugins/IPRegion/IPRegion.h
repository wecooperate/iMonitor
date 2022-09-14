//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __IPRegion_h_977e561b_53e6_46f5_883e_a206b24077e0__
#define __IPRegion_h_977e561b_53e6_46f5_883e_a206b24077e0__
//******************************************************************************
class cxIPRegion
{
#define g_IPRegion SINGLETON_(cxIPRegion)

public:
	cxIPRegion(void);

public:
	CString GetIPRegion(ULONG IP);

private:
	cxLock m_Lock;
	std::map<ULONG, CString> m_IPCaches;
};
//******************************************************************************
#endif
