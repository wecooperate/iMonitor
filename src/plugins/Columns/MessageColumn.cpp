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
		new cxMessageColumnDir(),
		new cxMessageColumnFilename()
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
//******************************************************************************
cxMessageColumnFilename::cxMessageColumnFilename(void)
	: cxMessageColumnBase(_T("File/Folder Name"), _T("File/Folder name of path"), 200)
{
}
//******************************************************************************
String cxMessageColumnFilename::GetString(IMessage* Message)
{
	ULONG type = Message->GetType();

	if (type > emMSGProcess && type < emMSGRegistry)
	{
			String str;
			str.Format(_T("%s"), Message->GetString(proto::FileQueryOpen::emFieldPath));
			int nPos = str.ReverseFind('\\');
			String fullName = str.Right(str.GetLength() - nPos - 1);
			return fullName;
	}
	return String();
}
//******************************************************************************
//******************************************************************************
cxMessageColumnDir::cxMessageColumnDir(void)
	: cxMessageColumnBase(_T("Dir"), _T("Directory of path"), 200)
{
}
//******************************************************************************
String cxMessageColumnDir::GetString(IMessage* Message)
{
	ULONG type = Message->GetType();

	if (type > emMSGProcess && type < emMSGRegistry)
	{
		String str;
		str.Format(_T("%s"), Message->GetString(proto::FileQueryOpen::emFieldPath));
		int nPos = str.ReverseFind('\\');
		String fullName = str.Left(nPos);
		return fullName;
	}
	return String();
}
//******************************************************************************
