//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIMessageColumn_h_24c093e2_9d79_45b4_b852_4366ba5dafc2__
#define __UIMessageColumn_h_24c093e2_9d79_45b4_b852_4366ba5dafc2__
//******************************************************************************
#include <UI/Service/Service.h>
//******************************************************************************
class UIMessageColumn : public IMessageColumn
{
public:
	UIMessageColumn(const QString& name, int field_index, int width, int align = 0);

public:
	void SetVisionService(IVisionService* service);
	void SetVisible(bool enable);

public:
	QString GetName(void) override;
	int GetWidth(void) override;
	int GetAlign(void) override;
	bool IsVisible(void) override;

public:
	QString GetString(IMessage* msg) override;
	QColor GetColor(IMessage* msg) override;
	QColor GetTextColor(IMessage* msg) override;
	QIcon GetIcon(IMessage* msg) override;
	QString GetToolTipsText(IMessage* msg) override;
	int GetFieldIndex(IMessage* msg) override;

protected:
	QString m_Name;
	int m_Width;
	int m_Align;
	bool m_Visible;
	int m_FieldIndex;

protected:
	IVisionService* m_VisionService = nullptr;
};
//******************************************************************************
#endif
