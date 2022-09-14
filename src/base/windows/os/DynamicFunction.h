//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __DynamicFunction_H__
#define __DynamicFunction_H__
//******************************************************************************
// clang-format off
//******************************************************************************
#define BEGIN_DYNAMIC_FUNCTION_MAP(module, name)								\
		namespace module														\
		{																		\
			static HMODULE module_handle = GetModuleHandle(_T(##name));

#define END_DYNAMIC_FUNCTION_MAP() };

#define DYNAMIC_FUNCTION_MAP_EX(name, function_name, default_result)			\
		template<typename...Args>												\
		inline auto name(Args&&...args)											\
		{																		\
			typedef decltype(::name)* PFN;										\
			static PFN pfn = (PFN)GetProcAddress(module_handle, function_name);	\
			if (!pfn)															\
				return default_result;											\
			return pfn(forward<Args>(args)...);									\
		}

#define DYNAMIC_FUNCTION_MAP(name, default_result) DYNAMIC_FUNCTION_MAP_EX(name, #name, default_result)
//******************************************************************************
BEGIN_DYNAMIC_FUNCTION_MAP(mod_kernel32, "kernel32.dll")
	DYNAMIC_FUNCTION_MAP(IsWow64Process, FALSE)
	DYNAMIC_FUNCTION_MAP(Wow64DisableWow64FsRedirection, FALSE)
	DYNAMIC_FUNCTION_MAP(Wow64RevertWow64FsRedirection, FALSE)
	DYNAMIC_FUNCTION_MAP(QueryFullProcessImageNameW, FALSE)
	DYNAMIC_FUNCTION_MAP(GetProductInfo, FALSE)
END_DYNAMIC_FUNCTION_MAP()
//******************************************************************************
BEGIN_DYNAMIC_FUNCTION_MAP(mod_version, "version.dll")
	DYNAMIC_FUNCTION_MAP(GetFileVersionInfoExW, FALSE)
	DYNAMIC_FUNCTION_MAP(GetFileVersionInfoSizeExW, (DWORD)-1)
END_DYNAMIC_FUNCTION_MAP()
//******************************************************************************
#endif
