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
#include "UIStatusBar.h"
#include <Psapi.h>
//******************************************************************************
UIStatusBar::UIStatusBar(QWidget* parent)
	: QStatusBar(parent)
{
	m_LabelMSGCount = new QLabel();
	m_LabelMSGCount->setAlignment(Qt::AlignLeft);
	addWidget(m_LabelMSGCount);

	HandleEvent([this](const ServiceEventMSGUpdate& event) {
		OnUpdate(event);
	});
}
//******************************************************************************
void UIStatusBar::OnUpdate(const ServiceEventMSGUpdate& event)
{
	if (event.TotalCount == 0) {
		m_LabelMSGCount->setText("");
		return;
	}

	uint32_t count = event.Count;
	uint32_t total_count = event.TotalCount;
	auto percent = (double)count * 100 / (double)total_count;

	QString str = QString(" Showing %1 of %2 Events (%3%) ")
					  .arg(QLocale().toString(count))
					  .arg(QLocale().toString(total_count))
					  .arg(QString::number(percent, 'f', 2));

	m_LabelMSGCount->setText(str);
}
//******************************************************************************
