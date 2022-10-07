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

	switch (type) 
	{
		//emMSGTypeProcess
		case emMSGProcessCreate:
		case emMSGProcessExit:
		case emMSGProcessOpen:
		case emMSGThreadCreate:
		case emMSGThreadExit:
		case emMSGThreadOpen:
		case emMSGImageLoad:
		case emMSGProcessStart:
		case emMSGThreadStart:
		//emMSGTypeFile
		case emMSGFileCreate:
		case emMSGFilePostCreate:
		case emMSGFileQueryOpen:
		case emMSGFilePostQueryOpen:
		case emMSGFileCleanup:
		case emMSGFilePostCleanup_nosupport:
		case emMSGFileCreateSection:
		case emMSGFilePostCreateSection:
		case emMSGFileRead:
		case emMSGFilePostRead:
		case emMSGFileWrite:
		case emMSGFilePostWrite:
		case emMSGFileCreateHardLink:
		case emMSGFilePostCreateHardLink:
		case emMSGFileRename:
		case emMSGFilePostRename:
		case emMSGFileDelete:
		case emMSGFilePostDelete:
		case emMSGFileSetSize:
		case emMSGFilePostSetSize:
		case emMSGFileSetBasicInfo:
		case emMSGFilePostSetBasicInfo:
		case emMSGFileFindFile:
		case emMSGFilePostFindFile:
			{
					String str;
					str.Format(_T("%s"), Message->GetString(proto::FileQueryOpen::emFieldPath));
					int nPos = str.ReverseFind('\\');
					String fullName = str.Right(str.GetLength() - nPos - 1);
					return fullName;
				}
				default:
					break;
			}

	return String();
}
//******************************************************************************
