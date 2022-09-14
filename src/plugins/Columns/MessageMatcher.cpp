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
#include "MessageMatcher.h"
//******************************************************************************
const std::vector<IMessageMatcher*>& GetMatchers(void)
{
	static std::vector<IMessageMatcher*> matchers = {
		new cxMessageFileInfoDocumentMatcher(),
		new cxMessageOperationModifiableMatcher(),
	};

	return matchers;
}
//******************************************************************************
iMonitor::String cxMessageFileInfoDocumentMatcher::GetName(void)
{
	return _T("FileInfo.Document");
}
//******************************************************************************
iMonitor::String cxMessageFileInfoDocumentMatcher::GetDescription(void)
{
	return _T("Check if the path is the document file path");
}
//******************************************************************************
bool cxMessageFileInfoDocumentMatcher::IsMatch(IMessage* Message)
{
	auto path = Message->GetPath();
	CString ext = PathFindExtension(path);
	ext.MakeLower();

	static LPCTSTR document_exts[] = {
		_T(".txt"),
		_T(".doc"),
		_T(".docx"),
		_T(".ppt"),
		_T(".pptx"),
		_T(".xls"),
		_T(".xlsx"),
		_T(".json"),
		_T(".xml"),
		_T(".db"),
	};

	for (auto& it : document_exts) {
		if (ext == it)
			return true;
	}

	return false;
}
//******************************************************************************
iMonitor::String cxMessageOperationModifiableMatcher::GetName(void)
{
	return _T("Operation.Modifiable");
}
//******************************************************************************
iMonitor::String cxMessageOperationModifiableMatcher::GetDescription(void)
{
	return _T("Check if the opeartion may cause some modifications");
}
//******************************************************************************
bool cxMessageOperationModifiableMatcher::IsMatch(IMessage* Message)
{
	auto type = Message->GetType();

	return type == emMSGProcessCreate ||
		type == emMSGThreadCreate ||
		type == emMSGFilePostCreateHardLink ||
		type == emMSGFilePostRename ||
		type == emMSGFilePostDelete ||
		type == emMSGFilePostWrite ||
		type == emMSGRegPostDeleteKey ||
		type == emMSGRegPostRenameKey ||
		type == emMSGRegPostDeleteValue ||
		type == emMSGRegPostSetValue;
}
//******************************************************************************
