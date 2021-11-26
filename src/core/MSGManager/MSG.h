//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __MSG_USER_H__
#define __MSG_USER_H__
//******************************************************************************
// clang-format off
//******************************************************************************
#include "MSGData.h"
#include "MSGFormat.h"
#include "MSGInfo.h"
#include "MSGStatus.h"
//******************************************************************************
class cxMSGProcess;
//******************************************************************************
class cxMSG
{
	using cxMSGInfo = proto::MSGInfo;

public:
	enum { emMaxDataCount = 15 };

public:
	explicit			cxMSG				(cxMSGHeader* Header);

public:
	ULONGLONG			GetNumber			(ULONG Index) const;
	CString				GetString			(ULONG Index) const;
	ULONGLONG			GetCustomNumber		(ULONG Index) const;
	CString				GetCustomString		(ULONG Index) const;

public:
	CString				GetFieldName		(ULONG Index) const;
	ULONG				GetFieldIndex		(LPCWSTR Name) const;
	bool				IsNumber			(ULONG Index) const;

public:
	cxMSGInfo			GetMSGInfo			(void) const;
	cxMSGDataCallstack	GetCallstack		(void) const;
	cxMSGProcess*		GetProcess			(void) const;
	CString				GetProcessName		(void) const;
	CString				GetLocatePath		(void) const;

public:
	CString				GetName				(void) const;
	CString				GetSeqId			(void) const;
	CString				GetStatus			(void) const;
	CString				GetProcessId		(void) const;
	CString				GetThreadId			(void) const;
	CString				GetTime				(void) const;
	CString				GetPath				(void) const;
	CString				GetDetail			(LPCTSTR Split = _T(" ")) const;
	ULONG				GetGroup			(void) const;

protected:
	CString				FormatField			(ULONG Index, ULONG Type) const;
	CString				GetSocketControlName(void) const;

public:
	ULONG				m_Index;

public:
	ULONG				m_Type;
	ULONG				m_SeqId;
	ULONG				m_Status;
	ULONG				m_Fields;
	ULONG				m_CurrentProcessId;
	ULONG				m_CurrentThreadId;
	ULONGLONG			m_Time;
	ULONGLONG			m_Data[emMaxDataCount];
};
//******************************************************************************
#endif
