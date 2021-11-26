//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIMessageView_F4F1C2DE_D62E_46C1_89FB_51BFA153EE14__
#define __UIMessageView_F4F1C2DE_D62E_46C1_89FB_51BFA153EE14__
//******************************************************************************
#include <QTreeView>
#include <QProgressDialog>
//******************************************************************************
class UIMessageView
	: public QTreeView
	, public UIServiceClient
{
public:
	Q_OBJECT

public:
	UIMessageView(QWidget* parent = nullptr);
	~UIMessageView();

protected:
	void ShowProgressDialog(void);
	void HideProgressDialog(void);

private slots:
	void on_customContextMenuRequested(const QPoint& pos);
	void on_doubleClicked(const QModelIndex& index);
	void on_currentChanged(const QModelIndex& current, const QModelIndex& previous);

protected:
	QProgressDialog* m_Progress = nullptr;
	QTimer* m_ProgressTimer = nullptr;
};
//******************************************************************************
#endif
