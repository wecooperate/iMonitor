//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIMenuService_67E3FB2F_CD5C_4716_81A9_1F6924045DEB__
#define __UIMenuService_67E3FB2F_CD5C_4716_81A9_1F6924045DEB__
//******************************************************************************
#include "../Service.h"
//******************************************************************************
class UIMenuService
	: public QObject
	, public UIServiceImpl<IMenuService>
{
	Q_OBJECT

public:
	bool InitContextMenu(int row, int column, Menu* menu) override;
	bool InitHeadMenu(int column, Menu* menu) override;

	int InsertContextMenuDelegate(std::function<void(int, int, Menu*)> delegate) override;
	int InsertHeadMenuDelegate(std::function<void(int, Menu*)> delegate) override;
	void RemoteDelegate(int id) override;

protected:
	void AddMessageMenu(Menu* menu, IMessage* msg, IMessageColumn* column);

protected:
	void InsertCopyMenu(bool IsSubMenu, Menu* menu, IMessage* msg, int field);
	void InsertRuleMenu(bool IsInclude, bool IsSubMenu, Menu* menu, IMessage* msg, int field);

protected:
	std::map<int, std::function<void(int, int, Menu*)>> m_ContextDelegates;
	std::map<int, std::function<void(int, Menu*)>> m_HeadDelegates;
	int m_IdIndex = 0;
};
//******************************************************************************
#endif
