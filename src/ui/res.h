//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __res_h_82199058_dca0_48ae_908c_46226c7bf819__
#define __res_h_82199058_dca0_48ae_908c_46226c7bf819__
//******************************************************************************
class UIResource
{
#define g_res SINGLETON_(UIResource)

public:
	QIcon icon_main = QIcon(":/res/main.ico");
	QIcon icon_locate = QIcon(":/res/locate.ico");
	QIcon icon_filter = QIcon(":/res/filter.ico");
	QIcon icon_find = QIcon(":/res/find.ico");
	QIcon icon_color = QIcon(":/res/color.ico");
	QIcon icon_clear = QIcon(":/res/clear.ico");
	QIcon icon_boolmark = QIcon(":/res/bookmark.ico");
	QIcon icon_autoscroll = QIcon(":/res/autoscroll.ico");
	QIcon icon_start = QIcon(":/res/start.ico");
	QIcon icon_setting = QIcon(":/res/setting.ico");
	QIcon icon_save = QIcon(":/res/save.ico");
	QIcon icon_open = QIcon(":/res/open.ico");
	QIcon icon_add = QIcon(":/res/add.svg");
	QIcon icon_list = QIcon(":/res/list.svg");
	QIcon icon_switch_on = QIcon(":/res/on.svg");
	QIcon icon_switch_off = QIcon(":/res/off.svg");

	QIcon icon_msg_file = QIcon(":/res/F.ico");
	QIcon icon_msg_process = QIcon(":/res/P.ico");
	QIcon icon_msg_network = QIcon(":/res/N.ico");
	QIcon icon_msg_registry = QIcon(":/res/R.ico");
	QIcon icon_msg_kernel = QIcon(":/res/K.ico");
	QIcon icon_msg_user = QIcon(":/res/U.ico");
};
//******************************************************************************
#endif
