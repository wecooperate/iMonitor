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
#include "MSGProcess.h"
//******************************************************************************
#define PROCESS_ACCESS_WIN10_XXX 0x2000
//******************************************************************************
static constexpr auto g_SystemProcessId = 4;
//******************************************************************************
cxMSGProcess::cxMSGProcess(ULONG ProcessId)
{
	m_ProcessId = ProcessId;
	m_ParentProcessId = 0;
	m_CreateTime = 0;
	m_ExitTime = 0;

	GetInformation();
}
//******************************************************************************
cxMSGProcess::cxMSGProcess(PSYSTEM_PROCESS_INFORMATION ProcessInfo)
{
	m_ProcessId = (ULONG)ProcessInfo->UniqueProcessId;
	m_ParentProcessId = (ULONG)ProcessInfo->InheritedFromUniqueProcessId;
	m_CreateTime = ProcessInfo->CreateTime.QuadPart;
	m_ExitTime = 0;
	m_ProcessName = CString(ProcessInfo->ImageName.Buffer, ProcessInfo->ImageName.Length / 2);

	GetInformation();
}
//******************************************************************************
cxMSGProcess::~cxMSGProcess(void)
{
	if (m_Icon) {
		DestroyIcon(m_Icon);
	}
}
//******************************************************************************
void cxMSGProcess::GetInformation(void)
{
	if (m_ProcessId == g_SystemProcessId) {
		GetKernelModule();
	} else {
		GetUserModule();
		GetBaseInformation();
	}

	LoadProcessIcon();

	m_FileVersion.Reset(m_ProcessPath);
}
//******************************************************************************
void cxMSGProcess::GetBaseInformation(void)
{
	HANDLE process_handle = OpenProcess(MAXIMUM_ALLOWED, FALSE, m_ProcessId);

	if (!process_handle)
		process_handle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, m_ProcessId);

	if (!process_handle)
		process_handle = OpenProcess(PROCESS_ACCESS_WIN10_XXX, FALSE, m_ProcessId);

	if (!process_handle)
		process_handle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, m_ProcessId);

	if (!process_handle)
		return;

	m_ProcessPath = g_ProcessManager->GetProcessPath(process_handle);
	m_Commandline = g_ProcessManager->GetProcessCommandline(process_handle);

	if (m_ProcessPath.IsEmpty())
		m_ProcessPath = m_ProcessName;
	else
		m_ProcessName = PathFindFileName(m_ProcessPath);

	FILETIME dummy = {};
	GetProcessTimes(process_handle, (PFILETIME)&m_CreateTime, (PFILETIME)&m_ExitTime, &dummy, &dummy);

	CloseHandle(process_handle);
}
//******************************************************************************
void cxMSGProcess::GetUserModule(void)
{
	for (auto& it : cxProcessModuleEnumerator(m_ProcessId)) {
		cxMSGProcessModule module;
		module.m_BaseAddress = (ULONGLONG)it->modBaseAddr;
		module.m_Size = it->modBaseSize;
		module.m_Path = it->szExePath;
		module.m_Name = it->szModule;
		InsertModule(std::move(module));
	}
}
//******************************************************************************
void cxMSGProcess::GetKernelModule(void)
{
	ULONG len = 0;

	NTSTATUS status = mod_ntdll::ZwQuerySystemInformation(
		SystemModuleInformation,
		nullptr,
		0,
		&len);

	if (STATUS_INFO_LENGTH_MISMATCH != status)
		return;

	if (0 == len)
		return;

	std::unique_ptr<char> data(new char[len]);

	status = mod_ntdll::ZwQuerySystemInformation(
		SystemModuleInformation,
		data.get(),
		len,
		&len);

	if (!NT_SUCCESS(status))
		return;

	PSYSTEM_MODULE_INFORMATION lpModule = (PSYSTEM_MODULE_INFORMATION)data.get();

	for (ULONG i = 0; i < lpModule->Count; i++) {
		PSYSTEM_MODULE_ENTRY entry = &lpModule->Module[i];

		cxMSGProcessModule module;
		module.m_BaseAddress = (ULONGLONG)entry->ModuleBaseAddress;
		module.m_Size = entry->ModuleSize;
		module.m_Name = CA2T(&entry->ModuleName[entry->OffsetToFileName]);
		module.m_Path = g_PathTransfer->Transfer(CA2T(entry->ModuleName));

		if (i == 0)
			m_ProcessPath = module.m_Path;

		InsertModule(std::move(module));
	}
}
//******************************************************************************
void cxMSGProcess::LoadProcessIcon(void)
{
	if (m_Icon)
		return;

	if (m_ProcessPath.IsEmpty()) {
		m_Icon = LoadIcon(NULL, IDI_APPLICATION);
		return;
	}

	SHFILEINFO sfi = {};
	SHGetFileInfo(m_ProcessPath, NULL, &sfi, sizeof(sfi), SHGFI_ICON);
	m_Icon = sfi.hIcon ? sfi.hIcon : LoadIcon(NULL, IDI_APPLICATION);
}
//******************************************************************************
void cxMSGProcess::FixInformation(ULONGLONG CreateTime, ULONG ParentProcessId, LPCTSTR Path, LPCTSTR Commandline)
{
	if (m_CreateTime == 0)
		m_CreateTime = CreateTime;

	if (m_ParentProcessId == 0)
		m_ParentProcessId = ParentProcessId;

	if (m_Commandline.IsEmpty())
		m_Commandline = Commandline;

	if (m_ProcessPath.IsEmpty()) {
		m_ProcessPath = Path;
		m_ProcessName = PathFindFileName(m_ProcessPath);
	}

	LoadProcessIcon();
}
//******************************************************************************
cxMSGProcessModule* cxMSGProcess::GetModule(ULONGLONG Address, ULONGLONG Time)
{
	AUTO_LOCK(m_Lock);

	for (auto& it : m_Modules) {
		if (Time != 0 && it->m_LoadTime > Time)
			continue;

		if (it->m_BaseAddress <= Address && it->m_BaseAddress + it->m_Size >= Address)
			return it.get();
	}

	return NULL;
}
//******************************************************************************
void cxMSGProcess::InsertModule(cxMSGProcessModule&& Module)
{
	AUTO_LOCK(m_Lock);

	for (auto& it : m_Modules) {
		if (it->m_BaseAddress == Module.m_BaseAddress && it->m_Path == Module.m_Path)
			return;
	}

	m_Modules.push_back(std::make_unique<cxMSGProcessModule>(std::move(Module)));
}
//******************************************************************************
void cxMSGProcess::EnumModules(std::function<bool(const cxMSGProcessModule&)> Callback)
{
	if (!Callback)
		return;

	AUTO_LOCK(m_Lock);

	for (auto& it : m_Modules) {
		if (!Callback(*it))
			break;
	}
}
//******************************************************************************
