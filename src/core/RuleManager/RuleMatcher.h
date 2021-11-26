//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __RuleMatcher_H__
#define __RuleMatcher_H__
//******************************************************************************
class cxMSG;
//******************************************************************************
#define emMSGAllType 0
//******************************************************************************
enum emMatchOperator : ULONG {
	emOperatorNumberBegin,
	emOperatorNumberEqual,
	emOperatorNumberNotEqual,
	emOperatorNumberGreater,
	emOperatorNumberLess,
	emOperatorNumberGreaterEqual,
	emOperatorNumberLessEqual,
	emOperatorNumberInclude,
	emOperatorNumberNotInclude,
	emOperatorNumberEnd,

	emOperatorStringBegin,
	emOperatorStringEqual,
	emOperatorStringNotEqual,
	emOperatorStringMatch,
	emOperatorStringNotMatch,
	emOperatorStringMatchWithCase,
	emOperatorStringNotMatchWithCase,
	emOperatorStringEnd,
};
//******************************************************************************
class cxRuleMatcher
{
public:
	static CString GetOperatorString(emMatchOperator Operator);
	static bool IsNumberOperator(emMatchOperator Operator);

public:
	cxRuleMatcher(emMatchOperator Op, ULONG Field, ULONGLONG Data, ULONG Type = emMSGAllType);
	cxRuleMatcher(emMatchOperator Op, ULONG Field, const CString& Data, ULONG Type = emMSGAllType);

public:
	bool IsMatch(cxMSG* msg);

public:
	bool IsNumber(void);

protected:
	bool IsMatchNumber(ULONGLONG Data);
	bool IsMatchString(const CString& Data);
	bool IsMatchCallstack(cxMSG* msg);

protected:
	emMatchOperator m_Operator;
	ULONG m_Type;
	ULONG m_Field;
	ULONGLONG m_Data;
	CString m_DataString;
};
//******************************************************************************
#endif
