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
#include "UIManager.h"
//******************************************************************************
#include "Service/Config/UIConfigService.h"
#include "Service/Vision/UIVisionService.h"
#include "Service/Message/UIMessageService.h"
#include "Service/Menu/UIMenuService.h"
//******************************************************************************
#include "UIMain.h"
#include "View/UIMessageProperties.h"
#include "View/Filter/UIFilterEditView.h"
#include "View/UISettingView.h"
//******************************************************************************
IServiceManager* ServiceManagerInstance()
{
	return g_UIManager;
}
//******************************************************************************
UIManager::UIManager(void)
{
	connect(
		this, &UIManager::UIExecute, this, [](std::function<void()> Runnable) {
			Runnable();
		},
		Qt::BlockingQueuedConnection);

	RegisterService<UIConfigService>();
	RegisterService<UIVisionService>();
	RegisterService<UIMessageService>();
	RegisterService<UIMenuService>();

	RegisterViewCreator<UIMain>(SCHEME_MAIN_VIEW);
	RegisterViewCreator<UIMessageProperties>(SCHEME_PROPERTIES_VIEW, false);
	RegisterViewCreator<UIFilterEditView>(SCHEME_FILTER_EDIT_VIEW, false);
	RegisterViewCreator<UISettingView>(SCHEME_SETTING_VIEW, false);
}
//******************************************************************************
void UIManager::Initialize(void)
{
	m_Initialized = true;

	for (auto& it : m_Services) {
		it.second->Initialize(this);
	}

	Show(SCHEME_MAIN_VIEW);
}
//******************************************************************************
void UIManager::Uninitialize(void)
{
	m_Initialized = false;

	for (auto& it : m_Services) {
		it.second->Uninitialize();
	}

	for (auto& it : m_ViewCreators) {
		if (it.second.Instance) {
			it.second.Instance->deleteLater();
		}
	}

	m_EventHandlers.clear();
}
//******************************************************************************
void UIManager::RegisterService(const char* name, IService* service)
{
	if (!name || !service)
		return;

	m_Services.insert(std::make_pair(name, service));
}
//******************************************************************************
IService* UIManager::GetService(const char* name) const
{
	auto it = m_Services.find(name);

	return it == m_Services.end() ? nullptr : it->second.get();
}
//******************************************************************************
QWidget* UIManager::GetView(const char* name)
{
	auto it = m_ViewCreators.find(name);

	if (it != m_ViewCreators.end()) {
		auto& creator = it->second;

		if (!creator.Singleton) {
			auto widget = creator.Create();
			widget->setAttribute(Qt::WA_DeleteOnClose, true);
			return widget;
		}

		if (!creator.Instance) {
			creator.Instance = creator.Create();
		}

		return creator.Instance;
	}

	return nullptr;
}
//******************************************************************************
bool UIManager::IsUIThreand(void)
{
	return m_CurrentThreadId == std::this_thread::get_id();
}
//******************************************************************************
void UIManager::RegisterHandler(int32_t event, IServiceEventHandler* handler)
{
	for (auto it = m_EventHandlers.lower_bound(event); it != m_EventHandlers.upper_bound(event); it++) {
		if (it->second == handler)
			return;
	}

	m_EventHandlers.insert(std::make_pair(event, handler));
}
//******************************************************************************
void UIManager::UnregisterHandler(int32_t event, IServiceEventHandler* handler)
{
	for (auto it = m_EventHandlers.begin(); it != m_EventHandlers.end();) {
		if (it->second == handler) {
			if (event == 0 || event == it->first) {
				it = m_EventHandlers.erase(it);
				continue;
			}
		}
		it++;
	}
}
//******************************************************************************
void UIManager::FireEvent(int32_t event, void* data)
{
	if (!m_Initialized)
		return;

	if (!IsUIThreand()) {
		emit UIExecute([&]() {
			FireEvent(event, data);
		});
		return;
	}

	for (auto it = m_EventHandlers.lower_bound(event); it != m_EventHandlers.upper_bound(event); it++) {
		it->second->OnEvent(event, data);
	}
}
//******************************************************************************
void UIManager::Show(const char* name, bool modal, IMessage* msg)
{
	auto view = GetView(name);

	if (0 != strcmp(name, SCHEME_MAIN_VIEW)) {
		view->setParent(GetView(SCHEME_MAIN_VIEW), Qt::Window);
	}

	if (modal) {
		if (auto dialog = qobject_cast<QDialog*>(view)) {
			dialog->setModal(true);
		}
	}

	if (msg) {
		view->setProperty("msg", QVariant::fromValue((void*)msg));
	}

	view->show();
}
//******************************************************************************
