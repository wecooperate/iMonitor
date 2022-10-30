//******************************************************************************
/*++
	FileName:		Plugin.h
	Description:

--*/
//******************************************************************************
#ifndef __Plugin_H_BAE6EAAC_6C89_493D_85DE_5DA8922942DA__
#define __Plugin_H_BAE6EAAC_6C89_493D_85DE_5DA8922942DA__
//******************************************************************************
// clang-format off
//******************************************************************************
#include "iMonitorSDK.h"
//******************************************************************************
namespace iMonitor {
//******************************************************************************
// Plugin Implement Interfaces
//******************************************************************************
interface IMessageMatcher;
interface IMessageColumn;
interface IPlugin;
//******************************************************************************
// PluginManager Provider Interfaces
//******************************************************************************
interface IMessage;
interface IMessageCallstack;
interface IMessageProcessModule;
interface IMessageProcess;
interface IMessageProcessManager;
interface IMessageFilterManager;
interface IMessageColumnManager;
interface IMessageSymbolManager;
interface IMessageManager;
interface IResourceManager;
interface IConfigurable;
interface IConfigManager;
interface IPluginManager;

interface IUIExtension;
interface IUIManager;
//******************************************************************************
typedef CStringW String;
typedef LPCWSTR ConstString;
typedef emMSGDataType DataType;
typedef ULONG Color;
typedef HICON Icon;
//******************************************************************************
#define IMONITOR_DEFAULT_COLOR Color(-1)
#define IMONITOR_ABI_VERSION 1
//******************************************************************************
struct Binary
{
	PVOID					Data				= nullptr;
	ULONG					Length				= 0;
};
//******************************************************************************
interface IMessage
{
	virtual ULONG			GetType				(void) = 0;
	virtual ULONG			GetIndex			(void) = 0;
	virtual ULONG			GetSeqId			(void) = 0;
	virtual ULONG			GetStatus			(void) = 0;
	virtual ULONG			GetCurrentProcessId	(void) = 0;
	virtual ULONG			GetCurrentThreadId	(void) = 0;
	virtual ULONGLONG		GetTime				(void) = 0;

	virtual String			GetTypeName			(void) = 0;
	virtual ULONG			GetFieldCount		(void) = 0;
	virtual DataType		GetFieldType		(ULONG Index) = 0;
	virtual String			GetFieldName		(ULONG Index) = 0;
	virtual ULONG			GetFieldIndex		(ConstString Name) = 0;

	virtual ULONG			GetULONG			(ULONG Index) = 0;
	virtual ULONGLONG		GetULONGLONG		(ULONG Index) = 0;
	virtual String			GetString			(ULONG Index) = 0;
	virtual Binary			GetBinary			(ULONG Index) = 0;

	virtual IMessageProcess* GetProcess			(void) = 0;
	virtual IMessageCallstack* GetCallstack		(void) = 0;

	inline ULONG			GetGroupType		(void)							{ return MSG_GET_GROUP(GetType()); }
	inline String			GetPath				(void)							{ return GetString(emMSGFieldPath); }
};
//******************************************************************************
interface IMessageColumn
{
	enum ColumnAlign {
		emAlignDefault		= 0,
		emAlignLeft			= 1,
		emAlignRight		= 2,
        emAlignCenter		= 4,
	};

	virtual String			GetName				(void) = 0;
	virtual String			GetDescription		(void) = 0;
	virtual ULONG			GetWidth			(void)							{ return 100; }
	virtual ULONG			GetAlign			(void)							{ return emAlignDefault; }
	virtual ULONG			GetMessageType		(void)							{ return 0; }

	virtual DataType		GetDataType			(IMessage* Message) = 0;
	virtual ULONG			GetULONG			(IMessage* Message) = 0;
	virtual ULONGLONG		GetULONGLONG		(IMessage* Message) = 0;
	virtual String			GetString			(IMessage* Message) = 0;
	virtual Binary			GetBinary			(IMessage* Message) = 0;

