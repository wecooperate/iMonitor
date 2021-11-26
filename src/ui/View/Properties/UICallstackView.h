//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UICallstackView_h_c18b2bfb_6a97_41bd_a186_82b4ee58f151__
#define __UICallstackView_h_c18b2bfb_6a97_41bd_a186_82b4ee58f151__
//******************************************************************************
#include <QWidget>
#include "Model/UITreeViewModel.h"
#include "View/UIMessageProperties.h"
//******************************************************************************
namespace Ui {
class UICallstackView;
}
//******************************************************************************
class UICallstackView
	: public QFrame
	, public UIServiceClient
	, public UIMessagePropertyWidget
{
	Q_OBJECT

public:
	explicit UICallstackView(QWidget* parent = nullptr);
	~UICallstackView();

public:
	void OnUpdate(IMessage* msg) override;

protected:
	void on_customContextMenuRequested(const QPoint& pos);

private:
	Ui::UICallstackView* ui;

protected:
	UITreeViewModel* m_Model;
	std::vector<std::shared_ptr<cxSymbolParser>> m_Symbols;
};
//******************************************************************************
#endif
