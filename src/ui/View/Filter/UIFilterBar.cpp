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
#include "UIFilterBar.h"
#include "ui_UIFilterBar.h"
//******************************************************************************
UIFilterBar::UIFilterBar(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::UIFilterBar)
{
	ui->setupUi(this);

	ui->btnAddFilter->setIcon(g_res->icon_add);
	ui->btnAddFilter->setIconSize(QSize(20, 20));
	ui->btnAddFilter->setText("");
	ui->btnAddFilter->setDisabled(true);

	ui->btnFilterEdit->setIcon(g_res->icon_list);
	ui->btnFilterEdit->setIconSize(QSize(20, 20));
	ui->btnFilterEdit->setText("");

	m_NumberValidator = new QRegExpValidator(QRegExp("0[xX][0-9A-Fa-f]+|[0-9]+"), this);

	InitType();
	InitAction();
	InitOperator();
}
//******************************************************************************
UIFilterBar::~UIFilterBar()
{
	delete ui;
}
//******************************************************************************
void UIFilterBar::SetDelegate(std::function<void(const cxRuleMatcher&, bool)> delegate)
{
	m_Delegate = delegate;

	if (m_Delegate)
		ui->btnFilterEdit->hide();
}
//******************************************************************************
void UIFilterBar::on_btnAddFilter_clicked()
{
	auto type = ui->comboBoxType->currentData().toUInt();
	auto field = ui->comboBoxField->currentData().toUInt();
	auto op = (emMatchOperator)ui->comboBoxOperator->currentData().toUInt();
	auto include = ui->comboBoxAction->currentData().toBool();
	auto value = ui->editValue->text();

	if (value.isEmpty())
		return;

	if (cxRuleMatcher::IsNumberOperator(op)) {
		ULONGLONG number_value = 0;
		if (value.length() > 2 && (value[1] == 'x' || value[1] == 'X')) {
			number_value = value.toLongLong(nullptr, 16);
		} else {
			number_value = value.toLongLong(nullptr, 10);
		}
		InsertRule(cxRuleMatcher(op, field, number_value, type), include);
	} else {
		InsertRule(cxRuleMatcher(op, field, QStringToCString(value), type), include);
	}
}
//******************************************************************************
void UIFilterBar::on_btnFilterEdit_clicked()
{
	g_UIManager->Show(SCHEME_FILTER_EDIT_VIEW, true);
}
//******************************************************************************
void UIFilterBar::on_comboBoxType_currentIndexChanged(int index)
{
	auto combobox = ui->comboBoxType;

	InitField(combobox->itemData(index).toUInt());
}
//******************************************************************************
void UIFilterBar::on_comboBoxField_currentIndexChanged(int index)
{
	auto field = ui->comboBoxField->itemData(index);

	ui->comboBoxOperator->setEnabled(field != emMSGFieldCallstack);

	if (field == emMSGFieldCallstack) {
		ui->comboBoxOperator->setCurrentIndex(0);
		ui->editValue->setPlaceholderText("input callstack module path, support wildcard string value, for example: *.exe");
	} else {
		on_comboBoxOperator_currentIndexChanged(ui->comboBoxOperator->currentIndex());
	}
}
//******************************************************************************
void UIFilterBar::on_editValue_textChanged(const QString& text)
{
	ui->btnAddFilter->setDisabled(text.isEmpty());
}
//******************************************************************************
void UIFilterBar::on_comboBoxOperator_currentIndexChanged(int index)
{
	auto combobox = ui->comboBoxOperator;
	auto type = combobox->itemData(index).toUInt();

	ui->editValue->setValidator(nullptr);
	ui->editValue->setText("");

	if (type == emOperatorStringMatch || type == emOperatorStringNotMatch) {
		ui->editValue->setPlaceholderText("input wildcard string value, for example: *.exe");
	} else if (type > emOperatorStringBegin) {
		ui->editValue->setPlaceholderText("input string value");
	} else {
		ui->editValue->setPlaceholderText("input number value, for example: 0x123ABC or 12345");
		ui->editValue->setValidator(m_NumberValidator);
	}

	ui->editValue->setFocus();
}
//******************************************************************************
void UIFilterBar::InitType()
{
	auto combobox = ui->comboBoxType;
	combobox->clear();

	combobox->addItem("*", emMSGAllType);

	for (auto& it : g_MSGConfig->GetConfigItems()) {
		auto group = MSG_GET_GROUP(it.Type);
		QIcon icon;
		switch (group) {
		case emMSGGroupProcess:
			icon = g_res->icon_msg_process;
			break;

		case emMSGGroupFile:
			icon = g_res->icon_msg_file;
			break;

		case emMSGGroupRegistry:
			icon = g_res->icon_msg_registry;
			break;

		case emMSGGroupSocket:
			icon = g_res->icon_msg_network;
			break;
		}

		combobox->addItem(icon, QStringFrom(it.Name), (int)it.Type);
	}
}
//******************************************************************************
void UIFilterBar::InitField(ULONG Type)
{
	auto combobox = ui->comboBoxField;
	combobox->clear();

	combobox->addItem("Path", emMSGFieldPath);
	combobox->addItem("Callstack", emMSGFieldCallstack);
	combobox->addItem("Status", emMSGFieldStatus);
	combobox->addItem("No.", emMSGFieldSeqId);
	combobox->addItem("CurrentProcessId", emMSGFieldCurrentProcessId);
	combobox->addItem("CurrentThreadId", emMSGFieldCurrentThreadId);
	combobox->addItem("CurrentProcessName", emMSGFieldCurrentProcessName);
	combobox->addItem("CurrentProcessPath", emMSGFieldCurrentProcessPath);
	combobox->addItem("CurrentCommandline", emMSGFieldCurrentProcessCommandline);
	combobox->addItem("Operation", emMSGFieldType);

	if (Type == emMSGAllType) {
		return;
	}

	auto info = g_MSGInfo->GetMSGInfo(Type);

	for (ULONG i = emMSGFieldPath + 1; i < info.FieldCount; i++) {
		combobox->addItem(QStringFrom(info.Fields[i].Name), (int)i);
	}
}
//******************************************************************************
void UIFilterBar::InitOperator()
{
	auto combobox = ui->comboBoxOperator;
	combobox->clear();

	auto operators = {
		emOperatorStringMatch,
		emOperatorStringNotMatch,
		emOperatorStringEqual,
		emOperatorStringNotEqual,
		emOperatorNumberEqual,
		emOperatorNumberNotEqual,
		emOperatorNumberGreater,
		emOperatorNumberGreaterEqual,
		emOperatorNumberLess,
		emOperatorNumberLessEqual,
		emOperatorNumberInclude,
	};

	for (auto& it : operators) {
		combobox->addItem(QStringFrom(cxRuleMatcher::GetOperatorString(it)), (int)it);
	}
}
//******************************************************************************
void UIFilterBar::InitAction()
{
	auto combobox = ui->comboBoxAction;
	combobox->clear();

	combobox->addItem("Include", true);
	combobox->addItem("Exclude", false);
}
//******************************************************************************
void UIFilterBar::InsertRule(const cxRuleMatcher& matcher, bool include)
{
	if (m_Delegate) {
		m_Delegate(matcher, include);
		return;
	}

	g_RuleManager->InsertRule(matcher, include);
}
//******************************************************************************
