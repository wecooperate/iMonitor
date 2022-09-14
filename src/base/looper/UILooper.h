//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __UILooper_F4DF1D15_61DD_4F91_9564_155FA9D153B5__
#define __UILooper_F4DF1D15_61DD_4F91_9564_155FA9D153B5__
//******************************************************************************
#include "Looper.h"
//******************************************************************************
class cxUILooper : public cxLooper
{
public:
	uint32_t GetType(void) override;
	void WakeUp(void) override;
	void Terminate(void) override;
	void OnWork(void) override;

protected:
	HWND CreateMSGWindow(void);
	void OnMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	void DoDispatchTask();

protected:
	HWND m_hWnd = nullptr;
};
//******************************************************************************
class cxUIMainLooper : public cxUILooper
{
public:
	~cxUIMainLooper(void);

public:
	void Start(void);
};
//******************************************************************************
#endif
