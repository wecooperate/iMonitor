//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __IRule_h_448af63f_ad3b_4503_8924_21be2d4af660__
#define __IRule_h_448af63f_ad3b_4503_8924_21be2d4af660__
//******************************************************************************
class cxMSG;
//******************************************************************************
interface IRuleDelegate
{
	virtual void OnRuleChanged(bool Increase) = 0;
};
//******************************************************************************
interface IRuleManager
{
	virtual bool IsEnable(cxMSG* msg) = 0;
	virtual void RegisterDelegate(IRuleDelegate* Delegate) = 0;
	virtual void UnregisterDelegate(IRuleDelegate* Delegate) = 0;
};
//******************************************************************************
#endif
