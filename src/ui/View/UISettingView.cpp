
//******************************************************************************
/*++
	FileName:		UISettingView.cpp
	Description:

--*/
//******************************************************************************
#include "stdafx.h"
#include "UISettingView.h"
#include "ui_UISettingView.h"
#include "Settings/UISymbolSettingView.h"
//******************************************************************************
UISettingView::UISettingView(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::UISettingView)
{
	ui->setupUi(this);

	ui->tab->addTab(new UISymbolSettingView(this), "Symbol");
}
//******************************************************************************
UISettingView::~UISettingView()
{
	delete ui;
}
//******************************************************************************
void UISettingView::on_tab_currentChanged(int index)
{
	auto widget = dynamic_cast<UISettingWidget*>(ui->tab->widget(index));

	if (widget)
		widget->OnUpdate();
}
//******************************************************************************
void UISettingView::on_buttonBox_clicked(QAbstractButton* button)
{
	auto role = ui->buttonBox->buttonRole(button);

	if (role == QDialogButtonBox::ApplyRole || role == QDialogButtonBox::AcceptRole) {
		auto widget = dynamic_cast<UISettingWidget*>(ui->tab->currentWidget());
		if (widget)
			widget->OnApply();
	}
}
//******************************************************************************