	virtual	Color			GetBackgroundColor	(IMessage* Message)				{ return IMONITOR_DEFAULT_COLOR; }
	virtual Color			GetTextColor		(IMessage* Message)				{ return IMONITOR_DEFAULT_COLOR; }
	virtual String			GetToolTips			(IMessage* Message)				{ return String(); }
	virtual Icon			GetIcon				(IMessage* Message)				{ return Icon(); }
};
//******************************************************************************
interface IMessageColumnManager
{
	virtual void			EnumAllColumn		(bool (*Callback)(IMessageColumn*, PVOID), PVOID Context) = 0;
	virtual void			EnumCommonColumn	(bool (*Callback)(IMessageColumn*, PVOID), PVOID Context) = 0;
	virtual void			EnumTypeColumn		(ULONG Type, bool (*Callback)(IMessageColumn*, PVOID), PVOID Context) = 0;

	virtual IMessageColumn* GetColumn			(ConstString Name) = 0;
	virtual ULONG			GetCommonColumnCount(void) = 0;
	virtual IMessageColumn* GetCommonColumn		(ULONG Index) = 0;
	virtual ULONG			GetTypeColumnCount	(ULONG Type) = 0;
	virtual IMessageColumn* GetTypeColumn		(ULONG Type, ULONG Index) = 0;

	virtual DataType		GetDataType			(IMessage* Message, ConstString Name) = 0;
	virtual ULONG			GetULONG			(IMessage* Message, ConstString Name) = 0;
	virtual ULONGLONG		GetULONGLONG		(IMessage* Message, ConstString Name) = 0;
	virtual String			GetString			(IMessage* Message, ConstString Name) = 0;
	virtual Binary			GetBinary			(IMessage* Message, ConstString Name) = 0;

	virtual	Color			GetBackgroundColor	(IMessage* Message, ConstString Name) = 0;
	virtual Color			GetTextColor		(IMessage* Message, ConstString Name) = 0;
	virtual String			GetToolTips			(IMessage* Message, ConstString Name) = 0;
	virtual Icon			GetIcon				(IMessage* Message, ConstString Name) = 0;
};
//******************************************************************************
interface IMessageMatcher
{
	virtual String			GetName				(void) = 0;
	virtual String			GetDescription		(void) = 0;

	virtual bool			IsMatch				(IMessage* Message) = 0;
};
//******************************************************************************
interface IMessageFilterManager
{
	virtual void			FireFilterChange	(bool Increase) = 0;

	virtual	bool			IsMatch				(IMessage* Message) = 0;
};
//******************************************************************************
interface IMessageCallstack
{
	virtual ULONG			GetCount			(void) = 0;
	virtual ULONGLONG		GetAddress			(ULONG Index) = 0;
};
//******************************************************************************
interface IMessageProcess
{
	virtual	ULONG			GetProcessId		(void) = 0;
	virtual	ULONG			GetParentProcessId	(void) = 0;
	virtual String			GetProcessPath		(void) = 0;
	virtual String			GetProcessName		(void) = 0;
	virtual	String			GetCommandline		(void) = 0;
	virtual Icon			GetIcon				(void) = 0;
	virtual ULONGLONG		GetCreateTime		(void) = 0;
	virtual ULONGLONG		GetExitTime			(void) = 0;
	virtual String			GetVersionString	(ConstString Type) = 0;
};
//******************************************************************************
interface IMessageProcessModule
{
};
//******************************************************************************
interface IMessageProcessManager
{
	virtual IMessageProcess* FindProcess		(ULONG ProcessId, ULONGLONG Time = 0) = 0;
};
//******************************************************************************
interface IMessageSymbolManager
{
};
//******************************************************************************
interface IMessageManager
{
};
//******************************************************************************
interface IConfigurable
{
	virtual void			LoadConfig			(ConstString ConfigDirectory) = 0;
	virtual void			SaveConfig			(ConstString ConfigDirectory) = 0;
	virtual void			ResetConfig			(void) = 0;
};
//******************************************************************************
interface IGlobalConfig
{
	enum emSwtichConfig {
		emSwitchCapture,
		emSwitchAutoScroll,
		emSwitchColorful,
		emSwitchShowStatusBar,
		emSwitchDropFilteredMessage,
		emSwitchMax,
	};

	virtual	bool			IsMessageEnable		(ULONG Type) = 0;
	virtual void			SetMessageEnable	(ULONG Type, bool Enable) = 0;

	virtual	bool			IsGroupEnable		(ULONG Group) = 0;
	virtual void			SeteGroupEnable		(ULONG Group, bool Enable) = 0;

