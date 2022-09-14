//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __FileVersion_H__
#define __FileVersion_H__
//******************************************************************************
// clang-format off
//******************************************************************************
#define FOR_ALL_VERSION_FIELD(dx)												\
		dx(Comments)															\
		dx(InternalName)                   										\
		dx(ProductName)                    										\
		dx(CompanyName)                    										\
		dx(LegalCopyright)                 										\
		dx(ProductVersion)                 										\
		dx(FileDescription)                										\
		dx(LegalTrademarks)                										\
		dx(PrivateBuild)                   										\
		dx(FileVersion)                    										\
		dx(OriginalFilename)               										\
		dx(SpecialBuild)
#define MAKE_VERSION_GET_NAME(name)												\
		inline CString Get##name(void) const { return GetStringFileInfo(_T(#name)); }
//******************************************************************************
class cxFileVersion : public cxSafeObject
{
public:
	explicit cxFileVersion			(LPCTSTR Path = NULL, ULONG Flags = FILE_VER_GET_NEUTRAL);
	cxFileVersion					(cxFileVersion&& Target);
	~cxFileVersion					(void);

public:
	operator	bool				(void);

public:
	HRESULT		Reset				(LPCTSTR Path = NULL, ULONG Flags = FILE_VER_GET_NEUTRAL);

public:
	CString		GetTimestamp		(void) const;
	CString		GetStandardVersion	(void) const;
	CString		GetStringFileInfo	(LPCTSTR Type) const;

public:
	FOR_ALL_VERSION_FIELD(MAKE_VERSION_GET_NAME)

private:
	CString		m_Path;
	PVOID		m_Version			= NULL;
	ULONG		m_VersionSize		= 0;
	ULONG		m_Translation		= 0;
};
//******************************************************************************
#endif
