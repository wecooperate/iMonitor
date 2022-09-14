//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __Plugin_h_a3d10168_1104_42b3_9307_4720880b494c__
#define __Plugin_h_a3d10168_1104_42b3_9307_4720880b494c__
//******************************************************************************
class cxPlugin : public IPlugin
{
public:
	String GetName(void) override;
	String GetDescription(void) override;
	String GetAuthor(void) override;

	void Initialize(PluginContext* Context) override;
	void Release(void) override;

	ULONG GetColumnCount(void) override;
	IMessageColumn* GetColumn(ULONG Index) override;
};
//******************************************************************************
#endif
