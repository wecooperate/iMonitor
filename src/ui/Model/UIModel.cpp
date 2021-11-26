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
#include "UIModel.h"
//******************************************************************************
UIAbstractTableModel::UIAbstractTableModel(QObject* parent)
	: QAbstractTableModel(parent)
{
}
//******************************************************************************
int UIAbstractTableModel::columnCount(const QModelIndex& parent) const
{
	return GetColumnCount();
}
//******************************************************************************
QVariant UIAbstractTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Qt::Orientation::Horizontal)
		return QVariant();

	if (role == Qt::DisplayRole)
		return GetColumnName(section);

	return QVariant();
}
//******************************************************************************
int UIAbstractTableModel::rowCount(const QModelIndex& parent) const
{
	return GetCount();
}
//******************************************************************************
QVariant UIAbstractTableModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	int column = index.column();
	int row = index.row();

	switch (role) {
	case Qt::DisplayRole:
		return GetValue(column, row);

	case Qt::TextAlignmentRole:
		return GetAlign(column, row);

	case Qt::DecorationRole:
		return GetIcon(column, row);

	case Qt::ToolTipRole:
		return GetToolTips(column, row);

	case Qt::BackgroundColorRole: {
		auto color = GetColor(column, row);
		return color.isValid() ? color : QVariant();
	}

	case Qt::TextColorRole: {
		auto color = GetTextColor(column, row);
		return color.isValid() ? color : QVariant();
	}

	default:
		return QVariant();
	}
}
//******************************************************************************
QString UIAbstractTableModel::GetToolTips(int column, int row) const
{
	return QString();
}
//******************************************************************************
int UIAbstractTableModel::GetAlign(int column, int row) const
{
	return Qt::AlignLeft;
}
//******************************************************************************
QColor UIAbstractTableModel::GetColor(int column, int row) const
{
	return QColor();
}
//******************************************************************************
QColor UIAbstractTableModel::GetTextColor(int column, int row) const
{
	return QColor();
}
//******************************************************************************
QIcon UIAbstractTableModel::GetIcon(int column, int row) const
{
	return QIcon();
}
//******************************************************************************
bool UIAbstractTableModel::IsPath(int column, int row) const
{
	return false;
}
//******************************************************************************
UISortFilterProxyModel::UISortFilterProxyModel(QObject* parent)
	: QSortFilterProxyModel(parent)
{
}
//******************************************************************************
void UISortFilterProxyModel::SetCustomSort(int column, int role)
{
	m_CustomSortRoles[column] = role;
}
//******************************************************************************
void UISortFilterProxyModel::SetReverseFilter(bool enable)
{
	m_IsReverseFilter = enable;
}
//******************************************************************************
bool UISortFilterProxyModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
	auto it = m_CustomSortRoles.find(source_right.column());

	if (it == m_CustomSortRoles.end())
		return __super::lessThan(source_left, source_right);

	return sourceModel()->data(source_left, it->second) < sourceModel()->data(source_right, it->second);
}
//******************************************************************************
bool UISortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
	bool accept = __super::filterAcceptsRow(source_row, source_parent);

	return m_IsReverseFilter ? !accept : accept;
}
//******************************************************************************
