//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIVisionService_h_f7d2d167_203f_4bdb_add3_786f6c8de219__
#define __UIVisionService_h_f7d2d167_203f_4bdb_add3_786f6c8de219__
//******************************************************************************
#include <UI/Service/Service.h>
//******************************************************************************
class UIVisionService : public UIServiceImpl<IVisionService>
{
public:
	UIVisionService(void);

public:
	QColor GetColor(IMessage* msg, int index) override;
	QColor GetTextColor(IMessage* msg, int index) override;
	QIcon GetIcon(IMessage* msg, int index) override;

public:
	QIcon GetIcon(HICON Icon) override;
	QIcon GetGroupIcon(int Group) override;
	QIcon GetCallstackIcon(bool kernel) override;

protected:
	QColor m_ErrorColor;
	QColor m_Colors[emMSGGroupMax];

protected:
	QIcon m_UserIcon;
	QIcon m_KernelIcon;
	QIcon m_Icons[emMSGGroupMax];
	std::map<HICON, QIcon> m_WinIcons;
};
//******************************************************************************
#endif
