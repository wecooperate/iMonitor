//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "UITreeViewModel.h"
//******************************************************************************
UITreeViewModel::UITreeViewModel(QTreeView* view)
	: QStandardItemModel(view)
	, m_View(view)
{
}
//******************************************************************************
void UITreeViewModel::Insert(const QString& name, int width)
{
	int index = columnCount();
	setColumnCount(index + 1);
	setHeaderData(index, Qt::Horizontal, name);
	m_View->setColumnWidth(index, width);
}
//******************************************************************************
void UITreeViewModel::SetUserData(int row, int column, const QVariant& data)
{
	setData(index(row, column), data, Qt::UserRole);
}
//******************************************************************************
void UITreeViewModel::SetData(int row, int column, const QVariant& data, int align)
{
	setData(index(row, column), data);

	if (align != Qt::AlignLeft) {
		setData(index(row, column), align, Qt::TextAlignmentRole);
	}
}
//******************************************************************************
void UITreeViewModel::SetData(int row, int column, const CString& data, int align)
{
	SetData(row, column, QStringFrom(data), align);
}
//******************************************************************************
void UITreeViewModel::SetIcon(int row, int column, const QIcon& icon)
{
	setData(index(row, column), icon, Qt::DecorationRole);
}
//******************************************************************************
void UITreeViewModel::SetRowColor(int row, QColor color)
{
	for (int i = 0; i < columnCount(); i++)
		setData(index(row, i), color, Qt::BackgroundColorRole);
}
//******************************************************************************
QVariant UITreeViewModel::GetData(int row, int column, int role)
{
	return data(index(row, column), role);
}
//******************************************************************************
