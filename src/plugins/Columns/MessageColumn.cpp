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
//******************************************************************************
#include <iMonitorProtocolSDK.h>
//******************************************************************************
const std::vector<IMessageColumn*>& GetColumns(void)
{
	static std::vector<IMessageColumn*> columns = {
		new cxMessageColumnLocalAddress(),
		new cxMessageColumnRemoteAddress(),
	};

	return columns;
}
//******************************************************************************
cxMessageColumnLocalAddress::cxMessageColumnLocalAddress(void)
	: cxMessageColumnBase(_T("LocalAddress"), _T("Local Address of socket"), 200)
{
}
//******************************************************************************
String cxMessageColumnLocalAddress::GetString(IMessage* Message)
{
	switch (Message->GetType()) {
	case emMSGSocketPostConnect:
	case emMSGSocketSend:
	case emMSGSocketSendTo:
	case emMSGSocketPostRecv:
	case emMSGSocketPostRecvFrom:
	case emMSGSocketPostAccept: {
		String str;
		str.Format(_T("%s:%s"),
			Message->GetString(proto::SocketSend::emFieldLocalIP),
			Message->GetString(proto::SocketSend::emFieldLocalPort));
		return str;
	} break;

	default:
		break;
	}

	return String();
}
//******************************************************************************
cxMessageColumnRemoteAddress::cxMessageColumnRemoteAddress(void)
	: cxMessageColumnBase(_T("RemoteAddress"), _T("Remote Address of socket"), 200)
{
}
//******************************************************************************
String cxMessageColumnRemoteAddress::GetString(IMessage* Message)
{
	switch (Message->GetType()) {
	case emMSGSocketPostConnect:
	case emMSGSocketSend:
	case emMSGSocketSendTo:
	case emMSGSocketPostRecv:
	case emMSGSocketPostRecvFrom:
	case emMSGSocketPostAccept: {
		String str;
		str.Format(_T("%s:%s"),
			Message->GetString(proto::SocketSend::emFieldIP),
			Message->GetString(proto::SocketSend::emFieldPort));
		return str;
	} break;

	case emMSGHTTPRequest: {
		String str;
		str.Format(_T("%s:%s"),
			Message->GetString(proto::HTTPRequest::emFieldIP),
			Message->GetString(proto::HTTPRequest::emFieldPort));
		return str;
	} break;

	default:
		break;
	}

	return String();
}
//******************************************************************************
