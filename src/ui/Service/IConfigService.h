//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __IConfigService_A7914117_FCC8_47BC_9CDD_2DC5B0F852AD__
#define __IConfigService_A7914117_FCC8_47BC_9CDD_2DC5B0F852AD__
//******************************************************************************
interface IConfigService
	: public IService
	, public IConfig
{
	static constexpr auto NAME = "config";

	virtual QByteArray GetSectionByteArray(const char* section, const char* entry) = 0;
	virtual bool SetSectionByteArray(const char* section, const char* entry, const QByteArray& bytes) = 0;

	template<typename T>
	inline void SaveState(T * wnd, const char* name)
	{
		SetSectionByteArray(name, "state", wnd->saveState());
	}

	template<typename T>
	inline void LoadState(T * wnd, const char* name)
	{
		wnd->restoreState(GetSectionByteArray(name, "state"));
	}

	template<typename T>
	inline void SaveGeometry(T * wnd, const char* name)
	{
		SetSectionByteArray(name, "geometry", wnd->saveGeometry());
	}

	template<typename T>
	inline void LoadGeometry(T * wnd, const char* name)
	{
		wnd->restoreGeometry(GetSectionByteArray(name, "geometry"));
	}
};
//******************************************************************************
#endif
