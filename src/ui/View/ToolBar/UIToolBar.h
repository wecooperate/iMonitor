//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIToolBar_54B6C0DA_29D1_4BA8_ABEC_DD44C2C69546__
#define __UIToolBar_54B6C0DA_29D1_4BA8_ABEC_DD44C2C69546__
//******************************************************************************
class UIToolBar
	: public QObject
	, public UIServiceClient
{
	Q_OBJECT

public:
	void Initalize(QToolBar* toolbar);
	void LoadConfig(void);

protected:
	QAction* CreateSwitchAction(int Group);

protected:
	QToolBar* m_ToolBar;

protected:
	QAction* action_Colorful = nullptr;
	QAction* action_SwitchProcess = nullptr;
	QAction* action_SwitchFile = nullptr;
	QAction* action_SwitchRegistry = nullptr;
	QAction* action_SwitchNetwork = nullptr;
};
//******************************************************************************
#endif
