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
#include "RuleMatcher.h"
#include "../SymbolManager/SymbolManager.h"
//******************************************************************************
template<typename T>
static inline bool CharMatch(const T Matcher, const T Data, bool IgnoreCase)
{
	if (Matcher == '?') {
		return true;
	}
	return IgnoreCase ? toupper(Matcher) == toupper(Data) : Matcher == Data;
}
//******************************************************************************
template<typename T>
static bool StringMatch(const T* Matcher, int MatcherLength, const T* Data, int DataLength, bool IgnoreCase)
{
	int data_index = 0;
	int matcher_index = 0;
	int data_star = -1;
	int matcher_star = -1;

	while (data_index < DataLength) {
		if (matcher_index < MatcherLength) {
			if (Matcher[matcher_index] == '*') {
				data_star = data_index;
				matcher_star = matcher_index;
				matcher_index++;
				continue;
			}

			if (Matcher[matcher_index] == '>' && matcher_index == MatcherLength - 1 && matcher_index != matcher_star + 1) {
				return Data[data_index] == 0 || Data[data_index] == '\\' || Data[data_index] == '/';
			}

			if (CharMatch(Matcher[matcher_index], Data[data_index], IgnoreCase)) {
				data_index++;
				matcher_index++;
				continue;
			}
		}

		if (data_star >= 0) {
			data_index = ++data_star;
			matcher_index = matcher_star + 1;
			continue;
		}

		return false;
	}

	while (matcher_index < MatcherLength && (Matcher[matcher_index] == '*' || Matcher[matcher_index] == '>')) {
		++matcher_index;
	}

	return matcher_index == MatcherLength;
}
//******************************************************************************
static bool StringMatch(const char* Matcher, const char* Data, bool IgnoreCase)
{
	if (!Matcher || !Data)
		return Matcher == Data;

	return StringMatch(Matcher, strlen(Matcher), Data, strlen(Data), IgnoreCase);
}
//******************************************************************************
static bool StringMatch(const wchar_t* Matcher, const wchar_t* Data, bool IgnoreCase)
{
	if (!Matcher || !Data)
		return Matcher == Data;

	return StringMatch(Matcher, wcslen(Matcher), Data, wcslen(Data), IgnoreCase);
}
//******************************************************************************
CString cxRuleMatcher::GetOperatorString(emMatchOperator Operator)
{
	switch (Operator) {
	case emOperatorStringEqual:
		return _T("Equal");
	case emOperatorStringNotEqual:
		return _T("Not Equal");
	case emOperatorStringMatch:
		return _T("Match");
	case emOperatorStringNotMatch:
		return _T("Not Match");
	case emOperatorStringMatchWithCase:
		return _T("Match With Case");
	case emOperatorStringNotMatchWithCase:
		return _T("Not Match With Case");

	case emOperatorNumberEqual:
		return _T("==");
	case emOperatorNumberNotEqual:
		return _T("!=");
	case emOperatorNumberGreater:
		return _T(">");
	case emOperatorNumberLess:
		return _T("<");
	case emOperatorNumberGreaterEqual:
		return _T(">=");
	case emOperatorNumberLessEqual:
		return _T("<=");
	case emOperatorNumberInclude:
		return _T("&");
	case emOperatorNumberNotInclude:
		return _T("!&");

	default:
		return _T("");
	}
}
//******************************************************************************
bool cxRuleMatcher::IsNumberOperator(emMatchOperator Operator)
{
	return Operator > emOperatorNumberBegin && Operator < emOperatorNumberEnd;
}
//******************************************************************************
cxRuleMatcher::cxRuleMatcher(emMatchOperator Op, ULONG Field, ULONGLONG Data, ULONG Type)
	: m_Operator(Op)
	, m_Field(Field)
	, m_Data(Data)
	, m_Type(Type)
{
	DCHECK(IsNumberOperator(m_Operator));
}
//******************************************************************************
cxRuleMatcher::cxRuleMatcher(emMatchOperator Op, ULONG Field, const CString& Data, ULONG Type)
	: m_Operator(Op)
	, m_Field(Field)
	, m_Data(0)
	, m_DataString(Data)
	, m_Type(Type)
{
	DCHECK(!IsNumberOperator(m_Operator));
}
//******************************************************************************
bool cxRuleMatcher::IsMatch(cxMSG* msg)
{
	if (m_Type != emMSGAllType && m_Type != msg->m_Type)
		return false;

	if (m_Field == emMSGFieldCallstack)
		return IsMatchCallstack(msg);

	if (IsNumber())
		return IsMatchNumber(msg->GetNumber(m_Field));

	return IsMatchString(msg->GetString(m_Field));
}
//******************************************************************************
bool cxRuleMatcher::IsNumber(void)
{
	return IsNumberOperator(m_Operator);
}
//******************************************************************************
bool cxRuleMatcher::IsMatchNumber(ULONGLONG Data)
{
	switch (m_Operator) {
	case emOperatorNumberEqual:
		return Data == m_Data;

	case emOperatorNumberNotEqual:
		return Data != m_Data;

	case emOperatorNumberGreater:
		return Data > m_Data;

	case emOperatorNumberLess:
		return Data < m_Data;

	case emOperatorNumberGreaterEqual:
		return Data >= m_Data;

	case emOperatorNumberLessEqual:
		return Data <= m_Data;

	case emOperatorNumberInclude:
		return (Data & m_Data) == m_Data;

	case emOperatorNumberNotInclude:
		return (Data & m_Data) == 0;
	}

	return false;
}
//******************************************************************************
bool cxRuleMatcher::IsMatchString(const CString& Data)
{
	if (Data.IsEmpty() && m_DataString == _T("NULL")) {
		if (m_Operator == emOperatorStringEqual ||
			m_Operator == emOperatorStringMatch ||
			m_Operator == emOperatorStringMatchWithCase) {
			return true;
		}
		return false;
	}

	switch (m_Operator) {
	case emOperatorStringEqual:
		return m_DataString == Data;

	case emOperatorStringNotEqual:
		return m_DataString != Data;

	case emOperatorStringMatch:
		return StringMatch(m_DataString, Data, true);

	case emOperatorStringNotMatch:
		return !StringMatch(m_DataString, Data, true);

	case emOperatorStringMatchWithCase:
		return StringMatch(m_DataString, Data, false);

	case emOperatorStringNotMatchWithCase:
		return !StringMatch(m_DataString, Data, false);
	}

	return false;
}
//******************************************************************************
bool cxRuleMatcher::IsMatchCallstack(cxMSG* msg)
{
	auto callstack = msg->GetCallstack();

	for (ULONG i = 0; i < callstack.Count; i++) {
		cxSymbol symbol(callstack.Data[i], msg->m_CurrentProcessId, msg->m_Time);
		if (IsMatchString(symbol.m_ModulePath)) {
			return true;
		}
	}

	return false;
}
//******************************************************************************
