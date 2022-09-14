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
#include "Plugin.h"
#include "Language.h"
//******************************************************************************
#include <iMonitorProtocolSDK.h>
//******************************************************************************
const std::vector<IMessageColumn*>& GetColumns(void)
{
	static std::vector<IMessageColumn*> columns = {
		new cxMessageColumnProcessBehavior(),
	};

	return columns;
}
//******************************************************************************
cxMessageColumnProcessBehavior::cxMessageColumnProcessBehavior(void)
	: cxMessageColumnBase(tr("ProcessBehavior"), tr("Detecting if it is a behavior that needs attention"), 100)
{
}
//******************************************************************************
String cxMessageColumnProcessBehavior::GetString(IMessage* Message)
{
	CString str;

	switch (Message->GetType()) {
	case emMSGProcessCreate:
		str = tr("CreateProcess");
		break;

	case emMSGThreadCreate:
		if (Message->GetULONG(proto::ThreadCreate::emFieldRemoteThread) != 0 && Message->GetCurrentProcessId() > 4) {
			auto process = GetPluginContext()->ProcessManager->FindProcess(
				Message->GetULONG(proto::ThreadCreate::emFieldProcessId),
				Message->GetTime());
			if (process && process->GetParentProcessId() != Message->GetCurrentProcessId()) {
				str = tr("CreateRemoteThread");
			}
		}
		break;

	case emMSGFilePostCreate:
		if (Message->GetULONG(proto::FilePostCreate::emFieldInformation) == 2) {
			str = tr("CreateNewFile");
		}
		break;

	case emMSGFilePostRename:
		str = tr("RenameFile");
		break;

	case emMSGFilePostWrite:
		str = tr("ModifiyFile");
		break;

	case emMSGRegPostSetValue:
		str = tr("ModifyRegistry");
		break;

	case emMSGSocketPostConnect:
	case emMSGSocketSendTo:
	case emMSGHTTPRequest:
		str = tr("AccessNetwork");
		break;

	default:
		break;
	}

	return str;
}
//******************************************************************************
