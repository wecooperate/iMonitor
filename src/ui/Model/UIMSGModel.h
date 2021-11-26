//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIMSGModel_275DD69E_F8C7_44E0_B216_2F19629012C1__
#define __UIMSGModel_275DD69E_F8C7_44E0_B216_2F19629012C1__
//******************************************************************************
#include <QAbstractTableModel>
//******************************************************************************
class UIMSGModel
	: public QAbstractTableModel
	, public UIServiceClient
{
	Q_OBJECT

public:
	UIMSGModel(QTreeView* view);

public:
	void OnMSGCountChange(bool Reset, ULONG Count);

public:
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

protected:
	QTreeView* m_View = nullptr;
	ULONG m_MSGCount = 0;
};
//******************************************************************************
class UIMSGIndex
{
public:
	UIMSGIndex(const QModelIndex& index);
	UIMSGIndex(const QTreeView* view);

public:
	operator bool(void);
	cxMSG* operator->(void);
	operator cxMSG*(void);

	CString GetFieldString(void);
	ULONGLONG GetFieldNumber(void);
	int GetField(void);

protected:
	cxMSG* m_Msg = nullptr;
	QModelIndex m_Index;
};
//******************************************************************************
#endif
