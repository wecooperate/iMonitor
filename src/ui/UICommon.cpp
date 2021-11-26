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
#include "UICommon.h"
#include <QCheckBox>
//******************************************************************************
void UILoadConfig(QWidget* widget)
{
	auto name = widget->objectName();

	auto main_window = qobject_cast<QMainWindow*>(widget);
	if (main_window) {
		g_UIManager->GetConfigService()->LoadState(main_window, name.toStdString().c_str());
	}

	g_UIManager->GetConfigService()->LoadGeometry(widget, name.toStdString().c_str());

	for (auto& it : widget->findChildren<QTreeView*>()) {
		auto sub_name = name + '_' + it->objectName();
		g_UIManager->GetConfigService()->LoadState(it->header(), sub_name.toStdString().c_str());
	}

	for (auto& it : widget->findChildren<QTabWidget*>()) {
		auto sub_name = name + '_' + it->objectName();
		auto index = g_UIManager->GetConfigService()->GetSectionInt(sub_name.toStdString().c_str(), "index", -1);
		if (index != -1) {
			it->setCurrentIndex(index);
		}
	}

	for (auto& it : widget->findChildren<QCheckBox*>()) {
		auto sub_name = name + '_' + it->objectName();
		auto index = g_UIManager->GetConfigService()->GetSectionInt(sub_name.toStdString().c_str(), "check", -1);
		if (index != -1) {
			it->setChecked(index);
		}
	}
}
//******************************************************************************
void UISaveConfig(QWidget* widget)
{
	auto name = widget->objectName();

	auto main_window = qobject_cast<QMainWindow*>(widget);
	if (main_window) {
		g_UIManager->GetConfigService()->SaveState(main_window, name.toStdString().c_str());
	}

	g_UIManager->GetConfigService()->SaveGeometry(widget, name.toStdString().c_str());

	for (auto& it : widget->findChildren<QTreeView*>()) {
		auto sub_name = name + '_' + it->objectName();
		g_UIManager->GetConfigService()->SaveState(it->header(), sub_name.toStdString().c_str());
	}

	for (auto& it : widget->findChildren<QTabWidget*>()) {
		auto sub_name = name + '_' + it->objectName();
		g_UIManager->GetConfigService()->SetSectionInt(sub_name.toStdString().c_str(), "index", it->currentIndex());
	}

	for (auto& it : widget->findChildren<QCheckBox*>()) {
		auto sub_name = name + '_' + it->objectName();
		g_UIManager->GetConfigService()->SetSectionInt(sub_name.toStdString().c_str(), "check", it->isChecked());
	}
}
//******************************************************************************
void UIInitTreeView(QTreeView* view)
{
	view->setContextMenuPolicy(Qt::CustomContextMenu);
	view->setSelectionBehavior(QAbstractItemView::SelectRows);
	view->setSelectionMode(QAbstractItemView::SingleSelection);
	view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	view->setRootIsDecorated(false);
	view->setSortingEnabled(true);
	view->setAlternatingRowColors(false);
	view->setAnimated(false);
	view->setUniformRowHeights(true);
	view->setTextElideMode(Qt::TextElideMode::ElideMiddle);
	view->header()->setStretchLastSection(true);
}
//******************************************************************************
