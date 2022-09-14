//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __handle_904dcdaa_0802_4d47_974b_7564ba02e9ce__
#define __handle_904dcdaa_0802_4d47_974b_7564ba02e9ce__
//******************************************************************************
template<typename T, void (*TCloseHandle)(T)>
class cxHandle_ : public cxSafeObject
{
public:
	inline cxHandle_(const T Handle = NULL)
		: m_Handle(Handle)
	{
	}

	inline ~cxHandle_(void)
	{
		Close();
	}

public:
	inline cxHandle_(cxHandle_&& Target)
	{
		m_Handle = Target.m_Handle;
		Target.m_Handle = NULL;
	}

	inline const cxHandle_& operator=(cxHandle_&& Target)
	{
		Attach(Target.Detach());
		return *this;
	}

public:
	inline const cxHandle_& operator=(T Handle)
	{
		Attach(Handle);
		return *this;
	}

	inline operator T(void)
	{
		return m_Handle;
	}

	inline operator bool(void)
	{
		if (m_Handle == NULL)
			return false;

		if (m_Handle == (T)-1)
			return false;

		return true;
	}

public:
	inline void Attach(T Handle)
	{
		Close();
		m_Handle = Handle;
	}

	inline T Detach(void)
	{
		T tmp = m_Handle;
		m_Handle = NULL;
		return tmp;
	}

	inline void Close(void)
	{
		if (operator bool()) {
			TCloseHandle(m_Handle);
			m_Handle = NULL;
		}
	}

protected:
	T m_Handle = NULL;
};
//******************************************************************************
#if OS_WIN
//******************************************************************************
struct GlobalCloseHandle
{
	inline static void CloseHandle(HANDLE Handle) { ::CloseHandle(Handle); }
	inline static void CloseServiceHandle(SC_HANDLE Handle) { ::CloseServiceHandle(Handle); }
};
//******************************************************************************
typedef cxHandle_<HANDLE, GlobalCloseHandle::CloseHandle> cxHandle;
typedef cxHandle_<SC_HANDLE, GlobalCloseHandle::CloseServiceHandle> cxServiceHandle;
//******************************************************************************
#endif // OS_WIN
//******************************************************************************
#endif
