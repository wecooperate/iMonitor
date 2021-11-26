#include "stdafx.h"
#include "UISymbolSettingView.h"
#include "ui_UISymbolSettingView.h"
//******************************************************************************
UISymbolSettingView::UISymbolSettingView(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::UISymbolSettingView)
{
	ui->setupUi(this);

	ui->editSymbolPath->setPlaceholderText(QStringFrom(g_SymbolManager->GetDefaultSymbolPath()));
}
//******************************************************************************
UISymbolSettingView::~UISymbolSettingView()
{
	delete ui;
}
//******************************************************************************
void UISymbolSettingView::OnUpdate()
{
	auto str = GetConfigService()->GetSectionString("system", "symbol");

	if (!str.empty()) {
		ui->editSymbolPath->setText(str.c_str());
	}
}
//******************************************************************************
void UISymbolSettingView::OnApply()
{
	auto str = ui->editSymbolPath->toPlainText();

	if (str.isEmpty()) {
		g_SymbolManager->SetSymbolPath(g_SymbolManager->GetDefaultSymbolPath());
		GetConfigService()->SetSectionString("system", "symbol", NULL);
	} else {
		g_SymbolManager->SetSymbolPath(CA2T(str.toStdString().c_str(), CP_UTF8));
		GetConfigService()->SetSectionString("system", "symbol", str.toStdString().c_str());
	}
}
//******************************************************************************
