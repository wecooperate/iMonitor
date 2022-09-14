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
#include "UILooper.h"
//******************************************************************************
#define TIMER_WAKEUP_ID	  WM_USER + 1
#define MESSAGE_WAKEUP_ID WM_USER + 1
//******************************************************************************
uint32_t cxUILooper::GetType(void)
{
	return kUILooper;
}
//******************************************************************************
void cxUILooper::WakeUp(void)
{
	if (!m_hWnd)
		return;

	if (!::SetTimer(m_hWnd, TIMER_WAKEUP_ID, 0, nullptr)) {
		PostMessage(m_hWnd, MESSAGE_WAKEUP_ID, 0, 0);
	}
}
//******************************************************************************
void cxUILooper::Terminate(void)
{
	__super::Terminate();

	if (m_hWnd) {
		PostMessage(m_hWnd, WM_QUIT, 0, 0);
	}
}
//******************************************************************************
void cxUILooper::OnWork(void)
{
	m_hWnd = CreateMSGWindow();

	WakeUp();

	MSG msg = {};

	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (msg.message == WM_QUIT) {
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DestroyWindow(m_hWnd);

	m_hWnd = nullptr;
}
//******************************************************************************
HWND cxUILooper::CreateMSGWindow(void)
{
	struct stub
	{
		static LRESULT CALLBACK WindowProc(
			HWND hWnd,
			UINT msg,
			WPARAM wParam,
			LPARAM lParam)
		{
			cxUILooper* task_mgr = g_Looper->Current<cxUILooper>();

			if (task_mgr) {
				task_mgr->OnMessage(msg, wParam, lParam);
			}

			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	};

	WNDCLASSEX window_class = {};
	window_class.cbSize = sizeof(window_class);
	window_class.style = 0;
	window_class.lpfnWndProc = stub::WindowProc;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = nullptr;
	window_class.hIcon = nullptr;
	window_class.hCursor = nullptr;
	window_class.hbrBackground = nullptr;
	window_class.lpszMenuName = nullptr;
	window_class.lpszClassName = _T("UITask");
	window_class.hIconSm = nullptr;

	ATOM atom = RegisterClassEx(&window_class);

	return CreateWindow(
		window_class.lpszClassName,
		nullptr,
		0,
		0,
		0,
		0,
		0,
		nullptr,
		nullptr,
		nullptr,
		this);
}
//******************************************************************************
void cxUILooper::OnMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_TIMER:
		if (wParam == TIMER_WAKEUP_ID) {
			KillTimer(m_hWnd, TIMER_WAKEUP_ID);
			DoDispatchTask();
		}
		break;

	case MESSAGE_WAKEUP_ID:
		DoDispatchTask();
		break;

	default:
		break;
	}
}
//******************************************************************************
void cxUILooper::DoDispatchTask()
{
	DispatchTask();

	::SetTimer(m_hWnd, TIMER_WAKEUP_ID, GetNextDelayTime(), nullptr);
}
//******************************************************************************
cxUIMainLooper::~cxUIMainLooper(void)
{
	if (m_hWnd) {
		DestroyWindow(m_hWnd);
		m_hWnd = nullptr;
	}
}
//******************************************************************************
void cxUIMainLooper::Start(void)
{
	CoInitialize(nullptr);

	g_Looper->SetCurrent(this);

	m_hWnd = CreateMSGWindow();
}
//******************************************************************************
