//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __IMenuService_07DFAA01_2548_41F2_8701_24FAB3D087CF__
#define __IMenuService_07DFAA01_2548_41F2_8701_24FAB3D087CF__
//******************************************************************************
interface IMenuService : public IService
{
	static constexpr auto NAME = "menu";

	using Menu = QMenu;

	virtual bool InitContextMenu(int row, int column, Menu* menu) = 0;
	virtual bool InitHeadMenu(int column, Menu* menu) = 0;

	virtual int InsertContextMenuDelegate(std::function<void(int, int, Menu*)> delegate) = 0;
	virtual int InsertHeadMenuDelegate(std::function<void(int, Menu*)> delegate) = 0;
	virtual void RemoteDelegate(int id) = 0;
};
//******************************************************************************
#endif
