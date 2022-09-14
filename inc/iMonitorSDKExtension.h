//******************************************************************************
/*++
	FileName:		iMonitorSDKExtension.h
	Description:

--*/
//******************************************************************************
#ifndef __iMonitorSDKExtension_h_15a0ead5_1c5f_498a_a77b_c1bc22b46f2b__
#define __iMonitorSDKExtension_h_15a0ead5_1c5f_498a_a77b_c1bc22b46f2b__
//******************************************************************************
// clang-format off
//******************************************************************************
interface IMonitorMessage;
//******************************************************************************
interface IMonitorRuleCallback
{
	enum emMatchStatus {
		emMatchStatusBreak,
		emMatchStatusContinue,
	};

	struct MatchResult {
		ULONG				Action;
		const char*			ActionParam;
		const char*			GroupName;
		const char*			RuleName;
	};

	virtual void			OnBeginMatch		(IMonitorMessage* Message) {}
	virtual void			OnFinishMatch		(IMonitorMessage* Message) {}
	virtual emMatchStatus	OnMatch				(IMonitorMessage* Message, const MatchResult& Result) = 0;
};
//******************************************************************************
interface __declspec(uuid("51237525-2811-4BE2-A6A3-D8889E0D0CA1")) IMonitorRuleEngine : public IUnknown
{
	virtual void			Match				(IMonitorMessage* Message, IMonitorRuleCallback* Callback) = 0;
	virtual void			EnumAffectedMessage	(void(*Callback)(ULONG Type, void* Context), void* Context) = 0;
};
//******************************************************************************
interface IMonitorAgentChannel
{
	struct Binary {
		PVOID				Data;
		ULONG				Length;
	};

	struct Address {
		ULONG				IP;
		USHORT				Port;
	};

	virtual ULONG			LocalGetProcessId	(void) = 0;
	virtual ULONG			LocalGetThreadId	(void) = 0;
	virtual Binary			LocalGetCallstack	(void) = 0;
	virtual Address			LocalGetAddress		(void) = 0;
	virtual void			LocalSetAutoSend	(bool Enable) = 0;
	virtual void			LocalSetAutoReceive	(bool Enable) = 0;
	virtual bool			LocalSend			(const char* Data, size_t Length) = 0;
	virtual void			LocalReceive		(void) = 0;
	virtual void			LocalDisconnect		(void) = 0;

	virtual bool			RemoteSetAddress	(ULONG IP, USHORT Port) = 0;
	virtual Address			RemoteGetAddresss	(void) = 0;
	virtual void			RemoteSetAutoSend	(bool Enable) = 0;
	virtual void			RemoteSetAutoReceive(bool Enable) = 0;
	virtual bool			RemoteSend			(const char* Data, size_t Length) = 0;
	virtual void			RemoteReceive		(void) = 0;
	virtual void			RemoteDisconnect	(void) = 0;

	virtual void			SetContext			(void* Context) = 0;
	virtual void*			GetContext			(void) = 0;
	virtual bool			SSLRestartAgent		(void) = 0;
	virtual bool			SSLIsRestartAgent	(void) = 0;
	virtual bool			SSLIsFallback		(void) = 0;
	virtual void			Close				(void) = 0;
};
//******************************************************************************
interface IMonitorAgentCallback
{
	virtual void			OnCreate			(IMonitorAgentChannel* Channel) {}

	virtual void			OnLocalConnect		(IMonitorAgentChannel* Channel) {}
	virtual bool			OnLocalSSLHello		(IMonitorAgentChannel* Channel, const char* ServerName) { return true; }
	virtual void			OnLocalReceive		(IMonitorAgentChannel* Channel, const char* Data, size_t Length) {}
	virtual void			OnLocalError		(IMonitorAgentChannel* Channel, const char* Error) {}
	virtual void			OnLocalDisconnect	(IMonitorAgentChannel* Channel) {}

	virtual bool			OnRemotePreConnect	(IMonitorAgentChannel* Channel) { return true; }
	virtual bool			OnRemoteSSLVerify	(IMonitorAgentChannel* Channel, bool PreVerified) { return PreVerified; }
	virtual void			OnRemoteConnect		(IMonitorAgentChannel* Channel) {}
	virtual void			OnRemoteReceive		(IMonitorAgentChannel* Channel, const char* Data, size_t Length) {}
	virtual void			OnRemoteError		(IMonitorAgentChannel* Channel, const char* Error) {}
	virtual void			OnRemoteDisconnect	(IMonitorAgentChannel* Channel) {}

	virtual void			OnClose				(IMonitorAgentChannel* Channel) {}
};
//******************************************************************************
interface __declspec (uuid("51237525-2811-4BE2-A6A3-D8889E0D0CA0")) IMonitorAgentEngine : public IUnknown
{
	virtual bool			Agent				(IMonitorMessage* Message, IMonitorAgentCallback* Callback, bool SSL = false) = 0;
};
//******************************************************************************
#endif
