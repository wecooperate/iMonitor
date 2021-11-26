//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __IVisionService_835F3EF3_BF4C_4913_955C_5AE40F41FC84__
#define __IVisionService_835F3EF3_BF4C_4913_955C_5AE40F41FC84__
//******************************************************************************
interface IVisionService : public IService
{
	static constexpr auto NAME = "vision";

	virtual QColor GetColor(IMessage* msg, int index) = 0;
	virtual QColor GetTextColor(IMessage* msg, int index) = 0;
	virtual QIcon GetIcon(IMessage* msg, int index) = 0;

	virtual QIcon GetIcon(HICON Icon) = 0;
	virtual QIcon GetGroupIcon(int Group) = 0;
	virtual QIcon GetCallstackIcon(bool kernel) = 0;
};
//******************************************************************************
#endif
