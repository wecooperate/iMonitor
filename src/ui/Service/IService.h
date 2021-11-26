//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __IService_7578747C_2A2E_42C2_9270_35C25EAC3254__
#define __IService_7578747C_2A2E_42C2_9270_35C25EAC3254__
//******************************************************************************
interface IService;
interface IServiceManager;
//******************************************************************************
interface IServiceEventHandler
{
	virtual void OnEvent(int32_t event, void* data) = 0;
};
//******************************************************************************
interface IServiceEventManager
{
	virtual void RegisterHandler(int32_t event, IServiceEventHandler * handler) = 0;
	virtual void UnregisterHandler(int32_t event, IServiceEventHandler * handler) = 0;
	virtual void FireEvent(int32_t event, void* data) = 0;
};
//******************************************************************************
interface IService : public IServiceEventHandler
{
	virtual ~IService(void) = default;

	virtual void Initialize(IServiceManager * service_manager) = 0;
	virtual void Uninitialize(void) = 0;
};
//******************************************************************************
interface IServiceManager : public IServiceEventManager
{
	virtual ~IServiceManager(void) = default;

	virtual IService* GetService(const char* name) const = 0;
};
//******************************************************************************
IServiceManager* ServiceManagerInstance();
//******************************************************************************
#endif
