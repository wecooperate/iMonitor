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
#include "MessageColumnBase.h"
//******************************************************************************
cxMessageColumnBase::cxMessageColumnBase(const CString& Name, const CString& Desc, ULONG Width, ULONG Align)
	: m_Name(Name)
	, m_Description(Desc)
	, m_Width(Width)
	, m_Align(Align)
{
	if (m_Description.IsEmpty()) {
		m_Description = m_Name;
	}
}
//******************************************************************************
String cxMessageColumnBase::GetName(void)
{
	return m_Name;
}
//******************************************************************************
String cxMessageColumnBase::GetDescription(void)
{
	return m_Description;
}
//******************************************************************************
ULONG cxMessageColumnBase::GetWidth(void)
{
	return m_Width;
}
//******************************************************************************
ULONG cxMessageColumnBase::GetAlign(void)
{
	return m_Align;
}
//******************************************************************************
DataType cxMessageColumnBase::GetDataType(IMessage* Message)
{
	return emMSGDataString;
}
//******************************************************************************
ULONG cxMessageColumnBase::GetULONG(IMessage* Message)
{
	return 0;
}
//******************************************************************************
ULONGLONG cxMessageColumnBase::GetULONGLONG(IMessage* Message)
{
	return 0;
}
//******************************************************************************
String cxMessageColumnBase::GetString(IMessage* Message)
{
	return String();
}
//******************************************************************************
Binary cxMessageColumnBase::GetBinary(IMessage* Message)
{
	return Binary();
}
//******************************************************************************
