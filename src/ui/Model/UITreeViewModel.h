//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UITreeViewModel_h_52f3ffab_a32f_41fe_8658_67d581507fc8__
#define __UITreeViewModel_h_52f3ffab_a32f_41fe_8658_67d581507fc8__
//******************************************************************************
#include <QStandardItemModel>
//******************************************************************************
class UITreeViewModel : public QStandardItemModel
{
public:
	UITreeViewModel(QTreeView* view);

public:
	void Insert(const QString& name, int width);

public:
	void SetUserData(int row, int column, const QVariant& data);
	void SetData(int row, int column, const QVariant& data, int align = Qt::AlignLeft);
	void SetData(int row, int column, const CString& data, int align = Qt::AlignLeft);
	void SetIcon(int row, int column, const QIcon& icon);
	void SetRowColor(int row, QColor color);

public:
	QVariant GetData(int row, int column, int role = Qt::DisplayRole);

protected:
	QTreeView* m_View;
};
//******************************************************************************
#endif
