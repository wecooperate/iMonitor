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
#include "UIManager.h"
#include <QTranslator>
//******************************************************************************
int UIStartup(void)
{
	g_Looper->Start();

	QApplication app(__argc, __argv);

	Q_INIT_RESOURCE(res);

	if (QLocale().language() == QLocale::Chinese) {
		QTranslator* translator = new QTranslator();
		translator->load(":/res/language/zh_cn.qm");
		qApp->installTranslator(translator);
	}

	g_UIManager->Initialize();

	return app.exec();
}
//******************************************************************************
