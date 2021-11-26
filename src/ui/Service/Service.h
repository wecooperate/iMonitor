//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __Service_1C5E6A1B_B510_4F8F_8053_F53DB676B8BA__
#define __Service_1C5E6A1B_B510_4F8F_8053_F53DB676B8BA__
//******************************************************************************
#include "stdafx.h"
#include "IService.h"
#include "IConfigService.h"
#include "IMessageService.h"
#include "IVisionService.h"
#include "IMenuService.h"
//******************************************************************************
#include "ServiceEvent.h"
//******************************************************************************
#define DECLARE_SERVICE_(name) \
	inline I##name##Service* Get##name##Service() const { return GetService<I##name##Service>(); }
#define DECLARE_ALL_SERVICE() \
	DECLARE_SERVICE_(Config)  \
	DECLARE_SERVICE_(Message) \
	DECLARE_SERVICE_(Vision)  \
	DECLARE_SERVICE_(Menu)    \
	/* DECLARE_ALL_SERVICE */
//******************************************************************************
template<typename TBase>
class ServiceClient : public TBase
{
public:
	static constexpr auto SERVICE_ALL_EVENT = 0;

public:
	~ServiceClient()
	{
		if (m_ServiceManager) {
			m_ServiceManager->UnregisterHandler(SERVICE_ALL_EVENT, this);
		}
	}

public:
	template<typename T>
	inline T* GetService() const
	{
		static T* service = dynamic_cast<T*>(m_ServiceManager->GetService(T::NAME));

		return service;
	}

	DECLARE_ALL_SERVICE()

public:
	void OnEvent(int32_t event, void* data) override
	{
		auto it = m_EventHandlers.find(event);

		if (it != m_EventHandlers.end()) {
			it->second(data);
		}
	}

	template<typename T>
	void HandleEvent(int32_t event, T&& handler)
	{
		m_ServiceManager->RegisterHandler(event, this);

		if constexpr (lambda_type<T>::arity > 0) {
			m_EventHandlers[event] = [handler](void* data) {
				handler(*(typename lambda_type<T>::arg<0>::type*)data);
			};
		} else {
			m_EventHandlers[event] = [handler](void* data) {
				handler();
			};
		}
	}

	template<typename T>
	inline void HandleEvent(T&& handler)
	{
		if constexpr (lambda_type<T>::arity > 0) {
			HandleEvent(lambda_type<T>::arg<0>::type::NAME, std::move(handler));
		}
	}

	template<typename T>
	inline void FireEvent(T& event)
	{
		if (m_ServiceManager) {
			m_ServiceManager->FireEvent(T::NAME, &event);
		}
	}

	inline void FireEvent(int32_t event)
	{
		if (m_ServiceManager) {
			m_ServiceManager->FireEvent(event, nullptr);
		}
	}

protected:
	IServiceManager* m_ServiceManager = nullptr;
	std::map<int32_t, std::function<void(void*)>> m_EventHandlers;
};
//******************************************************************************
class UIServiceClient : public ServiceClient<IServiceEventHandler>
{
public:
	UIServiceClient()
	{
		m_ServiceManager = ServiceManagerInstance();
	}
};
//******************************************************************************
template<typename TService = IService>
class UIServiceImpl : public ServiceClient<TService>
{
public:
	void Initialize(IServiceManager* service_manager) override
	{
		m_ServiceManager = service_manager;

		Initialize();
	}

	void Uninitialize(void) override
	{
		m_ServiceManager->UnregisterHandler(SERVICE_ALL_EVENT, this);

		m_ServiceManager = nullptr;
	}

	virtual void Initialize(void) {}
};
//******************************************************************************
#endif
