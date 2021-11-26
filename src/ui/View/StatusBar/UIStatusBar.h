//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIStatusBar_A308C7A4_0D98_44F8_B85A_22ADAACD1ECE__
#define __UIStatusBar_A308C7A4_0D98_44F8_B85A_22ADAACD1ECE__
//******************************************************************************
class UIStatusBar
	: public QStatusBar
	, public UIServiceClient
{
	Q_OBJECT

public:
	UIStatusBar(QWidget* parent = nullptr);

protected:
	void OnUpdate(const ServiceEventMSGUpdate& event);

protected:
	QLabel* m_LabelMSGCount = nullptr;
};
//******************************************************************************
#endif
