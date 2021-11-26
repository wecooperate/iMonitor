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
#include "MSG.h"
#include "MSGConfig.h"
//******************************************************************************
cxMSG::cxMSG(cxMSGHeader* Header)
{
	m_Type = Header->Type;
	m_SeqId = Header->SeqId;
	m_Status = Header->Status;
	m_CurrentProcessId = Header->CurrentProcessId;
	m_CurrentThreadId = Header->CurrentThreadId;
	m_Time = Header->Time;

	m_Fields = 0;

	auto data = (const char*)(Header + 1);
	auto data_end = (const char*)Header + Header->Length;

	for (auto i = 0; i < emMaxDataCount; i++) {
		m_Data[i] = 0;

		if ((Header->Fields & BIT(i)) == 0)
			continue;

		m_Fields |= BIT(i);

		cxMSGDataHeader* dataheader = (cxMSGDataHeader*)data;

		m_Data[i] = g_MSGData->Insert(dataheader->Type, dataheader->GetData(), dataheader->Length);

		data += dataheader->Length + sizeof(cxMSGDataHeader);

		if (data >= data_end)
			break;
	}

	//
	// fix OpenProcess path
	//
	if (m_Type == emMSGProcessOpen) {
		if (GetPath().IsEmpty()) {
			auto process = g_MSGProcessManager->GetProcess(GetNumber(proto::ProcessCreate::emFieldProcessId), m_Time);
			m_Data[emMSGFieldPath] = g_MSGData->InsertString(process->m_ProcessPath);
		}
	}
}
//******************************************************************************
CString cxMSG::GetName(void) const
{
	if (m_Type == emMSGSocketPostControl)
		return GetSocketControlName();

	return g_MSGInfo->GetName(m_Type);
}
//******************************************************************************
CString cxMSG::GetSeqId(void) const
{
	return g_MSGFormat->FormatInteger(m_SeqId);
}
//******************************************************************************
CString cxMSG::GetTime(void) const
{
	return g_MSGFormat->Format(m_Time, emMSGDataTime);
}
//******************************************************************************
CString cxMSG::GetPath(void) const
{
	switch (m_Type) {
	case emMSGSocketPostConnect:
	case emMSGSocketSend:
	case emMSGSocketSendTo: {
		CString str;
		str.Format(_T("%s : %s -> %s : %s"),
			GetString(proto::SocketSend::emFieldLocalIP),
			GetString(proto::SocketSend::emFieldLocalPort),
			GetString(proto::SocketSend::emFieldIP),
			GetString(proto::SocketSend::emFieldPort));
		return str;
	}

	case emMSGSocketPostRecv:
	case emMSGSocketPostRecvFrom:
	case emMSGSocketPostAccept: {
		CString str;
		str.Format(_T("%s : %s <- %s : %s"),
			GetString(proto::SocketPostRecv::emFieldLocalIP),
			GetString(proto::SocketPostRecv::emFieldLocalPort),
			GetString(proto::SocketPostRecv::emFieldIP),
			GetString(proto::SocketPostRecv::emFieldPort));
		return str;
	}

	case emMSGSocketPostListen: {
		CString str;
		str.Format(_T("%s : %s"),
			GetString(proto::SocketPostListen::emFieldIP),
			GetString(proto::SocketPostListen::emFieldPort));
		return str;
	}

	case emMSGSocketCreate:
	case emMSGSocketPostControl: {
		CString str = _T("SocketObject: ");
		str += FormatField(emMSGFieldPrivateBegin, emMSGDataULONGLONG);
		return str;
	}

	default:
		break;
	}

	return FormatField(emMSGFieldPath, GetMSGInfo().Fields[emMSGFieldPath].Type);
}
//******************************************************************************
CString cxMSG::GetStatus(void) const
{
	return g_MSGStatus->GetString(m_Status);
}
//******************************************************************************
CString cxMSG::GetProcessId(void) const
{
	return g_MSGFormat->Format(m_CurrentProcessId, emMSGDataULONG);
}
//******************************************************************************
CString cxMSG::GetThreadId(void) const
{
	if (m_CurrentThreadId == 0)
		return CString();

	return g_MSGFormat->Format(m_CurrentThreadId, emMSGDataULONG);
}
//******************************************************************************
cxMSGDataCallstack cxMSG::GetCallstack(void) const
{
	return g_MSGData->GetCallstack(m_Data[emMSGFieldCallstack]);
}
//******************************************************************************
cxMSGProcess* cxMSG::GetProcess(void) const
{
	return g_MSGProcessManager->GetProcess(m_CurrentProcessId, m_Time);
}
//******************************************************************************
CString cxMSG::GetProcessName(void) const
{
	return g_MSGData->GetString(m_Data[emMSGFieldCurrentProcessName]);
}
//******************************************************************************
CString cxMSG::GetLocatePath(void) const
{
	if (MSG_GET_GROUP(m_Type) == emMSGGroupSocket)
		return GetProcess()->m_ProcessPath;

	return GetPath();
}
//******************************************************************************
CString cxMSG::GetFieldName(ULONG Index) const
{
	return g_MSGInfo->GetFieldName(m_Type, Index);
}
//******************************************************************************
ULONG cxMSG::GetFieldIndex(LPCWSTR Name) const
{
	return g_MSGInfo->GetFieldIndex(m_Type, Name);
}
//******************************************************************************
bool cxMSG::IsNumber(ULONG Index) const
{
	return g_MSGInfo->IsFieldNumber(m_Type, m_Index);
}
//******************************************************************************
CString cxMSG::GetDetail(LPCTSTR Split) const
{
	ULONG index = emMSGFieldPrivateBegin + 1;

	if (index >= emMSGGroupSocket && index <= emMSGGroupSocket + 100) {
		index = emMSGFieldPrivateBegin;
	}

	CString str;

	if (m_Status != STATUS_SUCCESS) {
		str = g_MSGStatus->GetErrorString(m_Status);
	}

	cxMSGInfo info = GetMSGInfo();

	for (ULONG i = index; i < info.FieldCount; i++) {
		if ((m_Fields & BIT(i)) == 0)
			continue;

		CString item;
		item.Format(_T("%s : %s"), info.Fields[i].Name, FormatField(i, info.Fields[i].Type));

		if (!str.IsEmpty()) {
			str += Split;
		}

		str += item;
	}

	return str;
}
//******************************************************************************
ULONG cxMSG::GetGroup(void) const
{
	return MSG_GET_GROUP(m_Type);
}
//******************************************************************************
cxMSG::cxMSGInfo cxMSG::GetMSGInfo(void) const
{
	return g_MSGInfo->GetMSGInfo(m_Type);
}
//******************************************************************************
ULONGLONG cxMSG::GetNumber(ULONG Index) const
{
	if (Index > emMSGFieldCustomExtension)
		return GetCustomNumber(Index);

	switch (Index) {
	case emMSGFieldType:
		return m_Type;

	case emMSGFieldSeqId:
		return m_SeqId;

	case emMSGFieldStatus:
		return m_Status;

	case emMSGFieldCurrentProcessId:
		return m_CurrentProcessId;

	case emMSGFieldCurrentThreadId:
		return m_CurrentThreadId;

	case emMSGFieldTime:
		return m_Time;

	case emMSGFieldCurrentProcessCreateTime:
		return GetProcess()->m_CreateTime;
	}

	if (Index < emMaxDataCount)
		return m_Data[Index];

	return 0;
}
//******************************************************************************
CString cxMSG::GetString(ULONG Index) const
{
	if (Index > emMSGFieldCustomExtension)
		return GetCustomString(Index);

	switch (Index) {
	case emMSGFieldType:
		return GetName();

	case emMSGFieldSeqId:
		return GetSeqId();

	case emMSGFieldStatus:
		return GetStatus();

	case emMSGFieldCurrentProcessId:
		return GetProcessId();

	case emMSGFieldCurrentThreadId:
		return GetThreadId();

	case emMSGFieldTime:
		return GetTime();

	case emMSGFieldDetail:
		return GetDetail();

	case emMSGFieldPath:
		return GetPath();

	case emMSGFieldCurrentProcessPath:
		return GetProcess()->m_ProcessPath;

	case emMSGFieldCurrentProcessCommandline:
		return GetProcess()->m_Commandline;
	}

	cxMSGInfo info = GetMSGInfo();

	if (Index >= info.FieldCount)
		return CString();

	return FormatField(Index, info.Fields[Index].Type);
}
//******************************************************************************
ULONGLONG cxMSG::GetCustomNumber(ULONG Index) const
{
	DCHECK(!"not support");

	return 0;
}
//******************************************************************************
CString cxMSG::GetCustomString(ULONG Index) const
{
	DCHECK(!"not support");

	return CString();
}
//******************************************************************************
CString cxMSG::FormatField(ULONG Index, ULONG Type) const
{
	if (Index >= emMaxDataCount)
		return CString();

	return g_MSGFormat->Format(m_Data[Index], Type);
}
//******************************************************************************
CString cxMSG::GetSocketControlName(void) const
{
	static std::map<ULONG, LPCTSTR> codes = {
		{ 0, _T("Bind") },
		{ 1, _T("Connect") },
		{ 2, _T("Listen") },
		{ 4, _T("Accept") },
		{ 5, _T("Recv") },
		{ 6, _T("RecvFrom") },
		{ 7, _T("Send") },
		{ 8, _T("SendTo") },
		{ 9, _T("Select") },
		{ 11, _T("Getsockname") },
		{ 15, _T("Getpeername") },
		{ 46, _T("Connectex") },
	};

	if (auto it = codes.find(m_Data[proto::SocketPostControl::emFieldCode]); it != codes.end()) {
		return CString(_T("SocketControl.")) + it->second;
	}

	return _T("SocketControl");
}
//******************************************************************************
