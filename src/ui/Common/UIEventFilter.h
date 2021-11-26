//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIEventFilter_h_00a16890_c38a_461d_92fa_ce76577f1552__
#define __UIEventFilter_h_00a16890_c38a_461d_92fa_ce76577f1552__
//******************************************************************************
class UIEventFilter : public QObject
{
	Q_OBJECT

public:
	explicit UIEventFilter(QObject* parent = NULL);

protected:
	virtual bool eventFilter(QObject* object, QEvent* event);

protected:
	bool FixToolTip(QObject* object, QEvent* event);
};
//******************************************************************************
#endif
