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
#include "ProcessManager.h"
//******************************************************************************
#include <ShellAPI.h>
#include <Userenv.h>
#include <Wtsapi32.h>
#include <Psapi.h>
//******************************************************************************
#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib, "Userenv.lib")
#pragma comment(lib, "PsApi.lib")
//******************************************************************************
#define PROCESS_ACCESS_WIN10_XXX 0x2000
//******************************************************************************
CString cxProcessManager::GetProcessPath(ULONG ProcessId)
{
	HANDLE ProcessHandle = OpenProcess(
		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE,
		ProcessId);

	if (!ProcessHandle) {
		ProcessHandle = OpenProcess(PROCESS_ACCESS_WIN10_XXX, FALSE, ProcessId);

		if (!ProcessHandle)
			return CString();
	}

	CString strPath = GetProcessPath(ProcessHandle);

	CloseHandle(ProcessHandle);

	return strPath;
}
//******************************************************************************
CString cxProcessManager::GetProcessPath(HANDLE ProcessHandle)
{
	TCHAR lpPath[MAX_PATH + 1] = {};

	do {
		DWORD dwRetSize = MAX_PATH;

		if (mod_kernel32::QueryFullProcessImageNameW(ProcessHandle, 0, lpPath, &dwRetSize))
			break;

		if (0 != GetModuleFileNameEx(ProcessHandle, NULL, lpPath, MAX_PATH))
			break;

		if (0 != GetProcessImageFileName(ProcessHandle, lpPath, MAX_PATH))
			return g_PathTransfer->Transfer(lpPath);
	} while (FALSE);

	return lpPath;
}
//******************************************************************************
CString cxProcessManager::GetProcessCommandline(HANDLE ProcessHandle)
{
	if (g_WOW64->IsWOW64Process() && !g_WOW64->IsWOW64Process(ProcessHandle))
		return GetProcessCommandlineWOW64(ProcessHandle);

	do {
		if (!ProcessHandle)
			break;

		PROCESS_BASIC_INFORMATION info = {};
		ULONG len = sizeof(info);

		NTSTATUS status = mod_ntdll::ZwQueryInformationProcess(
			ProcessHandle,
			0,
			&info,
			len,
			&len);

		if (!NT_SUCCESS(status))
			break;

		if (!info.PebBaseAddress)
			break;

		PVOID addr = (PVOID)((ULONG_PTR) & ((PPEB)0)->ProcessParameters + (ULONG_PTR)info.PebBaseAddress);

		if (!addr)
			break;

		SIZE_T length = 0;

		if (!ReadProcessMemory(
				ProcessHandle,
				addr,
				&addr,
				sizeof(addr),
				&length))
			break;

		RTL_USER_PROCESS_PARAMETERS process_parameters = {};

		if (!ReadProcessMemory(
				ProcessHandle,
				addr,
				&process_parameters,
				sizeof(RTL_USER_PROCESS_PARAMETERS),
				&length))
			break;

		if (!process_parameters.CommandLine.Buffer || 0 == process_parameters.CommandLine.Length)
			break;

		std::unique_ptr<WCHAR> data(new WCHAR[process_parameters.CommandLine.Length / sizeof(WCHAR) + 1]);

		if (!data)
			break;

		memset(data.get(), 0, process_parameters.CommandLine.Length + sizeof(WCHAR));

		if (!ReadProcessMemory(
				ProcessHandle,
				process_parameters.CommandLine.Buffer,
				data.get(),
				process_parameters.CommandLine.Length,
				&length))
			break;

		return CString(data.get());
	} while (false);

	return _T("");
}
//******************************************************************************
CString cxProcessManager::GetProcessCommandline(ULONG ProcessId)
{
	HANDLE ProcessHandle = OpenProcess(
		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE,
		ProcessId);

	if (!ProcessHandle) {
		ProcessHandle = OpenProcess(PROCESS_ACCESS_WIN10_XXX, FALSE, ProcessId);

		if (!ProcessHandle)
			return CString();
	}

	CString strPath = GetProcessCommandline(ProcessHandle);

	CloseHandle(ProcessHandle);

	return strPath;
}
//******************************************************************************
CString cxProcessManager::GetProcessCommandlineWOW64(HANDLE ProcessHandle)
{
	do {
		if (!ProcessHandle)
			break;

		PROCESS_BASIC_INFORMATION64 info = {};
		ULONG len = sizeof(info);

		NTSTATUS status = mod_ntdll::ZwWow64QueryInformationProcess64(
			ProcessHandle,
			0,
			&info,
			len,
			&len);

		if (!NT_SUCCESS(status))
			break;

		if (!info.PebBaseAddress)
			break;

		ULONGLONG addr = (ULONGLONG)((ULONGLONG) & ((PPEB64)0)->ProcessParameters + info.PebBaseAddress);

		if (!addr)
			break;

		ULONGLONG length = 0;

		status = mod_ntdll::ZwWow64ReadVirtualMemory64(
			ProcessHandle,
			addr,
			&addr,
			sizeof(addr),
			&length);

		if (!NT_SUCCESS(status))
			break;

		RTL_USER_PROCESS_PARAMETERS64 process_parameters = {};

		status = mod_ntdll::ZwWow64ReadVirtualMemory64(
			ProcessHandle,
			addr,
			&process_parameters,
			sizeof(process_parameters),
			&length);

		if (!NT_SUCCESS(status))
			break;

		if (!process_parameters.CommandLine.Buffer || 0 == process_parameters.CommandLine.Length)
			break;

		std::unique_ptr<WCHAR> data(new WCHAR[process_parameters.CommandLine.Length / sizeof(WCHAR) + 1]);

		if (!data)
			break;

		memset(data.get(), 0, process_parameters.CommandLine.Length + sizeof(WCHAR));

		status = mod_ntdll::ZwWow64ReadVirtualMemory64(
			ProcessHandle,
			process_parameters.CommandLine.Buffer,
			(PVOID)(LPCWSTR)data.get(),
			process_parameters.CommandLine.Length,
			&length);

		if (!NT_SUCCESS(status))
			break;

		return CString(data.get());
	} while (false);

	return _T("");
}
//******************************************************************************
