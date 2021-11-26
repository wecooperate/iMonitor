//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIMessageService_h_bc48cb1e_869a_44a2_9db6_c7114d14e91e__
#define __UIMessageService_h_bc48cb1e_869a_44a2_9db6_c7114d14e91e__
//******************************************************************************
#include <QObject>
//******************************************************************************
#include "UI/Service/Service.h"
#include "UIMessageColumnManager.h"
//******************************************************************************
class UIMessageService
	: public UIServiceImpl<IMessageService>
	, public cxMSGManager
{
public:
	void Initialize(void) override;
	void Uninitialize(void) override;

protected:
	void StartCapture(void) override;
	void StopCapture(void) override;
	IMessage* GetItem(int index) override;
	void RemoveAllItems(void) override;
	int GetTotalCount(void) override;
	int GetRuleApplyIndex(void) override;

protected:
	int InsertColumn(std::shared_ptr<IMessageColumn> column) override;
	void RemoteColumn(std::shared_ptr<IMessageColumn> column) override;
	std::shared_ptr<IMessageColumn> GetColumn(int index) override;
	int GetColumnCount(void) override;
	int GetColumnMaxCount(void) override;

protected:
	void OnMSGCountUpdate(bool Reset, ULONG Count) override;

protected:
	void OnRuleBeginApply() override;
	void OnRuleFinishApply() override;

private:
	UIMessageColumnManager m_ColumnManager;
	HRESULT m_StartResult = S_OK;
};
//******************************************************************************
#endif