	virtual bool			GetSwitch			(emSwtichConfig Switch) = 0;
	virtual void			SetSwitch			(emSwtichConfig Switch, bool Enable) = 0;

#define DECLARE_SWITCH_PROPERTY(name)                                                       \
	__declspec(property(get = GetSwitch##name, put = SetSwitch##name)) bool IsEnable##name; \
	inline bool GetSwitch##name() { return GetSwitch(emSwitch##name); }                     \
	inline void SetSwitch##name(bool Enable) { SetSwitch(emSwitch##name, Enable); }

	DECLARE_SWITCH_PROPERTY(Capture)
	DECLARE_SWITCH_PROPERTY(AutoScroll)
	DECLARE_SWITCH_PROPERTY(Colorful)
	DECLARE_SWITCH_PROPERTY(ShowStatusBar)
	DECLARE_SWITCH_PROPERTY(DropFilteredMessage)

#undef DECLARE_SWITCH_PROPERTY
};
//******************************************************************************
interface IConfigManager : public IGlobalConfig
{
	virtual String			GetConfigDirectory	(void) = 0;
};
//******************************************************************************
interface IResourceManager
{
	virtual	HICON			GetGroupIcon		(ULONG Group) = 0;
	virtual Color			GetGroupColor		(ULONG Group) = 0;
};
//******************************************************************************
// Plugin
//******************************************************************************
struct PluginContext
{
	IMessageColumnManager*	ColumnManager		= nullptr;
	IMessageFilterManager*	FilterManager		= nullptr;
	IMessageProcessManager*	ProcessManager		= nullptr;
	IMessageSymbolManager*	SymbolManager		= nullptr;
	IConfigManager*			ConfigManager		= nullptr;
	IResourceManager*		ResourceManager		= nullptr;
	IPluginManager*			PluginManager		= nullptr;

	IUIManager*				UIManager			= nullptr;
};
//******************************************************************************
interface IPlugin
{
	enum emPluginEvent {
		emEventLanguageChange = 1,
	};

	typedef LANGID EventContextLanguageChange;

	virtual ULONG			GetABIVersion		(void) { return IMONITOR_ABI_VERSION; }

	virtual String			GetName				(void) = 0;
	virtual	String			GetDescription		(void) = 0;
	virtual String			GetAuthor			(void) = 0;

	virtual void			Initialize			(PluginContext* Context) = 0;
	virtual void			Release				(void) = 0;

	virtual void			OnEvent				(ULONG Event, PVOID Context)	{}
	virtual IConfigurable*	GetConfigurable		(void)							{ return nullptr; }

	virtual ULONG			GetColumnCount		(void)							{ return 0; }
	virtual IMessageColumn*	GetColumn			(ULONG Index)					{ return nullptr; }
	virtual ULONG			GetMatcherCount		(void)							{ return 0; }
	virtual IMessageMatcher* GetMatcher			(ULONG Index)					{ return nullptr; }
	virtual ULONG			GetRequireEventCount(void)							{ return 0; }
	virtual ULONG			GetRequireEvent		(ULONG Index)					{ return 0; }

	virtual IUIExtension*	GetUIExtension		(void)							{ return nullptr; }
};
//******************************************************************************
interface IPluginManager
{
	virtual	void			EnumPlugins			(bool (*Callback)(IPlugin*, String, PVOID), PVOID Context) = 0;

	virtual IPlugin*		GetPlugin			(ConstString Name) = 0;
	virtual String			GetPluginPath		(ConstString Name) = 0;

	virtual void			FireEvent			(ULONG Event, PVOID EventContext) = 0;
};
//******************************************************************************
extern "C" {
	IPlugin* WINAPI iMonitorCreatePlugin(void);
};
//******************************************************************************
}
//******************************************************************************
#define IMONITOR_DEF_PLUGIN(name, desc)											\
	String		GetName			(void) override { return L##name; }				\
	String		GetDescription	(void) override { return L##desc; }

#define IMONITOR_DEF_MESSAGE_COLUMN(name, display_name, desc, width, type)		\
	String		GetName			(void) override { return L##name; }				\
	String		GetDisplayName	(void) override { return L##display_name; }		\
	String		GetDescription	(void) override { return L##desc; }				\
	ULONG		GetWidth		(void) override { return width; }				\
	DataType	GetDataType		(void) override { return type; }
//******************************************************************************
#endif
