//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __SimpleRule_H__
#define __SimpleRule_H__
//******************************************************************************
#include "IRule.h"
#include "RuleMatcher.h"
//******************************************************************************
class cxSimpleRule : public cxRuleMatcher
{
	friend class cxSimpleRuleManager;

public:
	cxSimpleRule(const cxRuleMatcher& Target);
	cxSimpleRule(const cxSimpleRule& Target);

protected:
	bool m_IsInclude = true;
	bool m_IsEnable = true;
};
//******************************************************************************
class cxSimpleRuleManager : public IRuleManager
{
#ifndef g_RuleManager
#define g_RuleManager SINGLETON_(cxSimpleRuleManager)
#endif

public:
	cxSimpleRuleManager(void);
	~cxSimpleRuleManager(void);

public:
	bool IsEnable(cxMSG* msg) override;
	void RegisterDelegate(IRuleDelegate* Delegate) override;
	void UnregisterDelegate(IRuleDelegate* Delegate) override;

public:
	void InsertRule(const cxRuleMatcher& Matcher, bool IsInclude = true, bool Enable = true);

	void RemoveAllIncludeRules(void);
	void RemoveAllExcludeRules(void);
	void RemoteAllRules(void);
	void DisableAllRules(void);

	bool HasLastRule(void);
	void RemoteLastRule(void);

	void ResetRules(std::list<std::shared_ptr<cxSimpleRule>> Rules);
	void EnumRules(std::function<bool(const cxSimpleRule*)> Delegate);

	void OnRuleChanged(bool Increase);

protected:
	void RebuildRules(bool ResetLastRule = true);
	void LoadConfig(void);
	void SaveConfig(void);

protected:
	cxLock m_Lock;
	std::set<IRuleDelegate*> m_Delegates;
	std::shared_ptr<cxSimpleRule> m_LastRule;
	std::list<std::shared_ptr<cxSimpleRule>> m_IncludeRules;
	std::list<std::shared_ptr<cxSimpleRule>> m_ExcludeRules;
	std::list<std::shared_ptr<cxSimpleRule>> m_AllRules;
};
//******************************************************************************
#endif
