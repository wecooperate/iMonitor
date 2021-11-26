//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __MSGData_H__
#define __MSGData_H__
//******************************************************************************
// clang-format off
//******************************************************************************
class cxMSGDataString
{
public:
	ULONGLONG		Hash					= 0;
	ULONGLONG		LowercaseHash			= 0;
	CString			Data;

	operator		CString(void)			{ return Data; }
};
//******************************************************************************
class cxMSGDataBinary
{
public:
	ULONGLONG		Hash					= 0;
	ULONG			Length					= 0;
	PVOID			Data					= 0;
};
//******************************************************************************
class cxMSGDataCallstack
{
public:
	ULONGLONG		Hash					= 0;
	ULONG			Count					= 0;
	PULONGLONG		Data					= 0;
};
//******************************************************************************
class cxMSGData
{
#define	g_MSGData SINGLETON_(cxMSGData)

public:
	~cxMSGData								(void);

public:
	ULONGLONG		Insert					(ULONG Type, PVOID Data, ULONG Length);

public:
	ULONGLONG		InsertString			(const CString& Data);
	ULONGLONG		InsertString			(PVOID Data, ULONG Length);
	ULONGLONG		InsertPath				(PVOID Data, ULONG Length);
	ULONGLONG		InsertBinary			(PVOID Data, ULONG Length);
	ULONGLONG		InsertCallstack			(PVOID Data, ULONG Length);

public:
	cxMSGDataString	GetString				(ULONGLONG Data);
	cxMSGDataBinary	GetBinary				(ULONGLONG Data);
	cxMSGDataCallstack GetCallstack			(ULONGLONG Data);

public:
	size_t			GetStringCount			(void);
	size_t			GetBinaryCount			(void);
	size_t			GetCallstackCount		(void);

public:
	void			RemoveAllData			(void);

protected:
	void			OnConflictString		(ULONGLONG Hash, const CString& Str);
	void			OnConflictBinary		(ULONGLONG Hash, PVOID Data, ULONG Length);
	
private:
	cxLock									m_Lock;
	std::map<ULONGLONG, cxMSGDataString>	m_Strings;
	std::map<ULONGLONG, cxMSGDataBinary>	m_Binarys;
	std::map<ULONGLONG, cxMSGDataCallstack>	m_Callstacks;
};
//******************************************************************************
#endif
