//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __LooperManager_F716FB72_6B6A_4482_859B_58A87C24C0DE__
#define __LooperManager_F716FB72_6B6A_4482_859B_58A87C24C0DE__
//******************************************************************************
#include "Looper.h"
//******************************************************************************
class cxLooperManager
{
#define g_Looper	 SINGLETON_(cxLooperManager)
#define g_MainLooper g_Looper->GetMainLooper()

public:
	void Start(void);
	std::shared_ptr<ILooper> GetMainLooper(void);

public:
	std::shared_ptr<ILooper> CreateLooper(ILooper::LooperType Type, std::string_view Name);

public:
	bool IsCurrent(ILooper* looper);
	void SetCurrent(ILooper* looper);
	ILooper* Current(void);

public:
	template<typename T>
	T* Current(void)
	{
		return reinterpret_cast<T*>(Current());
	}

private:
	std::shared_ptr<ILooper> m_MainLooper;
};
//******************************************************************************
#endif
