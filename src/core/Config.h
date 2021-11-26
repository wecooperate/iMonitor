//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __Config_224A9956_A4C5_460D_853A_0D1E4916DA98__
#define __Config_224A9956_A4C5_460D_853A_0D1E4916DA98__
//******************************************************************************
interface IConfig
{
	virtual bool SetSectionInt(const char* section, const char* entry, int data) = 0;
	virtual bool SetSectionString(const char* section, const char* entry, const char* data) = 0;
	virtual bool SetSectionBinary(const char* section, const char* entry, void* data, int length) = 0;
	virtual int GetSectionInt(const char* section, const char* entry, int default_value = 0) = 0;
	virtual std::string GetSectionString(const char* section, const char* entry, const char* default_value = "") = 0;
	virtual std::string GetSectionBinary(const char* section, const char* entry) = 0;
};
//******************************************************************************
class cxConfig
{
#define g_Config SINGLETON_(cxConfig)

public:
	enum emUserConfigSwitch {
		emSwitchCapture,
		emSwitchAutoScroll,
		emSwitchColorful,
		emSwitchShowStatusBar,
		emSwitchMax,
	};

public:
	cxConfig(void);

public:
	void LoadConfig(IConfig* Config);
	void SaveConfig(IConfig* Config);

public:
	bool GetSwitch(emUserConfigSwitch Switch);
	void SetSwitch(emUserConfigSwitch Switch, bool Enable);

#define DECLARE_SWITCH_PROPERTY(name)                                                       \
	__declspec(property(get = GetSwitch##name, put = SetSwitch##name)) bool IsEnable##name; \
	bool GetSwitch##name() { return GetSwitch(emSwitch##name); }                            \
	void SetSwitch##name(bool Enable) { SetSwitch(emSwitch##name, Enable); }

	DECLARE_SWITCH_PROPERTY(Capture)
	DECLARE_SWITCH_PROPERTY(AutoScroll)
	DECLARE_SWITCH_PROPERTY(Colorful)
	DECLARE_SWITCH_PROPERTY(ShowStatusBar)

#undef DECLARE_SWITCH_PROPERTY

public:
	bool IsMSGEnable(ULONG Type);
	bool IsMSGGroupEnable(ULONG GroupType);
	void SetIsUniqueMessage(bool enable);
	void SetMSGGroupEnable(ULONG GroupType, bool Enable);

protected:
	bool m_SwitchTable[emSwitchMax];
};
//******************************************************************************
#endif
