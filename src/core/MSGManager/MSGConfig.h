//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __MSGConfig_3199EB6B_246A_43E2_8FB3_142ECC49DD04__
#define __MSGConfig_3199EB6B_246A_43E2_8FB3_142ECC49DD04__
//******************************************************************************
#include "MSGInfo.h"
//******************************************************************************
enum emMSGGroup {
	emMSGGroupInternal = 0,
	emMSGGroupProcess = 1,
	emMSGGroupFile = 2,
	emMSGGroupRegistry = 3,
	emMSGGroupSocket = 4,
	emMSGGroupWFP = 5,
	emMSGGroupMax,
};
//******************************************************************************
#define MSG_GET_GROUP(type) (type / 100)
//******************************************************************************
struct cxMSGConfigItem
{
	ULONG Type;
	CString Name;
	bool Enable = true;

	ULONG Group(void) const
	{
		return MSG_GET_GROUP(Type);
	}
};
//******************************************************************************
class cxMSGConfig
{
#define g_MSGConfig SINGLETON_(cxMSGConfig)

public:
	cxMSGConfig(void);

public:
	bool IsEnable(ULONG Type);
	bool IsGroupEnable(ULONG GroupType);

public:
	void SetEnable(ULONG Type, bool Enable);
	void SetGroupEnable(ULONG GroupType, bool Enable);

public:
	const std::list<cxMSGConfigItem>& GetConfigItems(void);

public:
	bool m_Configs[emMSGMax];
	bool m_GroupConfigs[emMSGGroupMax];
	bool m_IsUniqueMessage = false;
};
//******************************************************************************
#endif
