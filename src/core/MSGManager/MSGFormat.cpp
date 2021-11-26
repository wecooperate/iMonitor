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
#include "MSGFormat.h"
#include "MSGData.h"
//******************************************************************************
#define APPEND_FLAG_(x)       \
	if (Data & x) {           \
		if (!str.IsEmpty())   \
			str += _T(" | "); \
		str += L#x;           \
	};
#define TEST_VALUE_(x) \
	if (Data == x) {   \
		str = L#x;     \
		break;         \
	}
//******************************************************************************
inline static CString MakeString(ULONG Data, const CString& Value)
{
	CString str;

	if (Value.IsEmpty())
		Data == 0 ? str = _T("0") : str.Format(_T("%08X"), Data);
	else
		str.Format(_T("%08X(%s)"), Data, Value);

	return str;
}
//******************************************************************************
inline static CString MSGFormatProcessAccess(ULONG Data)
{
	CString str;

	if ((Data & 0xFFFF) == 0xFFFF)
		str += _T("PROCESS_ALL_ACCESS");
	else {
		APPEND_FLAG_(PROCESS_TERMINATE)
		APPEND_FLAG_(PROCESS_CREATE_THREAD)
		APPEND_FLAG_(PROCESS_SET_SESSIONID)
		APPEND_FLAG_(PROCESS_VM_OPERATION)
		APPEND_FLAG_(PROCESS_VM_READ)
		APPEND_FLAG_(PROCESS_VM_WRITE)
		APPEND_FLAG_(PROCESS_DUP_HANDLE)
		APPEND_FLAG_(PROCESS_CREATE_PROCESS)
		APPEND_FLAG_(PROCESS_SET_QUOTA)
		APPEND_FLAG_(PROCESS_SET_INFORMATION)
		APPEND_FLAG_(PROCESS_QUERY_INFORMATION)
		APPEND_FLAG_(PROCESS_SUSPEND_RESUME)
		APPEND_FLAG_(PROCESS_QUERY_LIMITED_INFORMATION)
	}

	return MakeString(Data, str);
}
//******************************************************************************
inline static CString MSGFormatThreadAccess(ULONG Data)
{
	CString str;

	if ((Data & 0xFFFF) == 0xFFFF)
		str += _T("THREAD_ALL_ACCESS");
	else {
		APPEND_FLAG_(THREAD_TERMINATE)
		APPEND_FLAG_(THREAD_SET_INFORMATION)
		APPEND_FLAG_(THREAD_QUERY_INFORMATION)
		APPEND_FLAG_(THREAD_SUSPEND_RESUME)
		APPEND_FLAG_(THREAD_QUERY_LIMITED_INFORMATION)
		APPEND_FLAG_(THREAD_GET_CONTEXT)
		APPEND_FLAG_(THREAD_SET_CONTEXT)
		APPEND_FLAG_(THREAD_IMPERSONATE)
	}

	return MakeString(Data, str);
}
//******************************************************************************
inline static CString MSGFormatFileAccess(ULONG Data)
{
	CString str;

	if (Data == FILE_GENERIC_READ)
		str += _T("FILE_GENERIC_READ");
	else if (Data == FILE_GENERIC_WRITE)
		str += _T("FILE_GENERIC_WRITE");
	else if (Data == FILE_GENERIC_EXECUTE)
		str += _T("FILE_GENERIC_EXECUTE");
	else if ((Data & 0x1FF) == 0x1FF)
		str += _T("FILE_ALL_ACCESS");
	else {
		APPEND_FLAG_(FILE_READ_DATA)
		APPEND_FLAG_(FILE_LIST_DIRECTORY)
		APPEND_FLAG_(FILE_WRITE_DATA)
		APPEND_FLAG_(FILE_ADD_FILE)
		APPEND_FLAG_(FILE_APPEND_DATA)
		APPEND_FLAG_(FILE_ADD_SUBDIRECTORY)
		APPEND_FLAG_(FILE_CREATE_PIPE_INSTANCE)
		APPEND_FLAG_(FILE_READ_EA)
		APPEND_FLAG_(FILE_WRITE_EA)
		APPEND_FLAG_(FILE_EXECUTE)
		APPEND_FLAG_(FILE_TRAVERSE)
		APPEND_FLAG_(FILE_DELETE_CHILD)
		APPEND_FLAG_(FILE_READ_ATTRIBUTES)
		APPEND_FLAG_(FILE_WRITE_ATTRIBUTES)
	}

	return MakeString(Data, str);
}
//******************************************************************************
inline static CString MSGFormatFileAttributes(ULONG Data)
{
	CString str;

	APPEND_FLAG_(FILE_ATTRIBUTE_READONLY)
	APPEND_FLAG_(FILE_ATTRIBUTE_HIDDEN)
	APPEND_FLAG_(FILE_ATTRIBUTE_SYSTEM)
	APPEND_FLAG_(FILE_ATTRIBUTE_DIRECTORY)
	APPEND_FLAG_(FILE_ATTRIBUTE_ARCHIVE)
	APPEND_FLAG_(FILE_ATTRIBUTE_DEVICE)
	APPEND_FLAG_(FILE_ATTRIBUTE_NORMAL)
	APPEND_FLAG_(FILE_ATTRIBUTE_TEMPORARY)
	APPEND_FLAG_(FILE_ATTRIBUTE_SPARSE_FILE)
	APPEND_FLAG_(FILE_ATTRIBUTE_REPARSE_POINT)
	APPEND_FLAG_(FILE_ATTRIBUTE_COMPRESSED)
	APPEND_FLAG_(FILE_ATTRIBUTE_OFFLINE)
	APPEND_FLAG_(FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)

	return MakeString(Data, str);
}
//******************************************************************************
inline static CString MSGFormatFileShareAccess(ULONG Data)
{
	CString str;

	APPEND_FLAG_(FILE_SHARE_READ)
	APPEND_FLAG_(FILE_SHARE_WRITE)
	APPEND_FLAG_(FILE_SHARE_DELETE)

	return MakeString(Data, str);
}
//******************************************************************************
inline static CString MSGFormatFileDisposition(ULONG Data)
{
#define FILE_SUPERSEDE	  0x00000000
#define FILE_OPEN		  0x00000001
#define FILE_CREATE		  0x00000002
#define FILE_OPEN_IF	  0x00000003
#define FILE_OVERWRITE	  0x00000004
#define FILE_OVERWRITE_IF 0x00000005

	CString str;

	do {
		TEST_VALUE_(FILE_SUPERSEDE)
		TEST_VALUE_(FILE_OPEN)
		TEST_VALUE_(FILE_CREATE)
		TEST_VALUE_(FILE_OPEN_IF)
		TEST_VALUE_(FILE_OVERWRITE)
		TEST_VALUE_(FILE_OVERWRITE_IF)
	} while (false);

	return MakeString(Data, str);
}
//******************************************************************************
inline static CString MSGFormatFileCreateOption(ULONG Data)
{
#define FILE_DIRECTORY_FILE			   0x00000001
#define FILE_WRITE_THROUGH			   0x00000002
#define FILE_SEQUENTIAL_ONLY		   0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING 0x00000008
#define FILE_SYNCHRONOUS_IO_ALERT	   0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT   0x00000020
#define FILE_NON_DIRECTORY_FILE		   0x00000040
#define FILE_CREATE_TREE_CONNECTION	   0x00000080
#define FILE_COMPLETE_IF_OPLOCKED	   0x00000100
#define FILE_NO_EA_KNOWLEDGE		   0x00000200
#define FILE_OPEN_REMOTE_INSTANCE	   0x00000400
#define FILE_RANDOM_ACCESS			   0x00000800
#define FILE_DELETE_ON_CLOSE		   0x00001000
#define FILE_OPEN_BY_FILE_ID		   0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT	   0x00004000
#define FILE_NO_COMPRESSION			   0x00008000
#define FILE_OPEN_REQUIRING_OPLOCK	   0x00010000
#define FILE_RESERVE_OPFILTER		   0x00100000
#define FILE_OPEN_REPARSE_POINT		   0x00200000
#define FILE_OPEN_NO_RECALL			   0x00400000
#define FILE_OPEN_FOR_FREE_SPACE_QUERY 0x00800000

	CString str;

	APPEND_FLAG_(FILE_DIRECTORY_FILE)
	APPEND_FLAG_(FILE_WRITE_THROUGH)
	APPEND_FLAG_(FILE_SEQUENTIAL_ONLY)
	APPEND_FLAG_(FILE_NO_INTERMEDIATE_BUFFERING)
	APPEND_FLAG_(FILE_SYNCHRONOUS_IO_ALERT)
	APPEND_FLAG_(FILE_SYNCHRONOUS_IO_NONALERT)
	APPEND_FLAG_(FILE_NON_DIRECTORY_FILE)
	APPEND_FLAG_(FILE_CREATE_TREE_CONNECTION)
	APPEND_FLAG_(FILE_COMPLETE_IF_OPLOCKED)
	APPEND_FLAG_(FILE_NO_EA_KNOWLEDGE)
	APPEND_FLAG_(FILE_OPEN_REMOTE_INSTANCE)
	APPEND_FLAG_(FILE_RANDOM_ACCESS)
	APPEND_FLAG_(FILE_DELETE_ON_CLOSE)
	APPEND_FLAG_(FILE_OPEN_BY_FILE_ID)
	APPEND_FLAG_(FILE_OPEN_FOR_BACKUP_INTENT)
	APPEND_FLAG_(FILE_NO_COMPRESSION)
	APPEND_FLAG_(FILE_OPEN_REQUIRING_OPLOCK)
	APPEND_FLAG_(FILE_RESERVE_OPFILTER)
	APPEND_FLAG_(FILE_OPEN_REPARSE_POINT)
	APPEND_FLAG_(FILE_OPEN_NO_RECALL)
	APPEND_FLAG_(FILE_OPEN_FOR_FREE_SPACE_QUERY)

	return MakeString(Data, str);
}
//******************************************************************************
inline static CString MSGFormatPageProtection(ULONG Data)
{
	CString str;

	do {
		TEST_VALUE_(PAGE_READONLY)
		TEST_VALUE_(PAGE_READWRITE)
		TEST_VALUE_(PAGE_WRITECOPY)
		TEST_VALUE_(PAGE_EXECUTE)
		TEST_VALUE_(PAGE_EXECUTE_READ)
		TEST_VALUE_(PAGE_EXECUTE_READWRITE)
		TEST_VALUE_(PAGE_EXECUTE_WRITECOPY)
	} while (false);

	return MakeString(Data, str);
}
//******************************************************************************
inline static CString MSGFormatRegType(ULONG Data)
{
	CString str;

	do {
		TEST_VALUE_(REG_NONE)
		TEST_VALUE_(REG_SZ)
		TEST_VALUE_(REG_EXPAND_SZ)
		TEST_VALUE_(REG_BINARY)
		TEST_VALUE_(REG_DWORD)
		TEST_VALUE_(REG_DWORD_LITTLE_ENDIAN)
		TEST_VALUE_(REG_DWORD_BIG_ENDIAN)
		TEST_VALUE_(REG_LINK)
		TEST_VALUE_(REG_DWORD_BIG_ENDIAN)
		TEST_VALUE_(REG_MULTI_SZ)
		TEST_VALUE_(REG_RESOURCE_LIST)
		TEST_VALUE_(REG_FULL_RESOURCE_DESCRIPTOR)
		TEST_VALUE_(REG_RESOURCE_REQUIREMENTS_LIST)
		TEST_VALUE_(REG_QWORD)
		TEST_VALUE_(REG_QWORD_LITTLE_ENDIAN)

	} while (false);

	return MakeString(Data, str);
}
//******************************************************************************
inline static CString MSGFormatRegOptions(ULONG Data)
{
	CString str;

	APPEND_FLAG_(REG_OPTION_VOLATILE)
	APPEND_FLAG_(REG_OPTION_CREATE_LINK)
	APPEND_FLAG_(REG_OPTION_BACKUP_RESTORE)
	APPEND_FLAG_(REG_OPTION_OPEN_LINK)

	return MakeString(Data, str);
}
//******************************************************************************
inline static CString MSGFormatRegAccess(ULONG Data)
{
	CString str;

	if (Data == KEY_ALL_ACCESS)
		str += _T("KEY_ALL_ACCESS");
	else if (Data == KEY_WRITE)
		str += _T("KEY_WRITE");
	else if (Data == KEY_READ)
		str += _T("KEY_READ");
	else {
		APPEND_FLAG_(KEY_QUERY_VALUE)
		APPEND_FLAG_(KEY_SET_VALUE)
		APPEND_FLAG_(KEY_CREATE_SUB_KEY)
		APPEND_FLAG_(KEY_ENUMERATE_SUB_KEYS)
		APPEND_FLAG_(KEY_NOTIFY)
		APPEND_FLAG_(KEY_CREATE_LINK)
		APPEND_FLAG_(KEY_WOW64_32KEY)
		APPEND_FLAG_(KEY_WOW64_64KEY)
		APPEND_FLAG_(KEY_WOW64_RES)
	}

	return MakeString(Data, str);
}
//******************************************************************************
CString cxMSGFormat::Format(ULONGLONG Data, ULONG Type)
{
	ULONG type_base = MSG_GET_BASE_TYPE(Type);

	CString str;

	switch (type_base) {
	case emMSGDataULONG:
		return FormatULONG(Data, Type);

	case emMSGDataULONGLONG:
		return FormatULONGLONG(Data, Type);
		break;

	case emMSGDataString:
	case emMSGDataPath:
		str = g_MSGData->GetString(Data);
		break;

	case emMSGDataCallstatck:
		str.Format(_T("%016I64X"), Data);
		break;

	case emMSGDataBinary:
		cxMSGDataBinary data = g_MSGData->GetBinary(Data);
		str.Format(_T("len = %d"), data.Length);
		break;
	}

	return str;
}
//******************************************************************************
CString cxMSGFormat::FormatULONG(ULONG Data, ULONG Type)
{
	CString str;

	switch (Type) {
	case emMSGDataBool:
		str = Data == 0 ? "false" : "true";
		break;

	case emMSGDataHex:
		str.Format(_T("%08X"), Data);
		break;

	case emMSGDataSocketIP:
		str.Format(_T("%d.%d.%d.%d"),
			((PUCHAR)&Data)[0],
			((PUCHAR)&Data)[1],
			((PUCHAR)&Data)[2],
			((PUCHAR)&Data)[3]);
		break;

	case emMSGDataSocketPort:
		str.Format(_T("%d"), htons((USHORT)Data));
		break;

	case emMSGDataProcessAccess:
		return MSGFormatProcessAccess(Data);

	case emMSGDataThreadAccess:
		return MSGFormatThreadAccess(Data);

	case emMSGDataFileAccess:
		return MSGFormatFileAccess(Data);

	case emMSGDataFileAttributes:
		return MSGFormatFileAttributes(Data);

	case emMSGDataFileShareAccess:
		return MSGFormatFileShareAccess(Data);

	case emMSGDataFileDisposition:
		return MSGFormatFileDisposition(Data);

	case emMSGDataFileOptions:
		return MSGFormatFileCreateOption(Data);

	case emMSGDataFilePageProtection:
		return MSGFormatPageProtection(Data);

	case emMSGDataRegAccess:
		return MSGFormatRegAccess(Data);

	case emMSGDataRegOptions:
		return MSGFormatRegOptions(Data);

	case emMSGDataRegType:
		return MSGFormatRegType(Data);

	default:
		str.Format(_T("%d"), Data);
		break;
	}

	return str;
}
//******************************************************************************
CString cxMSGFormat::FormatULONGLONG(ULONGLONG Data, ULONG Type)
{
	CString str;

	switch (Type) {
	case emMSGDataTime:
		return FormatDateTime(Data);

	default:
		str.Format(_T("%016I64X"), Data);
		break;
	}

	return str;
}
//******************************************************************************
CString cxMSGFormat::FormatInteger(ULONG Data)
{
	CString str;
	str.Format(_T("%d"), Data);

	CString strfix = str;

	for (int index = 3; index < str.GetLength(); index += 3) {
		strfix.Insert(str.GetLength() - index, _T(","));
	}

	return strfix;
}
//******************************************************************************
CString cxMSGFormat::FormatAddress(ULONG Data)
{
	CString str;
	str.Format(_T("0x%X"), Data);
	return str;
}
//******************************************************************************
CString cxMSGFormat::FormatAddress(ULONGLONG Data)
{
	CString str;
	str.Format(_T("0x%I64X"), Data);
	return str;
}
//******************************************************************************
CString cxMSGFormat::FormatDateTime(ULONGLONG Data)
{
	if (Data == 0)
		return CString();

	ULONGLONG time = Data;
	SYSTEMTIME system_time;
	FileTimeToLocalFileTime((PFILETIME)&time, (PFILETIME)&time);
	FileTimeToSystemTime((PFILETIME)&time, &system_time);

	CString str;
	str.Format(_T("%d-%02d-%02d %02d:%02d:%02d %03d"),
		system_time.wYear,
		system_time.wMonth,
		system_time.wDay,
		system_time.wHour,
		system_time.wMinute,
		system_time.wSecond,
		system_time.wMilliseconds);
	return str;
}
//******************************************************************************
