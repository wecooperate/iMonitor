//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __PathTransfer_H__
#define __PathTransfer_H__
//******************************************************************************
// clang-format off
//******************************************************************************
class cxPathTransfer
{
#define g_PathTransfer SINGLETON_(cxPathTransfer)

public:
	cxPathTransfer					(void);

public:
	CString		Transfer			(LPCTSTR Path);

public:
	void		ResetDevicePath		(void);
	void		AddPathPair			(LPCTSTR Prefix, LPCTSTR Transfer);

protected:
	void		AddDevicePath		(void);
	void		AddPath				(void);
	void		AddRegPath			(void);

private:
	struct cxPathPair
	{
		CString	Prefix;
		CString	Transfer;
	};

	cxLock							m_Lock;
	std::list<cxPathPair>			m_PathTable;
	std::list<cxPathPair>			m_DevicePathTable;
};
//******************************************************************************
#endif
