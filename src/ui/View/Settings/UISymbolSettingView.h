//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UISymbolSettingView_h_05708ec1_b3e8_4568_8a99_6659e63440c3__
#define __UISymbolSettingView_h_05708ec1_b3e8_4568_8a99_6659e63440c3__
//******************************************************************************
#include "View/UISettingView.h"
//******************************************************************************
namespace Ui {
class UISymbolSettingView;
}
//******************************************************************************
class UISymbolSettingView
	: public QWidget
	, public UISettingWidget
	, public UIServiceClient
{
	Q_OBJECT

public:
	explicit UISymbolSettingView(QWidget* parent = nullptr);
	~UISymbolSettingView();

protected:
	void OnUpdate() override;
	void OnApply() override;

private:
	Ui::UISymbolSettingView* ui;
};
//******************************************************************************
#endif
