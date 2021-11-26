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
#include "UIMessageDetailView.h"
#include "ui_UIMessageDetailView.h"
#include <QLineEdit>
#include <Common/third_party/qhexview/qhexview.h>
//******************************************************************************
UIMessageDetailView::UIMessageDetailView(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::UIMessageDetailView)
{
	ui->setupUi(this);
}
//******************************************************************************
UIMessageDetailView::~UIMessageDetailView()
{
	delete ui;
}
//******************************************************************************
void UIMessageDetailView::OnUpdate(IMessage* msg)
{
	for (auto& it : m_Widgets) {
		delete it;
	}

	m_Widgets.clear();

	delete ui->gridLayout;
	ui->gridLayout = new QGridLayout(ui->groupBox);

	ui->labelTime->setText(QStringFrom(g_MSGFormat->FormatDateTime(msg->m_Time)));

	if (msg->m_Status != 0) {
		CString status = msg->GetStatus();
		status += " : ";
		status += g_MSGStatus->GetErrorString(msg->m_Status);
		ui->labelStatus->setText(QStringFrom(status));
	} else {
		ui->labelStatus->setText("");
	}

	ui->labelOperationIcon->setPixmap(GetVisionService()->GetGroupIcon(msg->GetGroup()).pixmap(16, 16));
	ui->labelOperation->setText(QStringFrom(msg->GetName()));
	ui->editProcessName->setText(QStringFrom(msg->GetProcessName()));
	ui->editPath->setText(QStringFrom(msg->GetPath()));

	if (!m_IconAction) {
		m_IconAction = new QAction(ui->editProcessName);
		ui->editProcessName->addAction(m_IconAction, QLineEdit::LeadingPosition);
	}

	m_IconAction->setIcon(GetVisionService()->GetIcon(msg->GetProcess()->m_Icon));

	auto info = msg->GetMSGInfo();

	bool needSpacer = true;
	int currentCount = 0;

	for (ULONG index = emMSGFieldPrivateBegin + 1; index < info.FieldCount; index++) {
		QString name = QStringFrom(info.Fields[index].Name);

		if (info.Fields[index].Type == emMSGDataBinary) {
			auto binary = g_MSGData->GetBinary(msg->GetNumber(index));
			if (binary.Length > 0) {
				InsertBinaryItem(currentCount++, name, binary);
				needSpacer = false;
				continue;
			}
		}

		InsertTextItem(currentCount++, name, QStringFrom(msg->GetString(index)));
	}

	if (needSpacer) {
		auto verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
		ui->gridLayout->addItem(verticalSpacer, currentCount, 0, 1, 1);
	}
}
//******************************************************************************
void UIMessageDetailView::InsertTextItem(int row, const QString& name, const QString& value)
{
	auto label = new QLabel(ui->groupBox);
	label->setText(name + ":");
	label->setAlignment(Qt::AlignRight);
	label->setMinimumWidth(140);
	ui->gridLayout->addWidget(label, row, 0, 1, 1);

	auto edit = new QLineEdit(ui->groupBox);
	edit->setText(value);
	edit->setReadOnly(true);
	ui->gridLayout->addWidget(edit, row, 1, 1, 1);

	m_Widgets.push_back(label);
	m_Widgets.push_back(edit);
}
//******************************************************************************
void UIMessageDetailView::InsertBinaryItem(int row, const QString& name, const cxMSGDataBinary& value)
{
	auto label = new QLabel(ui->groupBox);
	label->setText(name + ":");
	label->setAlignment(Qt::AlignRight);
	label->setMinimumWidth(140);
	ui->gridLayout->addWidget(label, row, 0, 1, 1);

	QHexView* hexview = new QHexView(ui->groupBox);
	hexview->setDocument(QHexDocument::fromMemory<QMemoryRefBuffer>((char*)value.Data, value.Length));
	hexview->setReadOnly(true);
	ui->gridLayout->addWidget(hexview, row, 1, 1, 1);

	m_Widgets.push_back(label);
	m_Widgets.push_back(hexview);
}
//******************************************************************************
