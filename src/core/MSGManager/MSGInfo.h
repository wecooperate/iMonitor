//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __MSGInfo_H__
#define __MSGInfo_H__
//******************************************************************************
#include <iMonitor.h>
#include <iMonitorUIMessage.h>
//******************************************************************************
class cxMSGInfoManager
{
#define g_MSGInfo SINGLETON_(cxMSGInfoManager)

public:
	using cxMSGInfo = proto::MSGInfo;

	struct cxMSGCommonInfo
	{
		ULONG Index;
		ULONG Type;
		LPCWSTR Name;
	};

public:
	cxMSGInfoManager();

public:
	cxMSGInfo GetMSGInfo(ULONG Type);
	const std::list<cxMSGCommonInfo>& GetMSGCommonInfo(void);

public:
	CString GetName(ULONG Type);
	CString GetGroupName(ULONG Group);
	ULONG GetFieldIndex(ULONG Type, LPCWSTR Name);
	CString GetFieldName(ULONG Type, ULONG Index);
	bool IsFieldNumber(ULONG Type, ULONG Index);
	CString GetCommonFieldName(ULONG Index);

private:
	std::map<ULONG, cxMSGInfo> m_Infos;
	std::list<cxMSGCommonInfo> m_CommonInfos;
};
//******************************************************************************
#endif
