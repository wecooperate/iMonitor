//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UISettingView_h_1aa5655d_f94a_47d0_9945_30073d6ac21b__
#define __UISettingView_h_1aa5655d_f94a_47d0_9945_30073d6ac21b__
//******************************************************************************
namespace Ui {
class UISettingView;
}
//******************************************************************************
interface UISettingWidget
{
	virtual void OnUpdate(void) = 0;
	virtual void OnApply(void) = 0;
};
//******************************************************************************
class UISettingView : public QDialog
{
	Q_OBJECT

public:
	explicit UISettingView(QWidget* parent = nullptr);
	~UISettingView();

private slots:
	void on_tab_currentChanged(int index);
	void on_buttonBox_clicked(QAbstractButton* button);

private:
	Ui::UISettingView* ui;
};
//******************************************************************************
#endif
