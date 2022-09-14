//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __MessageMatcher_h_1873968e_37f0_463a_a6a8_5ab9b818ffeb__
#define __MessageMatcher_h_1873968e_37f0_463a_a6a8_5ab9b818ffeb__
//******************************************************************************
class cxMessageFileInfoDocumentMatcher : public IMessageMatcher
{
public:
	String GetName(void) override;
	String GetDescription(void) override;
	bool IsMatch(IMessage* Message) override;
};
//******************************************************************************
class cxMessageOperationModifiableMatcher : public IMessageMatcher
{
public:
	String GetName(void) override;
	String GetDescription(void) override;
	bool IsMatch(IMessage* Message) override;
};
//******************************************************************************
const std::vector<IMessageMatcher*>& GetMatchers(void);
//******************************************************************************
#endif
