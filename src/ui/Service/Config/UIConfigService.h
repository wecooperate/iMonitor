//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIConfigService_77BB3538_2319_4E04_831D_63AD1A694138__
#define __UIConfigService_77BB3538_2319_4E04_831D_63AD1A694138__
//******************************************************************************
#include "../Service.h"
//******************************************************************************
class UIConfigService : public UIServiceImpl<IConfigService>
{
public:
	UIConfigService(void);

public:
	bool SetSectionInt(const char* section, const char* entry, int data) override;
	bool SetSectionString(const char* section, const char* entry, const char* data) override;
	bool SetSectionBinary(const char* section, const char* entry, void* data, int length) override;
	bool SetSectionByteArray(const char* section, const char* entry, const QByteArray& bytes) override;

	int GetSectionInt(const char* section, const char* entry, int default_value = 0) override;
	std::string GetSectionString(const char* section, const char* entry, const char* default_value = "") override;
	std::string GetSectionBinary(const char* section, const char* entry) override;
	QByteArray GetSectionByteArray(const char* section, const char* entry) override;

protected:
	QString GetKeyName(const char* section, const char* entry);

protected:
	std::unique_ptr<QSettings> m_settings;
};
//******************************************************************************
#endif
