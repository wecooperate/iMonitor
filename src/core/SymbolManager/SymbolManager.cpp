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
#include "SymbolManager.h"
//******************************************************************************
#pragma comment(lib, "dbghelp.lib")
//******************************************************************************
#define SYMBOL_HANDLE ((HANDLE)-12345678)
//******************************************************************************
void cxSymbolParser::OnBeginParse(std::function<void(cxSymbol*)> Callback)
{
	AUTO_LOCK(m_Lock);

	m_BeginCallback = Callback;
}
//******************************************************************************
void cxSymbolParser::OnFinishParse(std::function<void(cxSymbol*)> Callback)
{
	AUTO_LOCK(m_Lock);

	m_FinishCallback = Callback;
}
//******************************************************************************
void cxSymbolParser::FireBeginParse(void)
{
	AUTO_LOCK(m_Lock);

	if (m_BeginCallback) {
		m_BeginCallback(this);
	}
}
//******************************************************************************
void cxSymbolParser::FireFinishParse(void)
{
	AUTO_LOCK(m_Lock);

	if (m_FinishCallback) {
		m_FinishCallback(this);
	}
}
//******************************************************************************
void cxSymbolParser::Close(void)
{
	AUTO_LOCK(m_Lock);

	m_BeginCallback = NULL;
	m_FinishCallback = NULL;
}
//******************************************************************************
cxSymbolManager::cxSymbolManager(void)
{
	m_Looper = g_Looper->CreateLooper(ILooper::kUILooper, "SYM");

	SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_INCLUDE_32BIT_MODULES | SYMOPT_LOAD_LINES);
	SymInitialize(SYMBOL_HANDLE, NULL, FALSE);

	SetSymbolPath(GetDefaultSymbolPath());
}
//******************************************************************************
cxSymbolManager::~cxSymbolManager(void)
{
	for (auto& it : m_Modules) {
		it.ReleaseModule(SYMBOL_HANDLE);
	}
}
//******************************************************************************
CString cxSymbolManager::GetDefaultSymbolPath(void)
{
	auto path = g_Path->GetCurrentDirectory();
	path.Append(_T("symbols"));

	CString symbol_path = path;
	symbol_path += _T(";\nsrv*") + symbol_path + _T("*http://msdl.microsoft.com/download/symbols;");

	return symbol_path;
}
//******************************************************************************
void cxSymbolManager::SetSymbolPath(LPCTSTR Path)
{
	SymSetSearchPathW(SYMBOL_HANDLE, Path);
}
//******************************************************************************
bool cxSymbolManager::ParseSymbol(cxSymbol* Symbol)
{
	if (!Symbol)
		return false;

	if (Symbol->m_Address == 0)
		return false;

	cxSymbolModule symbol_module;

	if (!symbol_module.Initialize(Symbol->m_ModulePath))
		return false;

	{
		AUTO_LOCK(m_Lock);

		for (auto& it : m_Modules) {
			if (it.IsEqual(symbol_module)) {
				symbol_module = it;
				break;
			}
		}

		if (symbol_module.GetModuleBase() == 0) {
			if (!symbol_module.LoadModule(SYMBOL_HANDLE))
				return false;

			m_Modules.push_back(symbol_module);
		}
	}

	ULONGLONG displacement = 0;
	ULONGLONG fix_address = symbol_module.GetModuleBase() + Symbol->m_ModuleOffset;

	char data[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)] = {};
	PSYMBOL_INFO symbol_info = (PSYMBOL_INFO)data;

	symbol_info->SizeOfStruct = sizeof(SYMBOL_INFO);
	symbol_info->MaxNameLen = MAX_SYM_NAME;

	if (!SymFromAddr(SYMBOL_HANDLE, fix_address, &displacement, symbol_info))
		return false;

	CHAR symbol_name[MAX_PATH] = {};
	UnDecorateSymbolName(symbol_info->Name, symbol_name, MAX_PATH, UNDNAME_COMPLETE);

	Symbol->m_SymbolName = symbol_name;
	Symbol->m_DecoratedSymbolName = symbol_info->Name;
	Symbol->m_SymbolOffset = (ULONG)displacement;
	Symbol->m_PDBPath = symbol_module.GetPDBPath();

	IMAGEHLP_LINE64 symbol_line = {};
	symbol_line.SizeOfStruct = sizeof(symbol_line);
	DWORD line_displacement = 0;
	if (SymGetLineFromAddr64(SYMBOL_HANDLE, fix_address, &line_displacement, &symbol_line)) {
		Symbol->m_SourceFilePath = symbol_line.FileName;
		Symbol->m_SourceFileLine = symbol_line.LineNumber;
	}

	return true;
}
//******************************************************************************
void cxSymbolManager::Parse(std::weak_ptr<cxSymbolParser> Parser, std::shared_ptr<ILooper> Looper)
{
	m_Looper->PostRunnable([this, Parser, Looper]() {
		if (auto parser = Parser.lock()) {
			if (Looper) {
				Looper->RunOrPostRunnable([parser]() {
					parser->FireBeginParse();
				});
			} else {
				parser->FireBeginParse();
			}

			ParseSymbol(parser.get());

			if (Looper) {
				Looper->RunOrPostRunnable([parser]() {
					parser->FireFinishParse();
				});
			} else {
				parser->FireFinishParse();
			}
		}
	});
}
//******************************************************************************
