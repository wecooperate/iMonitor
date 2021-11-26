//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __MSGArray_H__
#define __MSGArray_H__
//******************************************************************************
template<typename T, size_t MaxRow, size_t MaxRawCount>
class cxMSGArray
{
public:
	~cxMSGArray()
	{
		for (size_t row = 0; row < MaxRow; row++) {
			if (m_Data[row])
				VirtualFree(m_Data[row], 0, MEM_RELEASE);
		}
	}

	ULONG GetCount(void) const
	{
		return m_Count;
	}

	T* Get(ULONG Index) const
	{
		if (Index >= m_Count)
			return NULL;

		return &m_Data[Index / MaxRawCount][Index % MaxRawCount];
	}

	T* Alloc(void)
	{
		if (m_Column == MaxRawCount)
			m_Column = 0;

		if (m_Column == 0) {
			if (m_Row == MaxRow)
				return NULL;

			if (!m_Data[m_Row])
				m_Data[m_Row] = (T*)VirtualAlloc(NULL, sizeof(T) * MaxRawCount, MEM_COMMIT, PAGE_READWRITE);

			if (!m_Data[m_Row])
				return NULL;

			m_Row++;
		}

		m_Column++;
		m_Count++;

		return &m_Data[m_Row - 1][m_Column - 1];
	}

	void RemoveAll()
	{
		for (int row = 0; row < MaxRow; row++) {
			if (m_Data[row]) {
				VirtualFree(m_Data[row], 0, MEM_RELEASE);
				m_Data[row] = NULL;
			}
		}

		ResetCount();
	}

	void ResetCount()
	{
		m_Row = 0;
		m_Column = 0;
		m_Count = 0;
	}

public:
	ULONG m_Row = 0;
	ULONG m_Column = 0;
	ULONG m_Count = 0;
	T* m_Data[MaxRow] = {};
};
//******************************************************************************
#endif
