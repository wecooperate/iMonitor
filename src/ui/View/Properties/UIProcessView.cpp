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
#include "UIProcessView.h"
#include "ui_UIProcessView.h"
//******************************************************************************
static QColor g_WarningColor("#FFDAB9");
//******************************************************************************
enum emModuleColumn {
	emModuleColumnNumber,
	emModuleColumnName,
	emModuleColumnPath,
	emModuleColumnAddress,
	emModuleColumnSize,
	emModuleColumnCompanyName,
	emModuleColumnVersion,
	emModuleColumnDescription,
	emModuleColumnLoadTime,
	emModuleColumnMax,
};
//******************************************************************************
UIProcessView::UIProcessView(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::UIProcessView)
{
	ui->setupUi(this);
	ui->btnLocate->setIcon(g_res->icon_locate);

	auto view = ui->treeViewModule;

	UIInitTreeView(view);

	auto proxy_model = new UISortFilterProxyModel(this);
	proxy_model->setSourceModel(m_ModuleModel = new UITreeViewModel(view));
	proxy_model->SetCustomSort(emModuleColumnSize);
	proxy_model->SetCustomSort(emModuleColumnAddress);
	m_ProxyModel = proxy_model;

	view->setModel(proxy_model);

	m_ModuleModel->Insert(tr("NO."), 60);
	m_ModuleModel->Insert(tr("Name"), 100);
	m_ModuleModel->Insert(tr("Path"), 300);
	m_ModuleModel->Insert(tr("Address"), 120);
	m_ModuleModel->Insert(tr("Size"), 80);
	m_ModuleModel->Insert(tr("Company"), 100);
	m_ModuleModel->Insert(tr("Version"), 100);
	m_ModuleModel->Insert(tr("Description"), 100);
	m_ModuleModel->Insert(tr("LoadTime"), 120);

	Q_CONNECT(view, customContextMenuRequested, on_customContextMenuRequested);
}
//******************************************************************************
UIProcessView::~UIProcessView()
{
	delete ui;
}
//******************************************************************************
void UIProcessView::OnUpdate(IMessage* msg)
{
	cxMSGProcess* process = msg->GetProcess();

	ui->labelIcon->setPixmap(QtWin::fromHICON(process->m_Icon));
	ui->editPath->setText(QStringFrom(process->m_ProcessPath));
	ui->editCommandline->setText(QStringFrom(process->m_Commandline));
	ui->labelFileVersion->setText(QStringFrom(process->m_FileVersion.GetStandardVersion()));
	ui->labelFileName->setText(QStringFrom(process->m_FileVersion.GetCompanyName()));
	ui->labelFileDescription->setText(QStringFrom(process->m_FileVersion.GetFileDescription()));

	ui->labelPid->setText(QString("PID: %1").arg(process->m_ProcessId));
	ui->labelStartTime->setText(QString("StartTime: %1").arg(QStringFrom(g_MSGFormat->FormatDateTime(process->m_CreateTime))));

	if (process->m_ExitTime != 0) {
		ui->labelExitTime->setText(QString("ExitTime:  %1").arg(QStringFrom(g_MSGFormat->FormatDateTime(process->m_ExitTime))));
	}

	m_Process = process;

	ResetModules();
}
//******************************************************************************
void UIProcessView::ResetModules(void)
{
	if (!m_Process)
		return;

	m_ModuleModel->setRowCount(0);

	int index = 0;
	m_Process->EnumModules([this, &index](const cxMSGProcessModule& module) {
		m_ModuleModel->setRowCount(index + 1);
		m_ModuleModel->SetData(index, emModuleColumnNumber, index, Qt::AlignRight);
		m_ModuleModel->SetData(index, emModuleColumnName, module.m_Name);
		m_ModuleModel->SetData(index, emModuleColumnPath, module.m_Path);
		m_ModuleModel->SetData(index, emModuleColumnAddress, g_MSGFormat->FormatAddress(module.m_BaseAddress), Qt::AlignRight);
		m_ModuleModel->SetData(index, emModuleColumnSize, g_MSGFormat->FormatAddress(module.m_Size), Qt::AlignRight);
		m_ModuleModel->SetData(index, emModuleColumnLoadTime, g_MSGFormat->FormatDateTime(module.m_LoadTime));

		m_ModuleModel->SetUserData(index, emModuleColumnAddress, module.m_BaseAddress);
		m_ModuleModel->SetUserData(index, emModuleColumnSize, module.m_Size);

		// TODO(async)
		cxFileVersion version(module.m_Path);
		m_ModuleModel->SetData(index, emModuleColumnVersion, version.GetStandardVersion());
		m_ModuleModel->SetData(index, emModuleColumnCompanyName, version.GetCompanyName());
		m_ModuleModel->SetData(index, emModuleColumnDescription, version.GetFileDescription());

		if (version.GetCompanyName() != "Microsoft Corporation") {
			m_ModuleModel->SetRowColor(index, g_WarningColor);
		}

		index++;
		return true;
	});

	UpdateFilter();
}
//******************************************************************************
void UIProcessView::UpdateFilter(void)
{
	if (ui->checkBoxSystemModules->isChecked()) {
		m_ProxyModel->SetReverseFilter(false);
		m_ProxyModel->setFilterWildcard(QString("*"));
		m_ProxyModel->setFilterKeyColumn(emModuleColumnCompanyName);
	} else {
		m_ProxyModel->SetReverseFilter(true);
		m_ProxyModel->setFilterFixedString("Microsoft Corporation");
		m_ProxyModel->setFilterKeyColumn(emModuleColumnCompanyName);
	}
}
//******************************************************************************
void UIProcessView::on_customContextMenuRequested(const QPoint& pos)
{
	auto index = ui->treeViewModule->currentIndex();

	if (!index.isValid())
		return;

	QMenu menu;

	menu.addAction("Copy", [this, index]() {
		qApp->clipboard()->setText(m_ModuleModel->GetData(index.row(), index.column()).toString());
	});

	if (index.column() == emModuleColumnPath) {
		auto str = m_ModuleModel->GetData(index.row(), index.column()).toString();
		if (!str.isEmpty()) {
			menu.addSeparator();
			menu.addAction(g_res->icon_locate, "Locate", [str]() {
				g_PathLocate->LocateFile(QStringToCString(str));
			});
		}
	}

	menu.exec(QCursor::pos());
}
//******************************************************************************
void UIProcessView::on_btnLocate_clicked()
{
	if (!m_Process || m_Process->m_ProcessPath.IsEmpty())
		return;

	g_PathLocate->Locate(m_Process->m_ProcessPath);
}
//******************************************************************************
void UIProcessView::on_checkBoxSystemModules_stateChanged(int arg)
{
	UpdateFilter();
}
//******************************************************************************
