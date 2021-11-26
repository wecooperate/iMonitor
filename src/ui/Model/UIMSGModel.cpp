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
#include "UIMSGModel.h"
//******************************************************************************
UIMSGModel::UIMSGModel(QTreeView* view)
	: m_View(view)
{
	HandleEvent([this](ServiceEventMSGUpdate& event) {
		OnMSGCountChange(event.Reset, event.Count);
	});
}
//******************************************************************************
int UIMSGModel::columnCount(const QModelIndex& parent) const
{
	return GetMessageService()->GetColumnCount();
}
//******************************************************************************
int UIMSGModel::rowCount(const QModelIndex& parent) const
{
	return m_MSGCount;
}
//******************************************************************************
QVariant UIMSGModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (section < 0)
		return QVariant();

	if (orientation != Qt::Orientation::Horizontal)
		return QVariant();

	if (role == Qt::DisplayRole)
		return GetMessageService()->GetColumn(section)->GetName();

	return QVariant();
}
//******************************************************************************
QVariant UIMSGModel::data(const QModelIndex& index, int role) const
{
	static IMessageService* service = GetMessageService();

	if (!index.isValid())
		return QVariant();

	int row = index.row();
	int column = index.column();

	if (role == Qt::TextAlignmentRole)
		return service->GetColumn(column)->GetAlign();

	auto msg = service->GetItem(row);
	auto msg_column = service->GetColumn(column);

	if (!msg || !msg_column)
		return QVariant();

	switch (role) {
	case Qt::DisplayRole:
		return msg_column->GetString(msg);

	case Qt::BackgroundColorRole: {
		auto color = msg_column->GetColor(msg);
		return color.isValid() ? color : QVariant();
	}

	case Qt::TextColorRole: {
		auto color = msg_column->GetTextColor(msg);
		return color.isValid() ? color : QVariant();
	}

	case Qt::DecorationRole:
		return msg_column->GetIcon(msg);

	case Qt::ToolTipRole:
		return msg_column->GetToolTipsText(msg);
	}

	return QVariant();
}
//******************************************************************************
void UIMSGModel::OnMSGCountChange(bool Reset, ULONG Count)
{
	auto index = m_View->currentIndex();

	if (Reset || m_MSGCount > Count) {
		beginResetModel();
		m_MSGCount = Count;
		endResetModel();
	} else if (Count != m_MSGCount) {
		beginInsertRows(QModelIndex(), m_MSGCount, Count);
		m_MSGCount = Count;
		endInsertRows();
	}

	if (!index.isValid()) {
		if (g_Config->IsEnableAutoScroll) {
			m_View->scrollToBottom();
		}
	} else {
		QRect rect = m_View->visualRect(index);
		QRect viewrect = m_View->rect();

		if (rect.y() > 0 && rect.y() < viewrect.bottom())
			m_View->setCurrentIndex(index);
		else if (g_Config->IsEnableAutoScroll)
			m_View->scrollToBottom();
	}
}
//******************************************************************************
UIMSGIndex::UIMSGIndex(const QTreeView* view)
	: UIMSGIndex(view->currentIndex())
{
}
//******************************************************************************
UIMSGIndex::UIMSGIndex(const QModelIndex& index)
	: m_Index(index)
{
	if (m_Index.row() <= 0 && m_Index.column() <= 0)
		return;

	m_Msg = g_UIManager->GetMessageService()->GetItem(m_Index.row());
}
//******************************************************************************
UIMSGIndex::operator bool(void)
{
	return m_Msg != nullptr;
}
//******************************************************************************
cxMSG* UIMSGIndex::operator->(void)
{
	return m_Msg;
}
//******************************************************************************
UIMSGIndex::operator cxMSG*(void)
{
	return m_Msg;
}
//******************************************************************************
CString UIMSGIndex::GetFieldString(void)
{
	return m_Msg->GetString(GetField());
}
//******************************************************************************
ULONGLONG UIMSGIndex::GetFieldNumber(void)
{
	return m_Msg->GetNumber(GetField());
}
//******************************************************************************
int UIMSGIndex::GetField(void)
{
	auto column = g_UIManager->GetMessageService()->GetColumn(m_Index.column());

	if (!column)
		return emMSGFieldInvalid;

	return column->GetFieldIndex(m_Msg);
}
//******************************************************************************
