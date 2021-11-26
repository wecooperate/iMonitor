//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIFilterEditView_h_19d38d3d_174c_4f07_bb4b_10d5f6fdb68e__
#define __UIFilterEditView_h_19d38d3d_174c_4f07_bb4b_10d5f6fdb68e__
//******************************************************************************
#include "Model/UITreeViewModel.h"
//******************************************************************************
namespace Ui {
class UIFilterEditView;
}
//******************************************************************************
class UISimpleRule : public cxSimpleRule
{
	friend class UIFilterEditView;

public:
	UISimpleRule(const cxSimpleRule& Target);

public:
	QString GetFieldString();
	QString GetValueString();
	QString GetActionString();
};
//******************************************************************************
class UIFilterEditView
	: public QDialog
	, public UIServiceClient
{
	Q_OBJECT

public:
	explicit UIFilterEditView(QWidget* parent = nullptr);
	~UIFilterEditView();

protected:
	void LoadRules();
	void SaveRules();
	void InsertRule(std::shared_ptr<UISimpleRule> rule);

protected:
	void keyPressEvent(QKeyEvent* event) override;

private slots:
	void on_buttonBox_clicked(QAbstractButton* button);
	void on_btnReset_clicked();
	void on_btnRemove_clicked();

private:
	Ui::UIFilterEditView* ui;

protected:
	bool m_Changed = false;
	UITreeViewModel* m_Model;
	std::vector<std::shared_ptr<UISimpleRule>> m_Items;
};
//******************************************************************************
#endif
