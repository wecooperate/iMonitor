//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "MSGInfo.h"
//******************************************************************************
cxMSGInfoManager::cxMSGInfoManager()
{
	m_Infos = proto::GetMSGInfoTable();

	m_CommonInfos = {
		{ emMSGFieldType, emMSGDataULONG, L"Operation" },
		{ emMSGFieldSeqId, emMSGDataULONG, L"NO." },
		{ emMSGFieldStatus, emMSGDataULONG, L"Status" },
		{ emMSGFieldCurrentProcessId, emMSGDataULONG, L"CurrentProcessId" },
		{ emMSGFieldCurrentThreadId, emMSGDataULONG, L"CurrentThreadId" },
		{ emMSGFieldTime, emMSGDataULONGLONG, L"Time" },
		{ emMSGFieldDetail, emMSGDataString, L"Detail" },
	};
}
//******************************************************************************
cxMSGInfoManager::cxMSGInfo cxMSGInfoManager::GetMSGInfo(ULONG Type)
{
	auto it = m_Infos.find(Type);

	if (it == m_Infos.end())
		return cxMSGInfo{ 0, NULL, 0, NULL };

	return it->second;
}
//******************************************************************************
const std::list<cxMSGInfoManager::cxMSGCommonInfo>& cxMSGInfoManager::GetMSGCommonInfo(void)
{
	return m_CommonInfos;
}
//******************************************************************************
CString cxMSGInfoManager::GetName(ULONG Type)
{
	for (auto& it : g_MSGConfig->GetConfigItems()) {
		if (it.Type == Type)
			return it.Name;
	}

	return GetMSGInfo(Type).Name;
}
//******************************************************************************
CString cxMSGInfoManager::GetGroupName(ULONG Group)
{
	switch (Group) {
	case emMSGGroupProcess:
		return L"Process";

	case emMSGGroupFile:
		return L"File";

	case emMSGGroupRegistry:
		return L"Registry";

	case emMSGGroupSocket:
		return L"Network";

	default:
		return CString();
	}
}
//******************************************************************************
ULONG cxMSGInfoManager::GetFieldIndex(ULONG Type, LPCWSTR Name)
{
	for (auto& it : m_CommonInfos) {
		if (0 == wcscmp(it.Name, Name))
			return it.Index;
	}

	auto info = GetMSGInfo(Type);

	for (ULONG i = 0; i < info.FieldCount; i++) {
		if (0 == wcscmp(info.Fields[i].Name, Name))
			return i;
	}

	return -1;
}
//******************************************************************************
CString cxMSGInfoManager::GetFieldName(ULONG Type, ULONG Index)
{
	if (Index > emMSGFieldExtension) {
		for (auto& it : m_CommonInfos) {
			if (it.Index == Index)
				return it.Name;
		}
	}

	auto info = GetMSGInfo(Type);

	if (Index < info.FieldCount)
		return info.Fields[Index].Name;

	return CString();
}
//******************************************************************************
bool cxMSGInfoManager::IsFieldNumber(ULONG Type, ULONG Index)
{
	if (Index == emMSGFieldPath)
		return false;

	if (Index > emMSGFieldExtension) {
		for (auto& it : m_CommonInfos) {
			if (it.Index == Index) {
				ULONG type = MSG_GET_BASE_TYPE(it.Type);
				return type == emMSGDataULONG || type == emMSGDataULONGLONG;
			}
		}
	}

	auto info = GetMSGInfo(Type);

	if (Index < info.FieldCount) {
		ULONG type = MSG_GET_BASE_TYPE(info.Fields[Index].Type);
		return type == emMSGDataULONG || type == emMSGDataULONGLONG;
	}

	return false;
}
//******************************************************************************
CString cxMSGInfoManager::GetCommonFieldName(ULONG Index)
{
	if (Index == emMSGFieldPath)
		return L"Path";

	if (Index < emMSGFieldPrivateBegin) {
		return m_Infos.begin()->second.Fields[Index].Name;
	}

	for (auto& it : m_CommonInfos) {
		if (it.Index == Index)
			return it.Name;
	}

	return CString();
}
//******************************************************************************
