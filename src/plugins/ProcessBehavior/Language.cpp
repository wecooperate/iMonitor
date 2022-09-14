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
#include "Language.h"
//******************************************************************************
static LANGID CurrentLangId = GetSystemDefaultLangID();
//******************************************************************************
void ChangeLanguage(LANGID LangId)
{
	CurrentLangId = LangId;
}
//******************************************************************************
LPCWSTR TranslateString(LPCWSTR Str)
{
	static std::map<CString, CString> translates = {
		{ L"CreateProcess", L"创建进程" },
		{ L"CreateRemoteThread", L"创建远程线程" },
		{ L"CreateNewFile", L"新建文件" },
		{ L"RenameFile", L"重命名文件" },
		{ L"ModifiyFile", L"修改文件" },
		{ L"ModifyRegistry", L"修改注册表" },
		{ L"AccessNetwork", L"访问网络" },
	};

	if (CurrentLangId != 2052)
		return Str;

	auto it = translates.find(Str);

	return it == translates.end() ? Str : it->second;
}
//******************************************************************************
