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
#include "UIToolBar.h"
//******************************************************************************
void UIToolBar::Initalize(QToolBar* toolbar)
{
	m_ToolBar = toolbar;

	for (auto& it : toolbar->actions()) {
		if (it->objectName() == "action_Colorful") {
			action_Colorful = it;
			break;
		}
	}

	action_SwitchProcess = CreateSwitchAction(emMSGGroupProcess);
	action_SwitchFile = CreateSwitchAction(emMSGGroupFile);
	action_SwitchRegistry = CreateSwitchAction(emMSGGroupRegistry);
	action_SwitchNetwork = CreateSwitchAction(emMSGGroupSocket);
}
//******************************************************************************
void UIToolBar::LoadConfig(void)
{
	action_SwitchProcess->setChecked(g_Config->IsMSGGroupEnable(emMSGGroupProcess));
	action_SwitchFile->setChecked(g_Config->IsMSGGroupEnable(emMSGGroupFile));
	action_SwitchRegistry->setChecked(g_Config->IsMSGGroupEnable(emMSGGroupRegistry));
	action_SwitchNetwork->setChecked(g_Config->IsMSGGroupEnable(emMSGGroupSocket));
}
//******************************************************************************
QAction* UIToolBar::CreateSwitchAction(int Group)
{
	auto action = new QAction(this);
	action->setObjectName(QString("action_Switch") + QStringFrom(g_MSGInfo->GetGroupName(Group)));
	action->setCheckable(true);
	action->setIcon(GetVisionService()->GetGroupIcon(Group));

	auto btn = new QToolButton(m_ToolBar);
	btn->setCheckable(true);
	btn->setAutoRaise(true);
	btn->setArrowType(Qt::NoArrow);
	btn->setDefaultAction(action);

	m_ToolBar->insertWidget(action_Colorful, btn);
	m_ToolBar->insertSeparator(action_Colorful);

	connect(action, &QAction::triggered, [Group](bool checked) {
		g_Config->SetMSGGroupEnable(Group, checked);
		g_RuleManager->OnRuleChanged(false);
	});

	action->setChecked(g_Config->IsMSGGroupEnable(Group));

	return action;
}
//******************************************************************************
