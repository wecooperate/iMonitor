//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __lock_b796c51e_9af0_4d39_8788_a310f726f5a8__
#define __lock_b796c51e_9af0_4d39_8788_a310f726f5a8__
//******************************************************************************
#include <mutex>
//******************************************************************************
class cxNoLock
{
public:
	void Lock() {}
	void Unlock() {}
};
//******************************************************************************
class cxLock
{
public:
	void Lock()
	{
		m_lock.lock();
	}

	void Unlock()
	{
		m_lock.unlock();
	}

	bool TryLock()
	{
		return m_lock.try_lock();
	}

private:
	std::recursive_mutex m_lock;
};
//******************************************************************************
class cxAtomicLock
{
public:
	void Lock()
	{
		while (m_lock.test_and_set()) {
			std::this_thread::yield();
		}
	}

	void Unlock()
	{
		m_lock.clear();
	}

private:
	std::atomic_flag m_lock = ATOMIC_FLAG_INIT;
};
//******************************************************************************
template<typename T>
class cxAutoLock_
{
public:
	explicit cxAutoLock_(T& lock)
		: m_lock(lock)
	{
		m_lock.Lock();
	}

	~cxAutoLock_()
	{
		m_lock.Unlock();
	}

private:
	T& m_lock;
};
//******************************************************************************
#define AUTO_LOCK(x) cxAutoLock_<decltype(x)> CONCAT(lock_at_line_, __LINE__)(x)
//******************************************************************************
#endif
