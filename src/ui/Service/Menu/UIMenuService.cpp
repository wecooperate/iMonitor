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
#include "UIMenuService.h"
//******************************************************************************
bool UIMenuService::InitContextMenu(int row, int column, Menu* menu)
{
	auto msg = GetMessageService()->GetItem(row);
	auto msg_column = GetMessageService()->GetColumn(column);

	AddMessageMenu(menu, msg, msg_column.get());

	for (auto& it : m_ContextDelegates)
		it.second(row, column, menu);

	return true;
}
//******************************************************************************
bool UIMenuService::InitHeadMenu(int column, Menu* menu)
{
	for (auto& it : m_HeadDelegates)
		it.second(column, menu);

	return true;
}
//******************************************************************************
int UIMenuService::InsertContextMenuDelegate(std::function<void(int, int, Menu*)> delegate)
{
	if (!delegate)
		return 0;

	auto id = ++m_IdIndex;

	m_ContextDelegates.insert(std::make_pair(id, delegate));

	return id;
}
//******************************************************************************
int UIMenuService::InsertHeadMenuDelegate(std::function<void(int, Menu*)> delegate)
{
	if (!delegate)
		return 0;

	auto id = ++m_IdIndex;

	m_HeadDelegates.insert(std::make_pair(id, delegate));

	return id;
}
//******************************************************************************
void UIMenuService::RemoteDelegate(int id)
{
	m_ContextDelegates.erase(id);
	m_HeadDelegates.erase(id);
}
//******************************************************************************
void UIMenuService::AddMessageMenu(Menu* menu, IMessage* msg, IMessageColumn* column)
{
	if (msg) {
		int field = column->GetFieldIndex(msg);

		menu->addAction("Properties", [msg]() {
			g_UIManager->Show(SCHEME_PROPERTIES_VIEW, false, msg);
		});

		menu->addSeparator();
		menu->addAction(g_res->icon_locate, "Locate", [msg]() {
			g_PathLocate->Locate(msg->GetLocatePath());
		});

		//
		// Copy
		//
		menu->addSeparator();

		InsertCopyMenu(false, menu, msg, field);

		auto copy_menu = menu->addMenu("Copy");

		for (ULONG i = emMSGFieldCurrentProcessName; i < msg->GetMSGInfo().FieldCount; i++) {
			InsertCopyMenu(true, copy_menu, msg, i);
		}

		menu->addAction("Copy Event", [this, msg]() {
			CString str;
			for (ULONG i = emMSGFieldCurrentProcessName; i < msg->GetMSGInfo().FieldCount; i++) {
				if (!str.IsEmpty()) {
					str.Append(_T("\n"));
				}
				str.AppendFormat(_T("%30s : %s"), msg->GetFieldName(i), msg->GetString(i));
			}
			qApp->clipboard()->setText(QStringFrom(str));
		});

		//
		// Include
		//
		menu->addSeparator();

		if (field != emMSGFieldDetail && field != emMSGFieldInvalid) {
			InsertRuleMenu(true, false, menu, msg, field);
		}

		auto include_menu = menu->addMenu("Include");

		for (ULONG i = emMSGFieldPath + 1; i < msg->GetMSGInfo().FieldCount; i++) {
			InsertRuleMenu(true, true, include_menu, msg, i);
		}

		//
		// Exclude
		//
		menu->addSeparator();

		if (field != emMSGFieldDetail && field != emMSGFieldInvalid) {
			InsertRuleMenu(false, false, menu, msg, field);
		}

		auto exclude_menu = menu->addMenu("Exclude");

		for (ULONG i = emMSGFieldPath + 1; i < msg->GetMSGInfo().FieldCount; i++) {
			InsertRuleMenu(false, true, exclude_menu, msg, i);
		}

		menu->addAction("Execute Events Before", [this, msg]() {
			g_RuleManager->InsertRule(cxRuleMatcher(emOperatorNumberLess, emMSGFieldSeqId, msg->m_SeqId), false);
		});

		menu->addAction("Execute Events After", [this, msg]() {
			g_RuleManager->InsertRule(cxRuleMatcher(emOperatorNumberGreater, emMSGFieldSeqId, msg->m_SeqId), false);
		});
	}

	menu->addSeparator();

	if (g_RuleManager->HasLastRule()) {
		menu->addAction("Remove Last Rule", [this]() {
			g_RuleManager->RemoteLastRule();
		});
	}

	menu->addAction("Remove All Included Rule", [this]() {
		g_RuleManager->RemoveAllIncludeRules();
	});

	menu->addAction("Remove All Excluded Rule", [this]() {
		g_RuleManager->RemoveAllExcludeRules();
	});

	menu->addAction("Remove All Rule", [this]() {
		g_RuleManager->RemoteAllRules();
	});

	menu->addAction("Disable All Rule", [this]() {
		g_RuleManager->DisableAllRules();
	});

	menu->addSeparator();

	menu->addAction("EditFilter", []() {
		g_UIManager->Show(SCHEME_FILTER_EDIT_VIEW, true);
	});
}
//******************************************************************************
void UIMenuService::InsertCopyMenu(bool IsSubMenu, Menu* menu, IMessage* msg, int field)
{
	CString field_name = msg->GetFieldName(field);
	CString field_value = msg->GetString(field);

	if (field_value.IsEmpty())
		return;

	QString title;

	if (IsSubMenu) {
		title = QString("%1 : '%2'").arg(QStringFrom(field_name)).arg(QFormatString(field_value));

	} else {
		title = QString("Copy '%1'").arg(QFormatString(field_value));
	}

	menu->addAction(title, [field_value]() {
		qApp->clipboard()->setText(QStringFrom(field_value));
	});
}
//******************************************************************************
void UIMenuService::InsertRuleMenu(bool IsInclude, bool IsSubMenu, Menu* menu, IMessage* msg, int field)
{
	CString field_name = msg->GetFieldName(field);
	CString field_value = msg->GetString(field);

	ULONG type;
	QString title;

	if (IsSubMenu) {
		type = msg->m_Type;
		title = QString("%1 = '%2'").arg(QStringFrom(field_name)).arg(QFormatString(field_value));
	} else {
		type = emMSGAllType;
		title = QString(IsInclude ? tr("Include '%1'") : tr("Exclude '%1'")).arg(QFormatString(field_value));
	}

	menu->addAction(title, [this, IsInclude, field, field_value, type]() {
		g_RuleManager->InsertRule(cxRuleMatcher(emOperatorStringEqual, field, field_value, type), IsInclude);
	});
}
//******************************************************************************
