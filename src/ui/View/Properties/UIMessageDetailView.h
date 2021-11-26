//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIMessageDetailView_h_8904e6b3_b96f_432b_bc5c_c359f49aff42__
#define __UIMessageDetailView_h_8904e6b3_b96f_432b_bc5c_c359f49aff42__
//******************************************************************************
#include "View/UIMessageProperties.h"
//******************************************************************************
namespace Ui {
class UIMessageDetailView;
}
//******************************************************************************
class UIMessageDetailView
	: public QWidget
	, public UIMessagePropertyWidget
	, public UIServiceClient
{
	Q_OBJECT

public:
	explicit UIMessageDetailView(QWidget* parent = nullptr);
	~UIMessageDetailView();

protected:
	void OnUpdate(IMessage* msg) override;

protected:
	void InsertTextItem(int row, const QString& name, const QString& value);
	void InsertBinaryItem(int row, const QString& name, const cxMSGDataBinary& value);

private:
	Ui::UIMessageDetailView* ui;

protected:
	QList<QWidget*> m_Widgets;
	QAction* m_IconAction = nullptr;
};
//******************************************************************************
#endif
