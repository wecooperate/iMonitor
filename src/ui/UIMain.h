//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIMain_H__
#define __UIMain_H__
//******************************************************************************
#include "View/ToolBar/UIToolBar.h"
//******************************************************************************
namespace Ui {
class UIMain;
}
//******************************************************************************
class UIMain
	: public QMainWindow
	, public UIServiceClient
{
	Q_OBJECT

public:
	UIMain(QWidget* parent = nullptr);

public:
	void LoadConfig(void);
	void SaveConfig(void);

protected:
	void LoadStyleSheet(void);

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void on_action_Monitor_triggered(bool checked);
	void on_action_AutoScroll_triggered(bool checked);
	void on_action_Clear_triggered();
	void on_action_Locate_triggered();
	void on_action_Colorful_triggered(bool checked);
	void on_action_Save_triggered();
	void on_action_Exit_triggered();
	void on_action_Setting_triggered();
	void on_action_About_triggered();
	void on_action_UniqueMessage_triggered(bool checked);

protected:
	Ui::UIMain* ui = nullptr;
	QTreeView* m_MessageView = nullptr;
	UIToolBar m_ToolBar;
};
//******************************************************************************
#endif
