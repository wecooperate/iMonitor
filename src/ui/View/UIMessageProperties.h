//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIMessageProperties_h_1c098182_d40e_4038_9dc8_32f7c059568e__
#define __UIMessageProperties_h_1c098182_d40e_4038_9dc8_32f7c059568e__
//******************************************************************************
#include <QDialog>
//******************************************************************************
namespace Ui {
class UIMessageProperties;
}
//******************************************************************************
interface UIMessagePropertyWidget
{
	virtual void OnUpdate(IMessage * msg) = 0;
};
//******************************************************************************
class UIMessageProperties
	: public QDialog
	, public UIServiceClient
{
	Q_OBJECT

public:
	explicit UIMessageProperties(QWidget* parent = nullptr);
	~UIMessageProperties();

protected:
	void showEvent(QShowEvent* event) override;

private slots:
	void on_tab_currentChanged(int index);

private:
	Ui::UIMessageProperties* ui;
};
//******************************************************************************
#endif
