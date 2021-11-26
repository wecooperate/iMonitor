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
#include "MSGData.h"
//******************************************************************************
cxMSGData::~cxMSGData(void)
{
	RemoveAllData();
}
//******************************************************************************
ULONGLONG cxMSGData::Insert(ULONG Type, PVOID Data, ULONG Length)
{
	Type = MSG_GET_BASE_TYPE(Type);

	switch (Type) {
	case emMSGDataULONG:
		return *(PULONG)Data;

	case emMSGDataULONGLONG:
		return *(PULONGLONG)Data;

	case emMSGDataString:
		return InsertString(Data, Length);

	case emMSGDataPath:
		return InsertPath(Data, Length);

	case emMSGDataBinary:
		return InsertBinary(Data, Length);

	case emMSGDataCallstatck:
		return InsertCallstack(Data, Length);

	default:
		return 0;
	}
}
//******************************************************************************
ULONGLONG cxMSGData::InsertString(PVOID Data, ULONG Length)
{
	CString str = CString((LPCWSTR)Data, Length / sizeof(WCHAR));

	return InsertString(str);
}
//******************************************************************************
ULONGLONG cxMSGData::InsertString(const CString& Data)
{
	ULONGLONG hash = CRC64(Data, Data.GetLength());

	AUTO_LOCK(m_Lock);

	if (auto it = m_Strings.find(hash); it != m_Strings.end()) {
		if (it->second.Data != Data) {
			OnConflictString(hash, Data);
		}
		return hash;
	}

	CString strLower = Data;
	strLower.MakeLower();

	cxMSGDataString data;
	data.Hash = hash;
	data.LowercaseHash = CRC64(strLower);
	data.Data = Data;

	m_Strings[hash] = data;

	return hash;
}
//******************************************************************************
ULONGLONG cxMSGData::InsertPath(PVOID Data, ULONG Length)
{
	CString str = CString((LPCWSTR)Data, Length / sizeof(WCHAR));

	return InsertString(g_PathTransfer->Transfer(str));
}
//******************************************************************************
ULONGLONG cxMSGData::InsertBinary(PVOID Data, ULONG Length)
{
	ULONGLONG hash = CRC64((PBYTE)Data, Length, Length);

	AUTO_LOCK(m_Lock);

	if (auto it = m_Binarys.find(hash); it != m_Binarys.end()) {
		if (Length != it->second.Length || !RtlEqualMemory(it->second.Data, Data, Length)) {
			OnConflictBinary(hash, Data, Length);
		}
		return hash;
	}

	cxMSGDataBinary data;
	data.Hash = hash;
	data.Length = Length;
	data.Data = new char[Length];
	memcpy(data.Data, Data, Length);

	m_Binarys[hash] = data;

	return hash;
}
//******************************************************************************
ULONGLONG cxMSGData::InsertCallstack(PVOID Data, ULONG Length)
{
	ULONGLONG hash = CRC64((PBYTE)Data, Length, Length);

	AUTO_LOCK(m_Lock);

	if (m_Callstacks.find(hash) != m_Callstacks.end())
		return hash;

	cxMSGDataCallstack data;
	data.Hash = hash;
	data.Count = Length / sizeof(ULONGLONG);
	data.Data = (PULONGLONG) new char[Length];
	memcpy(data.Data, Data, Length);

	m_Callstacks[hash] = data;

	return hash;
}
//******************************************************************************
cxMSGDataString cxMSGData::GetString(ULONGLONG Data)
{
	AUTO_LOCK(m_Lock);

	auto it = m_Strings.find(Data);

	if (it != m_Strings.end())
		return it->second;

	return cxMSGDataString();
}
//******************************************************************************
cxMSGDataBinary cxMSGData::GetBinary(ULONGLONG Data)
{
	AUTO_LOCK(m_Lock);

	auto it = m_Binarys.find(Data);

	if (it != m_Binarys.end())
		return it->second;

	return cxMSGDataBinary();
}
//******************************************************************************
cxMSGDataCallstack cxMSGData::GetCallstack(ULONGLONG Data)
{
	AUTO_LOCK(m_Lock);

	auto it = m_Callstacks.find(Data);

	if (it != m_Callstacks.end())
		return it->second;

	return cxMSGDataCallstack();
}
//******************************************************************************
size_t cxMSGData::GetStringCount(void)
{
	AUTO_LOCK(m_Lock);

	return m_Strings.size();
}
//******************************************************************************
size_t cxMSGData::GetBinaryCount(void)
{
	AUTO_LOCK(m_Lock);

	return m_Binarys.size();
}
//******************************************************************************
size_t cxMSGData::GetCallstackCount(void)
{
	AUTO_LOCK(m_Lock);

	return m_Callstacks.size();
}
//******************************************************************************
void cxMSGData::RemoveAllData(void)
{
	AUTO_LOCK(m_Lock);

	for (auto& it : m_Binarys) {
		if (it.second.Data != NULL)
			delete (char*)it.second.Data;
	}

	for (auto& it : m_Callstacks) {
		if (it.second.Data != NULL)
			delete (char*)it.second.Data;
	}

	m_Strings.clear();
	m_Binarys.clear();
	m_Callstacks.clear();
}
//******************************************************************************
void cxMSGData::OnConflictString(ULONGLONG Hash, const CString& Str)
{
	DCHECK(!"TODO(fix)");
}
//******************************************************************************
void cxMSGData::OnConflictBinary(ULONGLONG Hash, PVOID Data, ULONG Length)
{
	DCHECK(!"TODO(fix)");
}
//******************************************************************************
