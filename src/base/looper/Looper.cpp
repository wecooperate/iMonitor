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
#include "Looper.h"
#include "LooperManager.h"
//******************************************************************************
cxLooper::~cxLooper(void)
{
	m_IsTerminated = true;

	CancelAll();
}
//******************************************************************************
void cxLooper::SetName(std::string_view Name)
{
	m_Name = Name;
}
//******************************************************************************
std::string cxLooper::GetName(void)
{
	return m_Name;
}
//******************************************************************************
uint32_t cxLooper::PostRunnable(Runnable Callback, uint32_t msDelayTime)
{
	AUTO_LOCK(m_Lock);

	cxRunnableTask task;
	task.Callback = std::move(Callback);
	task.Id = ++m_TaskIndex;
	task.Interval = 0;
	task.NextTime = GetCurrentTickCount() + msDelayTime;
	auto id = task.Id;
	InsertTask(std::move(task));

	return id;
}
//******************************************************************************
uint32_t cxLooper::RunOrPostRunnable(Runnable Callback)
{
	if (g_Looper->IsCurrent(this)) {
		Callback();
		return 0;
	}

	return PostRunnable(std::move(Callback));
}
//******************************************************************************
uint32_t cxLooper::SetTimer(Runnable Callback, uint32_t msInterval, uint32_t msDelayTime)
{
	if (msDelayTime == kDelayTimeInterval) {
		msDelayTime = msInterval;
	}

	AUTO_LOCK(m_Lock);

	cxRunnableTask task;
	task.Callback = std::move(Callback);
	task.Id = ++m_TaskIndex;
	task.Interval = msInterval;
	task.NextTime = GetCurrentTickCount() + msDelayTime;
	auto id = task.Id;
	InsertTask(std::move(task));

	return id;
}
//******************************************************************************
void cxLooper::ResetTimer(uint32_t TaskId, uint32_t msInterval, uint32_t msDelayTime)
{
	if (msDelayTime == kDelayTimeInterval) {
		msDelayTime = msInterval;
	}

	AUTO_LOCK(m_Lock);

	for (auto it = m_Tasks.begin(); it != m_Tasks.end(); ++it) {
		auto task = *it;
		if (task->Id == TaskId) {
			task->Interval = msInterval;
			task->NextTime = GetCurrentTickCount() + msDelayTime;
			break;
		}
	}
}
//******************************************************************************
void cxLooper::Cancel(uint32_t TaskId)
{
	AUTO_LOCK(m_Lock);

	for (auto it = m_Tasks.begin(); it != m_Tasks.end(); ++it) {
		auto task = *it;
		if (task->Id == TaskId) {
			m_Tasks.erase(it);
			break;
		}
	}
}
//******************************************************************************
void cxLooper::CancelAll(void)
{
	AUTO_LOCK(m_Lock);

	m_Tasks.clear();
}
//******************************************************************************
void cxLooper::Terminate(void)
{
	if (m_IsTerminated)
		return;

	m_IsTerminated = true;

	WakeUp();

	CancelAll();
}
//******************************************************************************
bool cxLooper::IsTerminated(void)
{
	return m_IsTerminated;
}
//******************************************************************************
void cxLooper::Run()
{
	CoInitialize(nullptr);
	g_Looper->SetCurrent(this);
	OnWork();
	g_Looper->SetCurrent(nullptr);
	CoUninitialize();
}
//******************************************************************************
void cxLooper::InsertTask(cxRunnableTask&& Task)
{
	m_Tasks.emplace_back(std::make_shared<cxRunnableTask>(std::move(Task)));

	WakeUp();
}
//******************************************************************************
uint32_t cxLooper::GetNextDelayTime(void)
{
	AUTO_LOCK(m_Lock);

	uint64_t cur_time = GetCurrentTickCount();

	uint32_t next_delay_time = -1;

	for (auto it = m_Tasks.begin(); it != m_Tasks.end(); ++it) {
		auto task = *it;

		if (task->NextTime == 0)
			continue;

		if (task->NextTime < cur_time) {
			next_delay_time = 0;
			break;
		}

		uint32_t delay_time = task->NextTime - cur_time;

		if (delay_time < next_delay_time)
			next_delay_time = delay_time;
	}

	return next_delay_time;
}
//******************************************************************************
void cxLooper::DispatchTask(void)
{
	std::list<RunnableTask> tasks;

	{
		AUTO_LOCK(m_Lock);

		uint64_t cur_time = GetCurrentTickCount();

		for (auto it = m_Tasks.begin(); it != m_Tasks.end();) {
			auto task = *it;

			if (task->NextTime > cur_time) {
				it++;
				continue;
			}

			tasks.push_back(task);

			if (task->Interval == 0)
				it = m_Tasks.erase(it);
			else {
				task->NextTime = task->Interval + cur_time;
				it++;
			}
		}
	}

	for (auto& it : tasks)
		it->Callback();
}
//******************************************************************************
cxLooperThread::cxLooperThread(cxLooper* looper)
	: m_Looper(looper)
{
}
//******************************************************************************
cxLooperThread::~cxLooperThread(void)
{
	Stop();
}
//******************************************************************************
#if OS_WIN
static void SetThreadName(LPCSTR Name, DWORD ThreadId = GetCurrentThreadId())
{
	const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push, 8)
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType;	  // Must be 0x1000.
		LPCSTR szName;	  // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags;	  // Reserved for future use, must be zero.
	} THREADNAME_INFO;
#pragma pack(pop)

	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = Name;
	info.dwThreadID = ThreadId;
	info.dwFlags = 0;

	__try {
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}
}
#endif
//******************************************************************************
bool cxLooperThread::Start(std::string_view name)
{
	m_Looper->SetName(name);

	m_Thread = std::thread([this]() {
		SetThreadName(m_Looper->GetName().c_str());
		m_Looper->Run();
	});

	return true;
}
//******************************************************************************
void cxLooperThread::Stop(bool wait)
{
	if (m_Looper->IsTerminated()) {
		if (wait) {
			WaitForThreadExit();
		}
		return;
	}

	m_Looper->Terminate();
	if (wait) {
		WaitForThreadExit();
	}
	m_Looper->CancelAll();
}
//******************************************************************************
uint32_t cxLooperThread::Wait(uint32_t msTimeout)
{
	return WaitForSingleObject(m_Thread.native_handle(), msTimeout);
}
//******************************************************************************
void cxLooperThread::WaitForThreadExit()
{
	if (m_Thread.joinable()) {
		try {
			m_Thread.join();
		} catch (...) {
		}
	}
}
//******************************************************************************
