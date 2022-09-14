//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __iterator_154235a9_5fec_44dc_9b04_6175ee804d40__
#define __iterator_154235a9_5fec_44dc_9b04_6175ee804d40__
//******************************************************************************
template<typename T>
class iterator_
{
public:
	iterator_(T* ptr = nullptr)
		: m_ptr(ptr)
	{
	}

	const iterator_& operator=(T* ptr)
	{
		m_ptr = ptr;
		return *this;
	}

	const iterator_& operator++(void)
	{
		*this = m_ptr->next();
		return *this;
	}

	bool operator!=(const iterator_<T>& it)
	{
		return m_ptr != it.m_ptr;
	}

	bool operator==(const iterator_<T>& it)
	{
		return m_ptr == it.m_ptr;
	}

	T& operator*(void)
	{
		return *m_ptr;
	}

	T* operator->(void)
	{
		return m_ptr;
	}

private:
	T* m_ptr;
};
//******************************************************************************
template<typename T>
class cxIterator_ : public cxSafeObject
{
public:
	typedef iterator_<T> iterator;

public:
	inline iterator begin(void) { return iterator(); }
	inline iterator end(void) { return iterator(); }
	inline iterator next(void) { return iterator(); }

public:
	operator iterator(void) { return iterator(static_cast<T*>(this)); }
};
//******************************************************************************
template<typename T>
using cxEnumerator_ = cxIterator_<T>;
//******************************************************************************
#endif
