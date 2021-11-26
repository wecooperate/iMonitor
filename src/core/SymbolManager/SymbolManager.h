//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __SymbolManager_H__
#define __SymbolManager_H__
//******************************************************************************
#include "Symbol.h"
#include "SymbolModule.h"
//******************************************************************************
class cxSymbolParser : public cxSymbol
{
public:
	using cxSymbol::cxSymbol;

public:
	void OnBeginParse(std::function<void(cxSymbol*)> Callback);
	void OnFinishParse(std::function<void(cxSymbol*)> Callback);

public:
	void FireBeginParse(void);
	void FireFinishParse(void);

public:
	void Close(void);

protected:
	cxLock m_Lock;
	std::function<void(cxSymbol*)> m_BeginCallback;
	std::function<void(cxSymbol*)> m_FinishCallback;
};
//******************************************************************************
class cxSymbolManager
{
#define g_SymbolManager SINGLETON_(cxSymbolManager)

public:
	cxSymbolManager(void);
	~cxSymbolManager(void);

public:
	CString GetDefaultSymbolPath(void);
	void SetSymbolPath(LPCTSTR Path);

public:
	void Parse(std::weak_ptr<cxSymbolParser> Parser, std::shared_ptr<ILooper> Looper = NULL);

protected:
	bool ParseSymbol(cxSymbol* Symbol);

protected:
	cxLock m_Lock;
	std::list<cxSymbolModule> m_Modules;
	std::shared_ptr<ILooper> m_Looper;
};
//******************************************************************************
#endif
