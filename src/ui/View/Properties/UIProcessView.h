//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIProcessView_h_9a5c3805_886d_4dd0_94b3_f581c5e22909__
#define __UIProcessView_h_9a5c3805_886d_4dd0_94b3_f581c5e22909__
//******************************************************************************
#include "View/UIMessageProperties.h"
#include "Model/UITreeViewModel.h"
#include "Model/UIModel.h"
//******************************************************************************
namespace Ui {
class UIProcessView;
}
//******************************************************************************
class UIProcessView
	: public QWidget
	, public UIMessagePropertyWidget
	, public UIServiceClient
{
	Q_OBJECT

public:
	explicit UIProcessView(QWidget* parent = nullptr);
	~UIProcessView();

protected:
	void OnUpdate(IMessage* msg) override;
	void ResetModules(void);
	void UpdateFilter(void);

private slots:
	void on_customContextMenuRequested(const QPoint& pos);
	void on_btnLocate_clicked();
	void on_checkBoxSystemModules_stateChanged(int arg);

private:
	Ui::UIProcessView* ui;

private:
	UITreeViewModel* m_ModuleModel;
	UISortFilterProxyModel* m_ProxyModel;
	CString m_WindowsDirectory = g_Path->GetWindowDirectory();
	cxMSGProcess* m_Process = nullptr;
};
//******************************************************************************
#endif
