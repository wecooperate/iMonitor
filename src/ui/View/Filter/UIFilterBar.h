//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIFilterBar_h_63ef1369_a512_4b89_ac1f_9cf2fdbe4c7d__
#define __UIFilterBar_h_63ef1369_a512_4b89_ac1f_9cf2fdbe4c7d__
//******************************************************************************
#include <QRegExp>
//******************************************************************************
namespace Ui {
class UIFilterBar;
}
//******************************************************************************
class UIFilterBar
	: public QWidget
	, UIServiceClient
{
	Q_OBJECT

public:
	explicit UIFilterBar(QWidget* parent = nullptr);
	~UIFilterBar();

public:
	void SetDelegate(std::function<void(const cxRuleMatcher&, bool)> delegate);

private slots:
	void on_btnAddFilter_clicked();
	void on_btnFilterEdit_clicked();
	void on_comboBoxType_currentIndexChanged(int index);
	void on_comboBoxField_currentIndexChanged(int index);
	void on_editValue_textChanged(const QString& text);
	void on_comboBoxOperator_currentIndexChanged(int index);

protected:
	void InitType();
	void InitField(ULONG Type);
	void InitOperator();
	void InitAction();
	void InsertRule(const cxRuleMatcher& matcher, bool include);

private:
	Ui::UIFilterBar* ui;

protected:
	QRegExpValidator* m_NumberValidator;
	std::function<void(const cxRuleMatcher&, bool)> m_Delegate;
};
//******************************************************************************
#endif
