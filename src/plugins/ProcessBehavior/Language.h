//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#ifndef __Language_h_d453069c_5441_48d0_a978_e766a8e0b8b9__
#define __Language_h_d453069c_5441_48d0_a978_e766a8e0b8b9__
//******************************************************************************
void ChangeLanguage(LANGID LangId);
LPCWSTR TranslateString(LPCWSTR Str);
//******************************************************************************
#ifndef tr
#define tr(str) TranslateString(L##str)
#endif
//******************************************************************************
#endif
