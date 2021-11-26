//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __UIMessageColumnManager_h_aa12c61f_af05_4c20_bfab_9ac9902adbda__
#define __UIMessageColumnManager_h_aa12c61f_af05_4c20_bfab_9ac9902adbda__
//******************************************************************************
#include "UIMessageColumn.h"
//******************************************************************************
class UIMessageColumnManager
{
public:
	void Initialize(IVisionService* service);

public:
	std::shared_ptr<IMessageColumn> GetColumn(int index);
	int GetColumnCount(void);
	int GetMaxColumnCount(void);

public:
	int Insert(const QString& name, int field_index, int width, int align = 0);
	int Insert(std::shared_ptr<IMessageColumn> column);
	void Remove(std::shared_ptr<IMessageColumn> column);

protected:
	IVisionService* m_VisionService;
	std::vector<std::shared_ptr<IMessageColumn>> m_Columns;
	std::vector<std::shared_ptr<IMessageColumn>> m_VisibleColumns;
};
//******************************************************************************
#endif
