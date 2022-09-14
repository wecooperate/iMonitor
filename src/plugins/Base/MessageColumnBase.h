//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __MessageColumnBase_h_515da692_3f3d_44ed_a87e_18ea984184b7__
#define __MessageColumnBase_h_515da692_3f3d_44ed_a87e_18ea984184b7__
//******************************************************************************
class cxMessageColumnBase : public IMessageColumn
{
public:
	cxMessageColumnBase(const CString& Name, const CString& Desc, ULONG Width, ULONG Align = 0);
	virtual ~cxMessageColumnBase(void) = default;

public:
	String GetName(void) override;
	String GetDescription(void) override;
	ULONG GetWidth(void) override;
	ULONG GetAlign(void) override;

public:
	DataType GetDataType(IMessage* Message) override;
	ULONG GetULONG(IMessage* Message) override;
	ULONGLONG GetULONGLONG(IMessage* Message) override;
	String GetString(IMessage* Message) override;
	Binary GetBinary(IMessage* Message) override;

protected:
	CString m_Name;
	CString m_Description;
	ULONG m_Width = 0;
	ULONG m_Type = 0;
	ULONG m_Align = 0;
};
//******************************************************************************
#endif
