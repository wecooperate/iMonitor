//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "UIMain.h"
#include "ui_UIMain.h"
#include "View/UIMessageView.h"
#include "View/StatusBar/UIStatusBar.h"
#include "View/Filter/UIFilterBar.h"
#include <QFileDialog>
#include <QDateTime>
#include <QShortcut>
#include <QDesktopServices>
#include <QMessageBox>
//******************************************************************************
UIMain::UIMain(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::UIMain)
{
	ui->setupUi(this);
	ui->toolBarFilter->addWidget(new UIFilterBar());
	setStatusBar(new UIStatusBar(this));
	m_ToolBar.Initalize(ui->toolBar);
	setCentralWidget(m_MessageView = new UIMessageView(this));
	setWindowIcon(g_res->icon_main);

	LoadConfig();
	LoadStyleSheet();

#ifdef DEBUG
	QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_F5), this);
	connect(shortcut, &QShortcut::activated, [this]() {
		LoadStyleSheet();
	});
#endif

	HandleEvent([this](ServiceEventError& err) {
		QString title = this->windowTitle();
		if (err.Message) {
			title = err.Message;
		}
		QMessageBox::critical(this, title, QStringFrom(StringFromError(err.Error, 0)), QMessageBox::Ok);
		ExitProcess(err.Error);
	});

	if (g_Config->IsEnableCapture) {
		GetMessageService()->StartCapture();
	}
}
//******************************************************************************
void UIMain::LoadConfig(void)
{
	g_Config->LoadConfig(GetConfigService());

	ui->action_Monitor->setChecked(g_Config->IsEnableCapture);
	ui->action_AutoScroll->setChecked(g_Config->IsEnableAutoScroll);
	ui->action_Colorful->setChecked(g_Config->IsEnableColorful);

	ui->action_Open->setDisabled(true);
	ui->action_Save->setDisabled(true);

	m_ToolBar.LoadConfig();
}
//******************************************************************************
void UIMain::SaveConfig(void)
{
	g_Config->SaveConfig(GetConfigService());
}
//******************************************************************************
void UIMain::LoadStyleSheet(void)
{
	QString path_qss = ":/res/qss/default.css";
	QString path_file = QApplication::applicationDirPath() + "/main.css";

	if (PathFileExists(QStringToCString(path_file))) {
		path_qss = path_file;
	}

	QFile file(path_qss);

	if (file.open(QFile::ReadOnly)) {
		QString qss = QLatin1String(file.readAll());
		qApp->setStyleSheet(qss);
		file.close();
	}
}
//******************************************************************************
void UIMain::closeEvent(QCloseEvent* event)
{
	SaveConfig();

	m_MessageView->close();
	delete m_MessageView;
	m_MessageView = nullptr;

	g_UIManager->Uninitialize();
}
//******************************************************************************
void UIMain::on_action_Monitor_triggered(bool checked)
{
	checked ? GetMessageService()->StartCapture() : GetMessageService()->StopCapture();
}
//******************************************************************************
void UIMain::on_action_AutoScroll_triggered(bool checked)
{
	g_Config->IsEnableAutoScroll = checked;

	if (checked) {
		m_MessageView->scrollToBottom();
	}
}
//******************************************************************************
void UIMain::on_action_Clear_triggered()
{
	GetMessageService()->RemoveAllItems();

	FireEvent(emServiceEventMSGClear);
}
//******************************************************************************
void UIMain::on_action_Locate_triggered()
{
	UIMSGIndex msg(m_MessageView);

	if (!msg)
		return;

	g_PathLocate->Locate(msg->GetLocatePath());
}
//******************************************************************************
void UIMain::on_action_Colorful_triggered(bool checked)
{
	g_Config->IsEnableColorful = checked;
}
//******************************************************************************
void UIMain::on_action_Save_triggered()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_time = current_date_time.toString("yyyy_MM_dd_hhmm");

	QString file_name = QFileDialog::getSaveFileName(this,
		tr("Save"),
		current_time,
		tr("iMonitor Files (*.imt)"));

	if (file_name.isEmpty())
		return;

	// TODO
}
//******************************************************************************
void UIMain::on_action_Exit_triggered()
{
	ExitProcess(ERROR_SUCCESS);
}
//******************************************************************************
void UIMain::on_action_Setting_triggered()
{
	g_UIManager->Show(SCHEME_SETTING_VIEW, true);
}
//******************************************************************************
void UIMain::on_action_About_triggered()
{
	QDesktopServices::openUrl(QUrl("https://github.com/wecooperate/iMonitor"));
}
//******************************************************************************
void UIMain::on_action_UniqueMessage_triggered(bool checked)
{
	g_Config->SetIsUniqueMessage(checked);

	if (checked) {
		GetMessageService()->RemoveAllItems();
	}
}
//******************************************************************************
