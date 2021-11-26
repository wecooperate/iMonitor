//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UICommon_30CD153B_34AE_40FD_889A_292954F0AD7B__
#define __UICommon_30CD153B_34AE_40FD_889A_292954F0AD7B__
//******************************************************************************
void UILoadConfig(QWidget* widget);
void UISaveConfig(QWidget* widget);
void UIInitTreeView(QTreeView* view);
//******************************************************************************
template<typename T>
class UIView : public T
{
public:
	UIView(QWidget* parent = nullptr)
		: T(parent)
	{
		UILoadConfig(this);
	}

	void closeEvent(QCloseEvent* event) override
	{
		UISaveConfig(this);

		T::closeEvent(event);
	}

	__if_exists(T::done)
	{
		void done(int result) override
		{
			T::done(result);
			close();
		}
	}
};
//******************************************************************************
#endif
