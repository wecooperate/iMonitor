//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __Looper_DBC2F446_56DF_4A0E_BB58_D6F3F62BB358__
#define __Looper_DBC2F446_56DF_4A0E_BB58_D6F3F62BB358__
//******************************************************************************
// clang-format off
//******************************************************************************
#include <functional>
//******************************************************************************
typedef std::function<void()> Runnable;
//******************************************************************************
interface ILooper
{
	enum LooperType {
		kEventLooper,
		kUILooper,
		kIOLooper,
		kASIOLooper,
		kUVLooper,
	};

	enum {
		kDelayTimeInterval = -1,
		kDelayTimeImmediate = 0,
	};

	virtual				~ILooper			(void) = default;

	virtual uint32_t	GetType				(void) = 0;
	virtual uint32_t	PostRunnable		(Runnable Callback, uint32_t msDelayTime = kDelayTimeImmediate) = 0;
	virtual uint32_t	RunOrPostRunnable	(Runnable Callback) = 0;
	virtual uint32_t	SetTimer			(Runnable Callback, uint32_t msInterval, uint32_t msDelayTime = kDelayTimeInterval) = 0;
	virtual void		ResetTimer			(uint32_t Id, uint32_t msInterval, uint32_t msDelayTime = kDelayTimeInterval) = 0;
	virtual void		Cancel				(uint32_t Id) = 0;
	virtual void		CancelAll			(void) = 0;
};
//******************************************************************************
class cxLooper : public ILooper
{
public:
	struct cxRunnableTask {
		Runnable	Callback;
		uint32_t	Id;
		uint32_t	Interval;
		uint64_t	NextTime;
	};

	typedef std::shared_ptr<cxRunnableTask> RunnableTask;

public:
	~cxLooper (void) override;

public:
	void				SetName				(std::string_view Name);
	std::string			GetName				(void);

public:
	uint32_t			PostRunnable		(Runnable Callback, uint32_t msDelayTime = kDelayTimeImmediate) override;
	uint32_t			RunOrPostRunnable	(Runnable Callback) override;
	uint32_t			SetTimer			(Runnable Callback, uint32_t msInterval, uint32_t msDelayTime = kDelayTimeInterval) override;
	void				ResetTimer			(uint32_t Id, uint32_t msInterval, uint32_t msDelayTime = kDelayTimeInterval) override;
	void				Cancel				(uint32_t Id) override;
	void				CancelAll			(void) override;

public:
	virtual void		OnWork				(void) = 0;
	virtual void		WakeUp				(void) = 0;
	virtual void		Terminate			(void);
	virtual bool		IsTerminated		(void);
	virtual void		Run					(void);

protected:
	void				InsertTask			(cxRunnableTask&& Task);
	void				DispatchTask		(void);

protected:
	uint32_t			GetNextDelayTime	(void);

protected:
	bool				m_IsTerminated		= false;
	std::string			m_Name;
	cxLock				m_Lock;
	cxAtomic			m_TaskIndex;
	std::list<RunnableTask> m_Tasks;
};
//******************************************************************************
class cxLooperThread
{
public:
	cxLooperThread(cxLooper* looper);
	~cxLooperThread(void);

public:
	bool				Start				(std::string_view name);
	void				Stop				(bool wait = true);
	uint32_t			Wait				(uint32_t msTimeout = INFINITE);

protected:
	void				WaitForThreadExit	(void);

protected:
	std::thread			m_Thread;
	cxLooper*			m_Looper;
};
//******************************************************************************
template<typename T>
class cxLooperThread_ : public T
	, public cxLooperThread
{
public:
	cxLooperThread_()
		: cxLooperThread(this)
	{
	}
};
//******************************************************************************
#endif
