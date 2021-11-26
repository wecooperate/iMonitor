//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UI_h_df5a3ab6_ea61_45e2_96ce_9ee9ff5ac062__
#define __UI_h_df5a3ab6_ea61_45e2_96ce_9ee9ff5ac062__
//******************************************************************************
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QTimer>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTreeWidget>
#include <QAbstractItemView>
#include <QHelpEvent>
#include <QToolTip>
#include <QSettings>
#include <QLabel>
#include <QStandardItemModel>
#include <QToolButton>
#include <QListWidget>
#include <QWidgetAction>
#include <QtWinExtras/QtWin>
#include <QClipboard>
//******************************************************************************
#define Q_CONNECT(widget, signal, slot, ...) connect(widget, &std::remove_pointer<decltype(widget)>::type::signal, this, &std::remove_pointer<decltype(this)>::type::slot, __VA_ARGS__)
//******************************************************************************
inline QColor QColorFromCOLORREF(COLORREF color)
{
	return QColor(GetRValue(color), GetGValue(color), GetBValue(color));
}
//******************************************************************************
inline QString QStringFrom(LPCTSTR Str)
{
	return QString::fromWCharArray(Str);
}
//******************************************************************************
inline QString QStringFrom(const CString& Str)
{
	return QString::fromWCharArray(Str);
}
//******************************************************************************
inline CString QStringToCString(const QString& Str)
{
	return Str.toStdWString().data();
}
//******************************************************************************
inline QString QFormatString(LPCTSTR data, int length = 40)
{
	CString str = data;

	if (str.GetLength() <= length)
		return QStringFrom(str);

	CString strfix = str.Left(length / 2);
	strfix += _T("...");
	strfix += str.Right(length / 2);

	return QStringFrom(strfix);
}
//******************************************************************************
#include "UIEventFilter.h"
//******************************************************************************
#endif
