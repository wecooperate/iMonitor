//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "LooperManager.h"
#include "UILooper.h"
//******************************************************************************
template<typename T>
class cxThreadLocalStorage
{
public:
	cxThreadLocalStorage(void)
	{
		m_Index = TlsAlloc();
	}

	inline T* Get(void)
	{
		return reinterpret_cast<T*>(TlsGetValue(m_Index));
	}

	inline bool Set(T* Value)
	{
		return TlsSetValue(m_Index, Value);
	}

protected:
	DWORD m_Index = -1;
};
//******************************************************************************
static cxThreadLocalStorage<ILooper> g_LooperLocalStorage;
//******************************************************************************
template<typename T>
std::shared_ptr<ILooper> DoCreateLooper(std::string_view Name)
{
	auto looper = std::make_shared<cxLooperThread_<T>>();
	looper->Start(Name);
	return looper;
}
//******************************************************************************
void cxLooperManager::Start(void)
{
	auto looper = std::make_shared<cxUIMainLooper>();
	looper->Start();
	m_MainLooper = looper;
}
//******************************************************************************
std::shared_ptr<ILooper> cxLooperManager::GetMainLooper(void)
{
	return m_MainLooper;
}
//******************************************************************************
std::shared_ptr<ILooper> cxLooperManager::CreateLooper(ILooper::LooperType Type, std::string_view Name)
{
	switch (Type) {
	case ILooper::kUILooper:
		return DoCreateLooper<cxUILooper>(Name);

	default:
		DCHECK(!"invalid looper type");
		return nullptr;
	}
}
//******************************************************************************
bool cxLooperManager::IsCurrent(ILooper* looper)
{
	return g_LooperLocalStorage.Get() == looper;
}
//******************************************************************************
void cxLooperManager::SetCurrent(ILooper* looper)
{
	g_LooperLocalStorage.Set(looper);
}
//******************************************************************************
ILooper* cxLooperManager::Current(void)
{
	return g_LooperLocalStorage.Get();
}
//******************************************************************************
