//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __MSGManager_H__
#define __MSGManager_H__
//******************************************************************************
// clang-format off
//******************************************************************************
#include "MSG.h"
#include "MSGInfo.h"
#include "MSGArray.h"
#include "Core/RuleManager/IRule.h"
#include <iMonitorSDK.h>
//******************************************************************************
class cxMSGManager
	: public IMonitorCallbackInternal
	, public IRuleDelegate
{
	enum { emMinUpdateInterval = 500 };

public:
	~cxMSGManager						(void);

public:
	HRESULT			Start				(void);
	void			Stop				(void);

protected:
	void			OnCallback			(cxMSGHeader* Header, cxMSGAction* Action) override;
	void			OnRuleChanged		(bool Increase) override;

protected:
	virtual	void	OnMSG				(cxMSG* msg) {}
	virtual void	OnMSGCountUpdate	(bool Reset, ULONG Count) {}
	virtual void	OnRuleBeginApply	(void) {}
	virtual void	OnRuleFinishApply	(void) {}

public:
	cxMSG*			GetMSG				(int Index) const;

public:
	void			StartCapture		(void);
	void			StopCapture			(void);

public:
	bool			IsIncluded			(cxMSG* msg);
	ULONG			GetIncludedCount	(void);
	ULONG			GetTotalCount		(void);
	void			RemoveAll			(void);

protected:
	void			OnPreMSG			(cxMSG* msg);
	void			InsertMSG			(cxMSG* msg);
	void			UpdateMSGCount		(bool Reset = false);
	ULONG			GetNextUpdateTime	(void);

private:
	ULONG			m_SeqIndex			= -1;

protected:
	ULONG			m_UpdateInterval	= emMinUpdateInterval;
	ULONG			m_UpdateTimerId		= 0;
	ULONG			m_RuleApplyIndex	= 0;

protected:
	MonitorManager						m_Monitor;
	cxLock								m_Lock;
	std::shared_ptr<ILooper>			m_Looper;
	cxMSGArray<cxMSG, 10000, 10000>		m_MSGs;
	cxMSGArray<ULONG, 10000, 10000>		m_IncludedMSGs;
};
//******************************************************************************
#endif
