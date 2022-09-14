//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __atomic_66BC8E83_DD76_438C_BA67_DA6A44418D9E__
#define __atomic_66BC8E83_DD76_438C_BA67_DA6A44418D9E__
//******************************************************************************
#include <atomic>
//******************************************************************************
template<typename T>
class cxAtomic_ : public std::atomic<T>
{
	using atomic = std::atomic<T>;

public:
	using atomic::atomic;

public:
	cxAtomic_(const T Value = T())
		: atomic(Value)
	{
	}

public:
	template<typename P>
	cxAtomic_& operator=(const P& Target)
	{
		atomic::operator=(Target);
		return *this;
	}

public:
	bool CompareAndSetValue(T Compare, T Value)
	{
		return atomic::compare_exchange_strong(Compare, Value);
	}
};
//******************************************************************************
typedef cxAtomic_<uint32_t> cxAtomic;
typedef cxAtomic_<bool> cxAtomicBool;
//******************************************************************************
#endif
