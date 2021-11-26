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
#include "SymbolModule.h"
//******************************************************************************
bool cxSymbolModule::Initialize(LPCTSTR Path)
{
	m_Path = Path;
	m_Name = PathFindFileName(m_Path);

	WIN32_FILE_ATTRIBUTE_DATA attr = {};

	if (!GetFileAttributesEx(m_Path, GetFileExInfoStandard, &attr))
		return false;

	CString path_low = Path;
	path_low.MakeLower();

	m_FileSize = MakeULONGLONG(attr.nFileSizeLow, attr.nFileSizeHigh);
	m_LastWriteTime = *(PULONGLONG)&attr.ftLastWriteTime;
	m_FastHash = CRC64(path_low);
	m_FastHash = CRC64(m_FileSize, m_FastHash);
	m_FastHash = CRC64(m_LastWriteTime, m_FastHash);

	return true;
}
//******************************************************************************
bool cxSymbolModule::LoadModule(HANDLE SymHandle)
{
	if (m_SymbolImageBase) {
		SymUnloadModule64(SymHandle, m_SymbolImageBase);
		m_SymbolImageBase = NULL;
		m_PDBPath.Empty();
	}

	if (!m_DebugData) {
		if (!m_FastHash || !LoadDebugData())
			return false;
	}

	MODLOAD_DATA mod_data = {};
	mod_data.ssize = sizeof(mod_data);
	mod_data.ssig = DBHHEADER_DEBUGDIRS;
	mod_data.size = m_DebugDataLength;
	mod_data.data = m_DebugData;

	static ULONGLONG symbol_image_base = 0x80000000;

	m_SymbolImageBase = SymLoadModuleExW(
		SymHandle,
		NULL,
		m_Path,
		NULL,
		symbol_image_base,
		m_SizeOfImage,
		&mod_data,
		0);

	if (m_SymbolImageBase == 0)
		return false;

	symbol_image_base += m_SizeOfImage;

	TCHAR pdb[MAX_PATH] = {};
	SymGetSymbolFileW(
		SymHandle,
		NULL,
		m_Path,
		sfPdb,
		pdb,
		MAX_PATH,
		NULL,
		0);

	m_PDBPath = pdb;

	return true;
}
//******************************************************************************
bool cxSymbolModule::ForceLoadModule(HANDLE SymHandle, LPCTSTR PDBPath)
{
	return false;
}
//******************************************************************************
void cxSymbolModule::ReleaseModule(HANDLE SymHandle)
{
	if (m_SymbolImageBase) {
		SymUnloadModule64(SymHandle, m_SymbolImageBase);
		m_SymbolImageBase = 0;
		m_PDBPath.Empty();
	}

	ReleaseDebugData();
}
//******************************************************************************
CString cxSymbolModule::GetPDBPath(void)
{
	return m_PDBPath;
}
//******************************************************************************
bool cxSymbolModule::LoadDebugData(void)
{
	if (m_DebugData)
		return true;

	cxHandle file = CreateFile(
		m_Path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (!file)
		return false;

	ULONG file_size = GetFileSize(file, NULL);

	if (file_size == 0 || file_size == INVALID_FILE_SIZE)
		return false;

	cxHandle filemapping = CreateFileMapping(file, NULL, PAGE_READONLY, 0, file_size, NULL);

	if (!filemapping)
		return false;

	PVOID image = MapViewOfFile(filemapping, FILE_MAP_READ, 0, 0, 0);

	if (!image)
		return false;

	PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)image;
	PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((PCHAR)image + dos_header->e_lfanew);

	if (nt_headers->FileHeader.Machine != IMAGE_FILE_MACHINE_AMD64) {
		m_ImageBase = nt_headers->OptionalHeader.ImageBase;
		m_SizeOfImage = nt_headers->OptionalHeader.SizeOfImage;
	} else {
		PIMAGE_NT_HEADERS64 nt_headers64 = (PIMAGE_NT_HEADERS64)nt_headers;
		m_ImageBase = nt_headers64->OptionalHeader.ImageBase;
		m_SizeOfImage = nt_headers64->OptionalHeader.SizeOfImage;
	}

	ULONG debug_data_len = 0;
	PIMAGE_DEBUG_DIRECTORY debug_data = (PIMAGE_DEBUG_DIRECTORY)ImageDirectoryEntryToData(image, FALSE, IMAGE_DIRECTORY_ENTRY_DEBUG, &debug_data_len);

	if (!debug_data || debug_data_len < sizeof(IMAGE_DEBUG_DIRECTORY)) {
		UnmapViewOfFile(image);
		return false;
	}

	m_DebugDataLength = sizeof(IMAGE_DEBUG_DIRECTORY) + debug_data->SizeOfData;
	m_DebugData = new char[m_DebugDataLength];

	*(PIMAGE_DEBUG_DIRECTORY)m_DebugData = *debug_data;
	((PIMAGE_DEBUG_DIRECTORY)m_DebugData)->PointerToRawData = sizeof(IMAGE_DEBUG_DIRECTORY);
	((PIMAGE_DEBUG_DIRECTORY)m_DebugData)->AddressOfRawData = 0;

	memcpy((PCHAR)m_DebugData + sizeof(IMAGE_DEBUG_DIRECTORY), (PCHAR)image + debug_data->PointerToRawData, debug_data->SizeOfData);

	UnmapViewOfFile(image);

	m_DebugDataHash = CRC64((PUCHAR)m_DebugData, m_DebugDataLength);

	return true;
}
//******************************************************************************
void cxSymbolModule::ReleaseDebugData(void)
{
	if (!m_DebugData)
		return;

	delete (char*)m_DebugData;

	m_DebugData = NULL;
	m_DebugDataLength = 0;
	m_DebugDataHash = 0;
}
//******************************************************************************
bool cxSymbolModule::IsEqual(const cxSymbolModule& Module)
{
	return m_FastHash == Module.m_FastHash;
}
//******************************************************************************
bool cxSymbolModule::IsEqualDebugData(const cxSymbolModule& Module)
{
	return m_DebugDataHash == Module.m_DebugDataHash;
}
//******************************************************************************
ULONGLONG cxSymbolModule::GetModuleBase(void)
{
	return m_SymbolImageBase;
}
//******************************************************************************
