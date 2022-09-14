//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/
//******************************************************************************
#include "stdafx.h"
#include "IPRegion.h"
//******************************************************************************
#include "xdb/xdb_searcher.h"
#include "xdb/xdb_searcher.c"
//******************************************************************************
static xdb_searcher_t searcher;
static bool success = false;
//******************************************************************************
cxIPRegion::cxIPRegion(void)
{
	auto path = g_Path->GetCurrentPath(_T("ip2region.xdb"));

	auto err = xdb_new_with_file_only(&searcher, (LPCSTR)CT2A(path, CP_UTF8));

	success = err == 0;
}
//******************************************************************************
CString cxIPRegion::GetIPRegion(ULONG IP)
{
	if (!success)
		return CString();

	AUTO_LOCK(m_Lock);

	if (auto it = m_IPCaches.find(IP); it != m_IPCaches.end())
		return it->second;

	CStringA str;
	str.Format("%d.%d.%d.%d",
		((PUCHAR)&IP)[0],
		((PUCHAR)&IP)[1],
		((PUCHAR)&IP)[2],
		((PUCHAR)&IP)[3]);

	char region_buffer[256] = {};

	auto err = xdb_search_by_string(&searcher, str, region_buffer, sizeof(region_buffer));
	if (err != 0)
		return CString();

	CString region = (LPCTSTR)CA2T(region_buffer, CP_UTF8);

	CString result;

	int start = 0;

	do {
		auto token = region.Tokenize(_T("|"), start);

		if (token.IsEmpty())
			break;

		if (token == _T("0"))
			continue;

		if (!result.IsEmpty()) {
			result += _T(".");
		}

		result += token;

	} while (true);

	if (result.Find(_T("ÄÚÍøIP")) != -1) {
		result = _T("ÄÚÍøµØÖ·");
	}

	m_IPCaches[IP] = result;

	return result;
}
//******************************************************************************
