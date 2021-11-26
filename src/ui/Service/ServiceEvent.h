//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __ServiceEvent_A45F7CF3_AA34_4198_A455_5D53939B2108__
#define __ServiceEvent_A45F7CF3_AA34_4198_A455_5D53939B2108__
//******************************************************************************
enum emServiceEvent {
	emServiceEventError = 1,
	emServiceEventMSGUpdate,
	emServiceEventMSGClear,
	emServiceEventRuleBeginApply,
	emServiceEventRuleFinishApply,
};
//******************************************************************************
template<emServiceEvent type>
struct ServiceEvent
{
	static constexpr auto NAME = type;
};
//******************************************************************************
struct ServiceEventError : public ServiceEvent<emServiceEventError>
{
	ServiceEventError(ULONG err, const char* msg)
		: Error(err)
		, Message(msg)
	{
	}

	ULONG Error;
	const char* Message;
};
//******************************************************************************
struct ServiceEventMSGUpdate : public ServiceEvent<emServiceEventMSGUpdate>
{
	bool Reset;
	ULONG Count;
	ULONG TotalCount;
};
//******************************************************************************
#endif
