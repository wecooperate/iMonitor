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
interface IRuleCallback
{
	enum emMatchStatus {
		emMatchStatusBreak,
		emMatchStatusContinue,
	};

	virtual void			OnBeginMatch		(IMonitorMessage* Message) {}
	virtual void			OnFinishMatch		(IMonitorMessage* Message) {}
	virtual emMatchStatus	OnMatch				(IMonitorMessage* Message, const char* GroupName, const char* RuleName, ULONG Action, const char* ActionParam) = 0;
};
//******************************************************************************
interface __declspec(uuid("51237525-2811-4BE2-A6A3-D8889E0D0CA1")) IRuleService : public IUnknown
{
	virtual void			Match				(IMonitorMessage* Message, IRuleCallback* Callback) = 0;
};
//******************************************************************************
interface IAgentChannel
{
	struct Address {
		ULONG				IP;
		USHORT				Port;
	};

	virtual ULONG			LocalGetProcessId	(void) = 0;
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
interface IAgentCallback
{
	virtual void			OnCreate			(IAgentChannel* Channel) {}

	virtual void			OnLocalConnect		(IAgentChannel* Channel) {}
	virtual bool			OnLocalSSLHello		(IAgentChannel* Channel, const char* ServerName) { return true; }
	virtual void			OnLocalReceive		(IAgentChannel* Channel, const char* Data, size_t Length) {}
	virtual void			OnLocalError		(IAgentChannel* Channel, const char* Error) {}
	virtual void			OnLocalDisconnect	(IAgentChannel* Channel) {}

	virtual bool			OnRemotePreConnect	(IAgentChannel* Channel) { return true; }
	virtual bool			OnRemoteSSLVerify	(IAgentChannel* Channel, bool PreVerified) { return PreVerified; }
	virtual void			OnRemoteConnect		(IAgentChannel* Channel) {}
	virtual void			OnRemoteReceive		(IAgentChannel* Channel, const char* Data, size_t Length) {}
	virtual void			OnRemoteError		(IAgentChannel* Channel, const char* Error) {}
	virtual void			OnRemoteDisconnect	(IAgentChannel* Channel) {}

	virtual void			OnClose				(IAgentChannel* Channel) {}
};
//******************************************************************************
interface __declspec (uuid("51237525-2811-4BE2-A6A3-D8889E0D0CA0")) IAgentService : public IUnknown
{
	virtual bool			Agent				(IMonitorMessage* Message, IAgentCallback* Callback, bool SSL = false) = 0;
};
//******************************************************************************
#endif
