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
#include "UIMessageProperties.h"
#include "ui_UIMessageProperties.h"
#include "Properties/UICallstackView.h"
#include "Properties/UIProcessView.h"
#include "Properties/UIMessageDetailView.h"
//******************************************************************************
UIMessageProperties::UIMessageProperties(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::UIMessageProperties)
{
	ui->setupUi(this);

	ui->tab->addTab(new UIMessageDetailView(this), "Event");
	ui->tab->addTab(new UIProcessView(this), "Process");
	auto index_callstack = ui->tab->addTab(new UICallstackView(this), "Callstack");
	ui->tab->setCurrentIndex(index_callstack);

	HandleEvent(emServiceEventMSGClear, [this]() {
		close();
	});
}
//******************************************************************************
UIMessageProperties::~UIMessageProperties()
{
	delete ui;
}
//******************************************************************************
void UIMessageProperties::showEvent(QShowEvent* event)
{
	IMessage* msg = (IMessage*)(property("msg").value<void*>());

	if (!msg)
		return;

	cxMSGProcess* process = msg->GetProcess();

	CString info;
	info.Format(_T("%s -> %s : %s"), msg->GetProcessName(), msg->GetName(), msg->GetString(emMSGFieldPath));

	setWindowIcon(GetVisionService()->GetIcon(process->m_Icon));
	setWindowTitle(QStringFrom(info));

	on_tab_currentChanged(ui->tab->currentIndex());
}
//******************************************************************************
void UIMessageProperties::on_tab_currentChanged(int index)
{
	IMessage* msg = (IMessage*)(property("msg").value<void*>());

	if (!msg)
		return;

	auto widget = dynamic_cast<UIMessagePropertyWidget*>(ui->tab->widget(index));

	if (!widget)
		return;

	widget->OnUpdate(msg);
}
//******************************************************************************
