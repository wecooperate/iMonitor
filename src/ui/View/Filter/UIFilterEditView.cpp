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
#include "UIFilterEditView.h"
#include "ui_UIFilterEditView.h"
#include "Model/UIModel.h"
//******************************************************************************
static QColor g_disableColor("#AAAAAA");
static QColor g_EnableColor("#FFFFFF");
//******************************************************************************
enum emFilterRuleColumn {
	emFilterRuleColumnField,
	emFilterRuleColumnOperator,
	emFilterRuleColumnValue,
	emFilterRuleColumnAction,
	emFilterRuleColumnMax,
};
//******************************************************************************
UISimpleRule::UISimpleRule(const cxSimpleRule& Target)
	: cxSimpleRule(Target)
{
}
//******************************************************************************
QString UISimpleRule::GetFieldString()
{
	if (m_Type == emMSGAllType)
		return QStringFrom(g_MSGInfo->GetCommonFieldName(m_Field));

	QString str;

	str += QStringFrom(g_MSGInfo->GetName(m_Type));
	str += '.';
	str += QStringFrom(g_MSGInfo->GetFieldName(m_Type, m_Field));

	return str;
}
//******************************************************************************
QString UISimpleRule::GetValueString()
{
	if (IsNumber())
		return QString("%1").arg(m_Data);

	return QStringFrom(m_DataString);
}
//******************************************************************************
QString UISimpleRule::GetActionString()
{
	return m_IsInclude ? "Include" : "Exclude";
}
//******************************************************************************
UIFilterEditView::UIFilterEditView(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::UIFilterEditView)
{
	ui->setupUi(this);

	auto view = ui->treeView;

	UIInitTreeView(view);

	auto proxy_model = new UISortFilterProxyModel(this);
	proxy_model->setSourceModel(m_Model = new UITreeViewModel(view));
	view->setModel(proxy_model);

	m_Model->Insert(tr("Field"), 200);
	m_Model->Insert(tr("Operator"), 120);
	m_Model->Insert(tr("Value"), 200);
	m_Model->Insert(tr("Action"), 120);

	LoadRules();

	ui->filterBar->SetDelegate([this](const cxRuleMatcher& matcher, bool include) {
		InsertRule(std::make_shared<UISimpleRule>(matcher));
		m_Changed = true;
	});

	ui->buttonBox->setFocusPolicy(Qt::NoFocus);

	connect(m_Model, &QStandardItemModel::itemChanged, [this]() {
		m_Changed = true;
	});
}
//******************************************************************************
UIFilterEditView::~UIFilterEditView()
{
	delete ui;
}
//******************************************************************************
void UIFilterEditView::LoadRules()
{
	g_RuleManager->EnumRules([this](const cxSimpleRule* Rule) {
		InsertRule(std::make_shared<UISimpleRule>(*Rule));
		return true;
	});
}
//******************************************************************************
void UIFilterEditView::SaveRules()
{
	auto count = m_Model->rowCount();

	std::list<std::shared_ptr<cxSimpleRule>> rules;

	for (auto index = 0; index < count; index++) {
		auto rule = (UISimpleRule*)m_Model->GetData(index, emFilterRuleColumnField, Qt::UserRole).toULongLong();
		rule->m_IsEnable = m_Model->item(index)->checkState() == Qt::Checked;
		rules.push_back(std::make_shared<cxSimpleRule>(*rule));
	}

	g_RuleManager->ResetRules(rules);
}
//******************************************************************************
void UIFilterEditView::InsertRule(std::shared_ptr<UISimpleRule> rule)
{
	m_Items.push_back(rule);

	auto index = m_Model->rowCount();
	m_Model->setRowCount(index + 1);

	m_Model->SetUserData(index, emFilterRuleColumnField, (qulonglong)rule.get());
	m_Model->SetData(index, emFilterRuleColumnField, rule->GetFieldString());
	m_Model->SetData(index, emFilterRuleColumnOperator, rule->GetOperatorString(rule->m_Operator));
	m_Model->SetData(index, emFilterRuleColumnValue, rule->GetValueString());
	m_Model->SetData(index, emFilterRuleColumnAction, rule->GetActionString());

	auto uitem = m_Model->item(index);
	uitem->setCheckable(true);
	uitem->setCheckState(rule->m_IsEnable ? Qt::Checked : Qt::Unchecked);
}
//******************************************************************************
void UIFilterEditView::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
		return;

	__super::keyPressEvent(event);
}
//******************************************************************************
void UIFilterEditView::on_buttonBox_clicked(QAbstractButton* button)
{
	auto role = ui->buttonBox->buttonRole(button);

	if (role == QDialogButtonBox::ApplyRole || role == QDialogButtonBox::AcceptRole) {
		if (m_Changed) {
			m_Changed = false;
			SaveRules();
		}
	}
}
//******************************************************************************
void UIFilterEditView::on_btnReset_clicked()
{
	m_Model->setRowCount(0);

	m_Changed = true;
}
//******************************************************************************
void UIFilterEditView::on_btnRemove_clicked()
{
	auto index = ui->treeView->currentIndex();

	if (!index.isValid())
		return;

	m_Model->removeRow(index.row());

	m_Changed = true;
}
//******************************************************************************
