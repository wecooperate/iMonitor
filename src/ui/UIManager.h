//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIManager_h_0b4caf9b_a31d_4429_9feb_02698adb5945__
#define __UIManager_h_0b4caf9b_a31d_4429_9feb_02698adb5945__
//******************************************************************************
#include "UICommon.h"
#include "Service/Service.h"
//******************************************************************************
#define SCHEME_MAIN_VIEW		"iMonitor://Main"
#define SCHEME_PROPERTIES_VIEW	"iMonitor://Property"
#define SCHEME_FILTER_EDIT_VIEW "iMonitor://FilterEdit"
#define SCHEME_SETTING_VIEW     "iMonitor://Setting"
//******************************************************************************
class UIManager
	: public QObject
	, public IServiceManager
{
	Q_OBJECT

#define g_UIManager SINGLETON_(UIManager)

public:
	UIManager(void);

public:
	void Initialize(void);
	void Uninitialize(void);

public:
	void RegisterService(const char* name, IService* service);

	template<typename T>
	void RegisterService()
	{
		RegisterService(T::NAME, new T());
	}

public:
	IService* GetService(const char* name) const override;

	template<typename T>
	inline T* GetService() const
	{
		return dynamic_cast<T*>(GetService(T::NAME));
	}

	DECLARE_ALL_SERVICE()

public:
	void RegisterHandler(int32_t event, IServiceEventHandler* handler) override;
	void UnregisterHandler(int32_t event, IServiceEventHandler* handler) override;
	void FireEvent(int32_t event, void* data) override;

public:
	void Show(const char* name, bool modal = false, IMessage* msg = nullptr);

	QWidget* GetView(const char* name);

	template<typename T>
	T* GetView(const char* name)
	{
		return qobject_cast<T*>(GetView(name));
	}

protected:
	struct ViewCreator
	{
		bool Singleton;
		QWidget* Instance;
		std::function<QWidget*(void)> Create;
	};

	template<typename T>
	void RegisterViewCreator(const char* name, bool singleton = true)
	{
		ViewCreator creator;

		creator.Singleton = singleton;
		creator.Instance = nullptr;
		creator.Create = []() {
			return new UIView<T>();
		};

		m_ViewCreators.insert(std::make_pair(name, std::move(creator)));
	}

protected:
	bool IsUIThreand(void);

signals:
	void UIExecute(std::function<void()> Runnable);

private:
	bool m_Initialized = false;
	std::thread::id m_CurrentThreadId = std::this_thread::get_id();
	std::map<std::string, std::unique_ptr<IService>> m_Services;
	std::multimap<int32_t, IServiceEventHandler*> m_EventHandlers;
	std::map<std::string, ViewCreator> m_ViewCreators;
};
//******************************************************************************
#endif
