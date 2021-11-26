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
#include "UIEventFilter.h"
//******************************************************************************
UIEventFilter::UIEventFilter(QObject* parent)
	: QObject(parent)
{
}
//******************************************************************************
bool UIEventFilter::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::ToolTip)
		return FixToolTip(object, event);

	return false;
}
//******************************************************************************
bool UIEventFilter::FixToolTip(QObject* object, QEvent* event)
{
	QAbstractItemView* view = qobject_cast<QAbstractItemView*>(object->parent());

	if (!view)
		return false;

	QHelpEvent* help_event = (QHelpEvent*)(event);

	QModelIndex index = view->indexAt(help_event->pos());

	if (!index.isValid())
		return false;

	QRect rect = view->visualRect(index);

	QString tooltiptext = view->model()->data(index, Qt::ToolTipRole).toString();

	if (!tooltiptext.isEmpty()) {
		QToolTip::showText(help_event->globalPos(), tooltiptext, view, rect);
	} else {
		QString text = view->model()->data(index).toString();

		QFontMetrics fm(view->font());
		int width = fm.width(text);
		int rectWidth = rect.width();

		if ((width > rect.width()))
			QToolTip::showText(help_event->globalPos(), text, view, rect);
		else
			QToolTip::hideText();
	}

	return true;
}
//******************************************************************************
