//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __IMessageService_E2ADF155_C9E5_4051_B31E_C3AF26343455__
#define __IMessageService_E2ADF155_C9E5_4051_B31E_C3AF26343455__
//******************************************************************************
class cxMSG;
using IMessage = cxMSG;
//******************************************************************************
interface IMessageColumn
{
	virtual ~IMessageColumn() = default;

	virtual QString GetName(void) = 0;
	virtual int GetWidth(void) = 0;
	virtual int GetAlign(void) = 0;
	virtual bool IsVisible(void) = 0;

	virtual QString GetString(IMessage* msg) = 0;
	virtual QColor GetColor(IMessage* msg) = 0;
	virtual QColor GetTextColor(IMessage* msg) = 0;
	virtual QIcon GetIcon(IMessage* msg) = 0;
	virtual QString GetToolTipsText(IMessage* msg) = 0;
	virtual int GetFieldIndex(IMessage* msg) = 0;
};
//******************************************************************************
interface IMessageService : public IService
{
	static constexpr auto NAME = "message";

	virtual void StartCapture(void) = 0;
	virtual void StopCapture(void) = 0;
	virtual IMessage* GetItem(int index) = 0;
	virtual void RemoveAllItems(void) = 0;
	virtual int GetTotalCount(void) = 0;
	virtual int GetRuleApplyIndex(void) = 0;

	virtual int InsertColumn(std::shared_ptr<IMessageColumn> column) = 0;
	virtual void RemoteColumn(std::shared_ptr<IMessageColumn> column) = 0;
	virtual std::shared_ptr<IMessageColumn> GetColumn(int index) = 0;
	virtual int GetColumnCount(void) = 0;
	virtual int GetColumnMaxCount(void) = 0;
};
//******************************************************************************
#endif
