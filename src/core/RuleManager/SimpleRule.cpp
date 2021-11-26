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
#include "SimpleRule.h"
#include "Config.h"
//******************************************************************************
cxSimpleRule::cxSimpleRule(const cxRuleMatcher& Target)
	: cxRuleMatcher(Target)
{
}
//******************************************************************************
cxSimpleRule::cxSimpleRule(const cxSimpleRule& Target)
	: cxRuleMatcher(Target)
	, m_IsInclude(Target.m_IsInclude)
	, m_IsEnable(Target.m_IsEnable)
{
}
//******************************************************************************
cxSimpleRuleManager::cxSimpleRuleManager(void)
{
	LoadConfig();
}
//******************************************************************************
cxSimpleRuleManager::~cxSimpleRuleManager(void)
{
	SaveConfig();
}
//******************************************************************************
bool cxSimpleRuleManager::IsEnable(cxMSG* msg)
{
	if (!g_Config->IsMSGEnable(msg->m_Type))
		return false;

	AUTO_LOCK(m_Lock);

	if (!m_IncludeRules.empty()) {
		for (auto& it : m_IncludeRules)
			if (!it->IsMatch(msg))
				return false;
	}

	for (auto& it : m_ExcludeRules) {
		if (it->IsMatch(msg))
			return false;
	}

	return true;
}
//******************************************************************************
void cxSimpleRuleManager::RegisterDelegate(IRuleDelegate* Delegate)
{
	if (!Delegate)
		return;

	AUTO_LOCK(m_Lock);

	m_Delegates.insert(Delegate);
}
//******************************************************************************
void cxSimpleRuleManager::UnregisterDelegate(IRuleDelegate* Delegate)
{
	if (!Delegate)
		return;

	AUTO_LOCK(m_Lock);

	m_Delegates.erase(Delegate);
}
//******************************************************************************
void cxSimpleRuleManager::InsertRule(const cxRuleMatcher& Matcher, bool IsInclude, bool Enable)
{
	auto rule = std::make_shared<cxSimpleRule>(Matcher);
	rule->m_IsEnable = Enable;
	rule->m_IsInclude = IsInclude;

	AUTO_LOCK(m_Lock);

	m_AllRules.push_back(rule);

	if (!Enable)
		return;

	auto& rules = IsInclude ? m_IncludeRules : m_ExcludeRules;
	rules.push_back(rule);

	m_LastRule = rule;

	OnRuleChanged(true);
}
//******************************************************************************
void cxSimpleRuleManager::RemoveAllIncludeRules(void)
{
	AUTO_LOCK(m_Lock);

	m_LastRule.reset();
	m_IncludeRules.clear();

	for (auto it = m_AllRules.begin(); it != m_AllRules.end();) {
		if ((*it)->m_IsInclude)
			it = m_AllRules.erase(it);
		else
			it++;
	}

	OnRuleChanged(false);
}
//******************************************************************************
void cxSimpleRuleManager::RemoveAllExcludeRules(void)
{
	AUTO_LOCK(m_Lock);

	m_LastRule.reset();
	m_ExcludeRules.clear();

	for (auto it = m_AllRules.begin(); it != m_AllRules.end();) {
		if (!(*it)->m_IsInclude)
			it = m_AllRules.erase(it);
		else
			it++;
	}

	OnRuleChanged(false);
}
//******************************************************************************
void cxSimpleRuleManager::RemoteAllRules(void)
{
	AUTO_LOCK(m_Lock);

	m_AllRules.clear();

	RebuildRules();

	OnRuleChanged(false);
}
//******************************************************************************
void cxSimpleRuleManager::DisableAllRules(void)
{
	AUTO_LOCK(m_Lock);

	for (auto& it : m_AllRules)
		it->m_IsEnable = false;

	RebuildRules();

	OnRuleChanged(false);
}
//******************************************************************************
bool cxSimpleRuleManager::HasLastRule(void)
{
	AUTO_LOCK(m_Lock);

	return m_LastRule != nullptr;
}
//******************************************************************************
void cxSimpleRuleManager::RemoteLastRule(void)
{
	AUTO_LOCK(m_Lock);

	if (!m_LastRule)
		return;

	for (auto it = m_AllRules.begin(); it != m_AllRules.end(); ++it) {
		if (*it == m_LastRule) {
			m_AllRules.erase(it);
			RebuildRules();
			return;
		}
	}

	OnRuleChanged(false);
}
//******************************************************************************
void cxSimpleRuleManager::ResetRules(std::list<std::shared_ptr<cxSimpleRule>> Rules)
{
	AUTO_LOCK(m_Lock);

	m_AllRules = std::move(Rules);

	RebuildRules();

	OnRuleChanged(false);
}
//******************************************************************************
void cxSimpleRuleManager::EnumRules(std::function<bool(const cxSimpleRule*)> Delegate)
{
	AUTO_LOCK(m_Lock);

	for (auto& it : m_AllRules) {
		if (!Delegate(it.get()))
			break;
	}
}
//******************************************************************************
void cxSimpleRuleManager::OnRuleChanged(bool Increase)
{
	for (auto& it : m_Delegates) {
		it->OnRuleChanged(Increase);
	}
}
//******************************************************************************
void cxSimpleRuleManager::RebuildRules(bool ResetLastRule)
{
	if (ResetLastRule) {
		m_LastRule.reset();
	}

	m_IncludeRules.clear();
	m_ExcludeRules.clear();

	for (auto& it : m_AllRules) {
		if (!it->m_IsEnable)
			continue;

		auto& rules = it->m_IsInclude ? m_IncludeRules : m_ExcludeRules;

		rules.push_back(it);
	}
}
//******************************************************************************
void cxSimpleRuleManager::LoadConfig(void)
{
	// TODO
}
//******************************************************************************
void cxSimpleRuleManager::SaveConfig(void)
{
	// TODO
}
//******************************************************************************
