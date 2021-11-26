//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIModel_18801C65_E7DD_47D6_AEA3_4561C6BB7F7B__
#define __UIModel_18801C65_E7DD_47D6_AEA3_4561C6BB7F7B__
//******************************************************************************
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>
//******************************************************************************
class UIAbstractTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	UIAbstractTableModel(QObject* parent = nullptr);

public:
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

protected:
	virtual int GetColumnCount(void) const = 0;
	virtual QString GetColumnName(int index) const = 0;
	virtual int GetColumnWidth(int index) const = 0;

	virtual int GetCount(void) const = 0;
	virtual QString GetValue(int column, int row) const = 0;

	virtual QString GetToolTips(int column, int row) const;
	virtual int GetAlign(int column, int row) const;
	virtual QColor GetColor(int column, int row) const;
	virtual QColor GetTextColor(int column, int row) const;
	virtual QIcon GetIcon(int column, int row) const;
	virtual bool IsPath(int column, int row) const;
};
//******************************************************************************
class UISortFilterProxyModel : public QSortFilterProxyModel
{
public:
	UISortFilterProxyModel(QObject* parent = nullptr);

public:
	void SetCustomSort(int column, int role = Qt::UserRole);
	void SetReverseFilter(bool enable);

protected:
	bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const override;
	bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;

protected:
	std::map<int, int> m_CustomSortRoles;
	bool m_IsReverseFilter = false;
};
//******************************************************************************
#endif
