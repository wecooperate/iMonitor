//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "MessageColumn.h"
#include "IPRegion.h"
//******************************************************************************
#include <iMonitorProtocolSDK.h>
//******************************************************************************
const std::vector<IMessageColumn*>& GetColumns(void)
{
	static std::vector<IMessageColumn*> columns = {
		new cxMessageColumnRemoteIPRegion(),
	};

	return columns;
}
//******************************************************************************
cxMessageColumnRemoteIPRegion::cxMessageColumnRemoteIPRegion(void)
	: cxMessageColumnBase(_T("RemoteIPRegion"), _T("Parse socket remote ip address region"), 200)
{
}
//******************************************************************************
String cxMessageColumnRemoteIPRegion::GetString(IMessage* Message)
{
	switch (Message->GetType()) {
	case emMSGSocketPostConnect:
	case emMSGSocketSend:
	case emMSGSocketSendTo:
	case emMSGSocketPostRecv:
	case emMSGSocketPostRecvFrom:
	case emMSGSocketPostAccept:
		return g_IPRegion->GetIPRegion(Message->GetULONG(proto::SocketSend::emFieldIP));

	case emMSGHTTPRequest:
		return g_IPRegion->GetIPRegion(Message->GetULONG(proto::HTTPRequest::emFieldIP));

	default:
		break;
	}

	return String();
}
//******************************************************************************
