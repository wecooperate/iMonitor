#pragma once

namespace proto {

struct MSGField
{
	ULONG Type;
	LPCWSTR Name;
};

struct MSGInfo
{
	ULONG Type;
	LPCWSTR Name;
	ULONG FieldCount;
	MSGField* Fields;
};

struct ProcessCreate
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldProcessId,
		emFieldCommandline,
		emFieldCreateTime,
		emFieldParentPath,
		emFieldParentProcessId,
		emFieldParentCommandline,
		emFieldParentCreateTime,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ProcessId" },
			{ emMSGDataString, L"Commandline" },
			{ emMSGDataTime, L"CreateTime" },
			{ emMSGDataPath, L"ParentPath" },
			{ emMSGDataULONG, L"ParentProcessId" },
			{ emMSGDataString, L"ParentCommandline" },
			{ emMSGDataTime, L"ParentCreateTime" },
		};
		static MSGInfo info = {
			emMSGProcessCreate,
			L"ProcessCreate",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct ProcessExit
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldProcessId,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ProcessId" },
		};
		static MSGInfo info = {
			emMSGProcessExit,
			L"ProcessExit",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct ProcessOpen
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldProcessId,
		emFieldParentProcessId,
		emFieldDesiredAccess,
		emFieldDuplicate,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ProcessId" },
			{ emMSGDataULONG, L"ParentProcessId" },
			{ emMSGDataProcessAccess, L"DesiredAccess" },
			{ emMSGDataBool, L"Duplicate" },
		};
		static MSGInfo info = {
			emMSGProcessOpen,
			L"ProcessOpen",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct ThreadCreate
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldProcessId,
		emFieldThreadId,
		emFieldStartAddress,
		emFieldRemoteThread,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ProcessId" },
			{ emMSGDataULONG, L"ThreadId" },
			{ emMSGDataULONGLONG, L"StartAddress" },
			{ emMSGDataBool, L"RemoteThread" },
		};
		static MSGInfo info = {
			emMSGThreadCreate,
			L"ThreadCreate",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct ThreadExit
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldProcessId,
		emFieldThreadId,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ProcessId" },
			{ emMSGDataULONG, L"ThreadId" },
		};
		static MSGInfo info = {
			emMSGThreadExit,
			L"ThreadExit",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct ThreadOpen
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldProcessId,
		emFieldParentProcessId,
		emFieldDesiredAccess,
		emFieldDuplicate,
		emFieldThreadId,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ProcessId" },
			{ emMSGDataULONG, L"ParentProcessId" },
			{ emMSGDataThreadAccess, L"DesiredAccess" },
			{ emMSGDataBool, L"Duplicate" },
			{ emMSGDataULONG, L"ThreadId" },
		};
		static MSGInfo info = {
			emMSGThreadOpen,
			L"ThreadOpen",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct ImageLoad
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldProcessId,
		emFieldImageBase,
		emFieldImageSize,
		emFieldIsKernelImage,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ProcessId" },
			{ emMSGDataULONGLONG, L"ImageBase" },
			{ emMSGDataULONGLONG, L"ImageSize" },
			{ emMSGDataBool, L"IsKernelImage" },
		};
		static MSGInfo info = {
			emMSGImageLoad,
			L"ImageLoad",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct ProcessStart
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldProcessId,
		emFieldCommandline,
		emFieldCreateTime,
		emFieldParentPath,
		emFieldParentProcessId,
		emFieldParentCommandline,
		emFieldParentCreateTime,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ProcessId" },
			{ emMSGDataString, L"Commandline" },
			{ emMSGDataTime, L"CreateTime" },
			{ emMSGDataPath, L"ParentPath" },
			{ emMSGDataULONG, L"ParentProcessId" },
			{ emMSGDataString, L"ParentCommandline" },
			{ emMSGDataTime, L"ParentCreateTime" },
		};
		static MSGInfo info = {
			emMSGProcessStart,
			L"ProcessStart",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct ThreadStart
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldProcessId,
		emFieldThreadId,
		emFieldStartAddress,
		emFieldRemoteThread,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ProcessId" },
			{ emMSGDataULONG, L"ThreadId" },
			{ emMSGDataULONGLONG, L"StartAddress" },
			{ emMSGDataBool, L"RemoteThread" },
		};
		static MSGInfo info = {
			emMSGThreadStart,
			L"ThreadStart",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileCreate
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldAttributes,
		emFieldAccess,
		emFieldShareAccess,
		emFieldCreateDisposition,
		emFieldCreateOptions,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataFileAttributes, L"Attributes" },
			{ emMSGDataFileAccess, L"Access" },
			{ emMSGDataFileShareAccess, L"ShareAccess" },
			{ emMSGDataFileDisposition, L"CreateDisposition" },
			{ emMSGDataFileOptions, L"CreateOptions" },
		};
		static MSGInfo info = {
			emMSGFileCreate,
			L"FileCreate",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostCreate
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldAttributes,
		emFieldAccess,
		emFieldShareAccess,
		emFieldCreateDisposition,
		emFieldCreateOptions,
		emFieldInformation,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataFileAttributes, L"Attributes" },
			{ emMSGDataFileAccess, L"Access" },
			{ emMSGDataFileShareAccess, L"ShareAccess" },
			{ emMSGDataFileDisposition, L"CreateDisposition" },
			{ emMSGDataFileOptions, L"CreateOptions" },
			{ emMSGDataULONG, L"Information" },
		};
		static MSGInfo info = {
			emMSGFilePostCreate,
			L"FilePostCreate",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileQueryOpen
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
		};
		static MSGInfo info = {
			emMSGFileQueryOpen,
			L"FileQueryOpen",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostQueryOpen
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldCreationTime,
		emFieldLastAccessTime,
		emFieldLastWriteTime,
		emFieldChangeTime,
		emFieldFileSize,
		emFieldFileAttributes,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataTime, L"CreationTime" },
			{ emMSGDataTime, L"LastAccessTime" },
			{ emMSGDataTime, L"LastWriteTime" },
			{ emMSGDataTime, L"ChangeTime" },
			{ emMSGDataULONGLONG, L"FileSize" },
			{ emMSGDataFileAttributes, L"FileAttributes" },
		};
		static MSGInfo info = {
			emMSGFilePostQueryOpen,
			L"FilePostQueryOpen",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileCleanup
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldInformation,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"Information" },
		};
		static MSGInfo info = {
			emMSGFileCleanup,
			L"FileCleanup",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileCreateSection
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldPageProtection,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataFilePageProtection, L"PageProtection" },
		};
		static MSGInfo info = {
			emMSGFileCreateSection,
			L"FileCreateSection",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostCreateSection
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldPageProtection,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataFilePageProtection, L"PageProtection" },
		};
		static MSGInfo info = {
			emMSGFilePostCreateSection,
			L"FilePostCreateSection",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileRead
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldReadLength,
		emFieldOffset,
		emFieldBuffer,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ReadLength" },
			{ emMSGDataULONGLONG, L"Offset" },
			{ emMSGDataULONGLONG, L"Buffer" },
		};
		static MSGInfo info = {
			emMSGFileRead,
			L"FileRead",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostRead
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldReadLength,
		emFieldOffset,
		emFieldBuffer,
		emFieldReturnLength,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"ReadLength" },
			{ emMSGDataULONGLONG, L"Offset" },
			{ emMSGDataULONGLONG, L"Buffer" },
			{ emMSGDataULONG, L"ReturnLength" },
		};
		static MSGInfo info = {
			emMSGFilePostRead,
			L"FilePostRead",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileWrite
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldWriteLength,
		emFieldOffset,
		emFieldBuffer,
		emFieldData,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"WriteLength" },
			{ emMSGDataULONGLONG, L"Offset" },
			{ emMSGDataULONGLONG, L"Buffer" },
			{ emMSGDataBinary, L"Data" },
		};
		static MSGInfo info = {
			emMSGFileWrite,
			L"FileWrite",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostWrite
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldWriteLength,
		emFieldOffset,
		emFieldBuffer,
		emFieldData,
		emFieldReturnLength,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"WriteLength" },
			{ emMSGDataULONGLONG, L"Offset" },
			{ emMSGDataULONGLONG, L"Buffer" },
			{ emMSGDataBinary, L"Data" },
			{ emMSGDataULONG, L"ReturnLength" },
		};
		static MSGInfo info = {
			emMSGFilePostWrite,
			L"FilePostWrite",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileCreateHardLink
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldLinkPath,
		emFieldReplaceIfExists,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataPath, L"LinkPath" },
			{ emMSGDataBool, L"ReplaceIfExists" },
		};
		static MSGInfo info = {
			emMSGFileCreateHardLink,
			L"FileCreateHardLink",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostCreateHardLink
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldLinkPath,
		emFieldReplaceIfExists,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataPath, L"LinkPath" },
			{ emMSGDataBool, L"ReplaceIfExists" },
		};
		static MSGInfo info = {
			emMSGFilePostCreateHardLink,
			L"FilePostCreateHardLink",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileRename
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldNewPath,
		emFieldReplaceIfExists,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataPath, L"NewPath" },
			{ emMSGDataBool, L"ReplaceIfExists" },
		};
		static MSGInfo info = {
			emMSGFileRename,
			L"FileRename",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostRename
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldNewPath,
		emFieldReplaceIfExists,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataPath, L"NewPath" },
			{ emMSGDataBool, L"ReplaceIfExists" },
		};
		static MSGInfo info = {
			emMSGFilePostRename,
			L"FilePostRename",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileDelete
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
		};
		static MSGInfo info = {
			emMSGFileDelete,
			L"FileDelete",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostDelete
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
		};
		static MSGInfo info = {
			emMSGFilePostDelete,
			L"FilePostDelete",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileSetSize
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldSize,
		emFieldSizeType,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONGLONG, L"Size" },
			{ emMSGDataULONG, L"SizeType" },
		};
		static MSGInfo info = {
			emMSGFileSetSize,
			L"FileSetSize",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostSetSize
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldSize,
		emFieldSizeType,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONGLONG, L"Size" },
			{ emMSGDataULONG, L"SizeType" },
		};
		static MSGInfo info = {
			emMSGFilePostSetSize,
			L"FilePostSetSize",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileSetBasicInfo
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldCreationTime,
		emFieldLastAccessTime,
		emFieldLastWriteTime,
		emFieldChangeTime,
		emFieldFileAttributes,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataTime, L"CreationTime" },
			{ emMSGDataTime, L"LastAccessTime" },
			{ emMSGDataTime, L"LastWriteTime" },
			{ emMSGDataTime, L"ChangeTime" },
			{ emMSGDataFileAttributes, L"FileAttributes" },
		};
		static MSGInfo info = {
			emMSGFileSetBasicInfo,
			L"FileSetBasicInfo",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostSetBasicInfo
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldCreationTime,
		emFieldLastAccessTime,
		emFieldLastWriteTime,
		emFieldChangeTime,
		emFieldFileAttributes,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataTime, L"CreationTime" },
			{ emMSGDataTime, L"LastAccessTime" },
			{ emMSGDataTime, L"LastWriteTime" },
			{ emMSGDataTime, L"ChangeTime" },
			{ emMSGDataFileAttributes, L"FileAttributes" },
		};
		static MSGInfo info = {
			emMSGFilePostSetBasicInfo,
			L"FilePostSetBasicInfo",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FileFindFile
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldFindName,
		emFieldRestartScan,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataPath, L"FindName" },
			{ emMSGDataBool, L"RestartScan" },
		};
		static MSGInfo info = {
			emMSGFileFindFile,
			L"FileFindFile",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct FilePostFindFile
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldFindName,
		emFieldRestartScan,
		emFieldFileName,
		emFieldCreationTime,
		emFieldLastAccessTime,
		emFieldLastWriteTime,
		emFieldChangeTime,
		emFieldFileSize,
		emFieldFileAttributes,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataPath, L"FindName" },
			{ emMSGDataBool, L"RestartScan" },
			{ emMSGDataPath, L"FileName" },
			{ emMSGDataTime, L"CreationTime" },
			{ emMSGDataTime, L"LastAccessTime" },
			{ emMSGDataTime, L"LastWriteTime" },
			{ emMSGDataTime, L"ChangeTime" },
			{ emMSGDataULONGLONG, L"FileSize" },
			{ emMSGDataFileAttributes, L"FileAttributes" },
		};
		static MSGInfo info = {
			emMSGFilePostFindFile,
			L"FilePostFindFile",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegCreateKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldOptions,
		emFieldDesiredAccess,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataRegOptions, L"Options" },
			{ emMSGDataRegAccess, L"DesiredAccess" },
		};
		static MSGInfo info = {
			emMSGRegCreateKey,
			L"RegCreateKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegPostCreateKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldOptions,
		emFieldDesiredAccess,
		emFieldDisposition,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataRegOptions, L"Options" },
			{ emMSGDataRegAccess, L"DesiredAccess" },
			{ emMSGDataULONG, L"Disposition" },
		};
		static MSGInfo info = {
			emMSGRegPostCreateKey,
			L"RegPostCreateKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegOpenKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldOptions,
		emFieldDesiredAccess,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataRegOptions, L"Options" },
			{ emMSGDataRegAccess, L"DesiredAccess" },
		};
		static MSGInfo info = {
			emMSGRegOpenKey,
			L"RegOpenKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegPostOpenKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldOptions,
		emFieldDesiredAccess,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataRegOptions, L"Options" },
			{ emMSGDataRegAccess, L"DesiredAccess" },
		};
		static MSGInfo info = {
			emMSGRegPostOpenKey,
			L"RegPostOpenKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegDeleteKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
		};
		static MSGInfo info = {
			emMSGRegDeleteKey,
			L"RegDeleteKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegPostDeleteKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
		};
		static MSGInfo info = {
			emMSGRegPostDeleteKey,
			L"RegPostDeleteKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegRenameKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldNewName,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"NewName" },
		};
		static MSGInfo info = {
			emMSGRegRenameKey,
			L"RegRenameKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegPostRenameKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldNewName,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"NewName" },
		};
		static MSGInfo info = {
			emMSGRegPostRenameKey,
			L"RegPostRenameKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegEnumKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldIndex,
		emFieldInformationClass,
		emFieldInformationLength,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"Index" },
			{ emMSGDataULONG, L"InformationClass" },
			{ emMSGDataULONG, L"InformationLength" },
		};
		static MSGInfo info = {
			emMSGRegEnumKey,
			L"RegEnumKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegPostEnumKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldIndex,
		emFieldInformationClass,
		emFieldInformationLength,
		emFieldResultLength,
		emFieldInformation,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataULONG, L"Index" },
			{ emMSGDataULONG, L"InformationClass" },
			{ emMSGDataULONG, L"InformationLength" },
			{ emMSGDataULONG, L"ResultLength" },
			{ emMSGDataBinary, L"Information" },
		};
		static MSGInfo info = {
			emMSGRegPostEnumKey,
			L"RegPostEnumKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegLoadKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldFilePath,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"FilePath" },
		};
		static MSGInfo info = {
			emMSGRegLoadKey,
			L"RegLoadKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegPostLoadKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldFilePath,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"FilePath" },
		};
		static MSGInfo info = {
			emMSGRegPostLoadKey,
			L"RegPostLoadKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegReplaceKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldOldFilePath,
		emFieldNewFilePath,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"OldFilePath" },
			{ emMSGDataString, L"NewFilePath" },
		};
		static MSGInfo info = {
			emMSGRegReplaceKey,
			L"RegReplaceKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegPostReplaceKey
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldOldFilePath,
		emFieldNewFilePath,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"OldFilePath" },
			{ emMSGDataString, L"NewFilePath" },
		};
		static MSGInfo info = {
			emMSGRegPostReplaceKey,
			L"RegPostReplaceKey",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegDeleteValue
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldValueName,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"ValueName" },
		};
		static MSGInfo info = {
			emMSGRegDeleteValue,
			L"RegDeleteValue",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegPostDeleteValue
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldValueName,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"ValueName" },
		};
		static MSGInfo info = {
			emMSGRegPostDeleteValue,
			L"RegPostDeleteValue",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegSetValue
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldValueName,
		emFieldDataType,
		emFieldData,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"ValueName" },
			{ emMSGDataRegType, L"DataType" },
			{ emMSGDataBinary, L"Data" },
		};
		static MSGInfo info = {
			emMSGRegSetValue,
			L"RegSetValue",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegPostSetValue
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldValueName,
		emFieldDataType,
		emFieldData,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"ValueName" },
			{ emMSGDataRegType, L"DataType" },
			{ emMSGDataBinary, L"Data" },
		};
		static MSGInfo info = {
			emMSGRegPostSetValue,
			L"RegPostSetValue",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegQueryValue
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldValueName,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"ValueName" },
		};
		static MSGInfo info = {
			emMSGRegQueryValue,
			L"RegQueryValue",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct RegPostQueryValue
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldValueName,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataPath, L"Path" },
			{ emMSGDataString, L"ValueName" },
		};
		static MSGInfo info = {
			emMSGRegPostQueryValue,
			L"RegPostQueryValue",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketCreate
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
		};
		static MSGInfo info = {
			emMSGSocketCreate,
			L"SocketCreate",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketControl
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldCode,
		emFieldInputLength,
		emFieldOutputLength,
		emFieldInputData,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataULONG, L"Code" },
			{ emMSGDataULONG, L"InputLength" },
			{ emMSGDataULONG, L"OutputLength" },
			{ emMSGDataBinary, L"InputData" },
		};
		static MSGInfo info = {
			emMSGSocketControl,
			L"SocketControl",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketPostControl
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldCode,
		emFieldInputLength,
		emFieldOutputLength,
		emFieldInputData,
		emFieldOutputData,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataULONG, L"Code" },
			{ emMSGDataULONG, L"InputLength" },
			{ emMSGDataULONG, L"OutputLength" },
			{ emMSGDataBinary, L"InputData" },
			{ emMSGDataBinary, L"OutputData" },
		};
		static MSGInfo info = {
			emMSGSocketPostControl,
			L"SocketPostControl",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketConnect
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
		emFieldSuperConnect,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
			{ emMSGDataBool, L"SuperConnect" },
		};
		static MSGInfo info = {
			emMSGSocketConnect,
			L"SocketConnect",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketPostConnect
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
		emFieldSuperConnect,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
			{ emMSGDataBool, L"SuperConnect" },
		};
		static MSGInfo info = {
			emMSGSocketPostConnect,
			L"SocketPostConnect",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketSend
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
		emFieldDataLength,
		emFieldData,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
			{ emMSGDataULONG, L"DataLength" },
			{ emMSGDataBinary, L"Data" },
		};
		static MSGInfo info = {
			emMSGSocketSend,
			L"SocketSend",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketRecv
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
		};
		static MSGInfo info = {
			emMSGSocketRecv,
			L"SocketRecv",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketPostRecv
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
		emFieldDataLength,
		emFieldData,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
			{ emMSGDataULONG, L"DataLength" },
			{ emMSGDataBinary, L"Data" },
		};
		static MSGInfo info = {
			emMSGSocketPostRecv,
			L"SocketPostRecv",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketSendTo
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
		emFieldDataLength,
		emFieldData,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
			{ emMSGDataULONG, L"DataLength" },
			{ emMSGDataBinary, L"Data" },
		};
		static MSGInfo info = {
			emMSGSocketSendTo,
			L"SocketSendTo",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketRecvFrom
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
		};
		static MSGInfo info = {
			emMSGSocketRecvFrom,
			L"SocketRecvFrom",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketPostRecvFrom
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
		emFieldDataLength,
		emFieldData,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
			{ emMSGDataULONG, L"DataLength" },
			{ emMSGDataBinary, L"Data" },
		};
		static MSGInfo info = {
			emMSGSocketPostRecvFrom,
			L"SocketPostRecvFrom",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketListen
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
		};
		static MSGInfo info = {
			emMSGSocketListen,
			L"SocketListen",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketPostListen
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
		};
		static MSGInfo info = {
			emMSGSocketPostListen,
			L"SocketPostListen",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketAccept
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
		};
		static MSGInfo info = {
			emMSGSocketAccept,
			L"SocketAccept",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct SocketPostAccept
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldSocketObject,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataULONGLONG, L"SocketObject" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
		};
		static MSGInfo info = {
			emMSGSocketPostAccept,
			L"SocketPostAccept",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct WFPTcpConnect
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
		};
		static MSGInfo info = {
			emMSGWFPTcpConnect,
			L"WFPTcpConnect",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct WFPUdpConnect
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldIP,
		emFieldPort,
		emFieldLocalIP,
		emFieldLocalPort,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataSocketIP, L"LocalIP" },
			{ emMSGDataSocketPort, L"LocalPort" },
		};
		static MSGInfo info = {
			emMSGWFPUdpConnect,
			L"WFPUdpConnect",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};

struct HTTPRequest
{
public:
	enum {
		emFieldCallstack,
		emFieldCurrentProcessCreateTime,
		emFieldCurrentProcessName,
		emFieldCurrentProcessPath,
		emFieldCurrentProcessCommandline,
		emFieldPath,
		emFieldIP,
		emFieldPort,
		emFieldHost,
		emFieldUri,
		emFieldHeader,
		emFieldData,
		emFieldStatus,
		emFieldResponseHeader,
		emFieldResponseData,
	};

	static const MSGInfo& GetMSGInfo()
	{
		static MSGField fileds[] = {
			{ emMSGDataBinary, L"Callback" },
			{ emMSGDataULONGLONG, L"CurrentProcessCreateTime" },
			{ emMSGDataString, L"CurrentProcessName" },
			{ emMSGDataPath, L"CurrentProcessPath" },
			{ emMSGDataString, L"CurrentProcessCommandline" },
			{ emMSGDataString, L"Path" },
			{ emMSGDataSocketIP, L"IP" },
			{ emMSGDataSocketPort, L"Port" },
			{ emMSGDataString, L"Host" },
			{ emMSGDataString, L"Uri" },
			{ emMSGDataString, L"Header" },
			{ emMSGDataBinary, L"Data" },
			{ emMSGDataULONG, L"Status" },
			{ emMSGDataString, L"ResponseHeader" },
			{ emMSGDataBinary, L"ResponseData" },
		};
		static MSGInfo info = {
			emMSGHTTPRequest,
			L"HTTPRequest",
			_countof(fileds),
			fileds,
		};
		return info;
	}
};


inline const std::map<ULONG, MSGInfo>& GetMSGInfoTable()
{
	static std::map<ULONG, MSGInfo> table = {
		{ emMSGProcessCreate, ProcessCreate::GetMSGInfo() },
		{ emMSGProcessExit, ProcessExit::GetMSGInfo() },
		{ emMSGProcessOpen, ProcessOpen::GetMSGInfo() },
		{ emMSGThreadCreate, ThreadCreate::GetMSGInfo() },
		{ emMSGThreadExit, ThreadExit::GetMSGInfo() },
		{ emMSGThreadOpen, ThreadOpen::GetMSGInfo() },
		{ emMSGImageLoad, ImageLoad::GetMSGInfo() },
		{ emMSGProcessStart, ProcessStart::GetMSGInfo() },
		{ emMSGThreadStart, ThreadStart::GetMSGInfo() },
		{ emMSGFileCreate, FileCreate::GetMSGInfo() },
		{ emMSGFilePostCreate, FilePostCreate::GetMSGInfo() },
		{ emMSGFileQueryOpen, FileQueryOpen::GetMSGInfo() },
		{ emMSGFilePostQueryOpen, FilePostQueryOpen::GetMSGInfo() },
		{ emMSGFileCleanup, FileCleanup::GetMSGInfo() },
		{ emMSGFileCreateSection, FileCreateSection::GetMSGInfo() },
		{ emMSGFilePostCreateSection, FilePostCreateSection::GetMSGInfo() },
		{ emMSGFileRead, FileRead::GetMSGInfo() },
		{ emMSGFilePostRead, FilePostRead::GetMSGInfo() },
		{ emMSGFileWrite, FileWrite::GetMSGInfo() },
		{ emMSGFilePostWrite, FilePostWrite::GetMSGInfo() },
		{ emMSGFileCreateHardLink, FileCreateHardLink::GetMSGInfo() },
		{ emMSGFilePostCreateHardLink, FilePostCreateHardLink::GetMSGInfo() },
		{ emMSGFileRename, FileRename::GetMSGInfo() },
		{ emMSGFilePostRename, FilePostRename::GetMSGInfo() },
		{ emMSGFileDelete, FileDelete::GetMSGInfo() },
		{ emMSGFilePostDelete, FilePostDelete::GetMSGInfo() },
		{ emMSGFileSetSize, FileSetSize::GetMSGInfo() },
		{ emMSGFilePostSetSize, FilePostSetSize::GetMSGInfo() },
		{ emMSGFileSetBasicInfo, FileSetBasicInfo::GetMSGInfo() },
		{ emMSGFilePostSetBasicInfo, FilePostSetBasicInfo::GetMSGInfo() },
		{ emMSGFileFindFile, FileFindFile::GetMSGInfo() },
		{ emMSGFilePostFindFile, FilePostFindFile::GetMSGInfo() },
		{ emMSGRegCreateKey, RegCreateKey::GetMSGInfo() },
		{ emMSGRegPostCreateKey, RegPostCreateKey::GetMSGInfo() },
		{ emMSGRegOpenKey, RegOpenKey::GetMSGInfo() },
		{ emMSGRegPostOpenKey, RegPostOpenKey::GetMSGInfo() },
		{ emMSGRegDeleteKey, RegDeleteKey::GetMSGInfo() },
		{ emMSGRegPostDeleteKey, RegPostDeleteKey::GetMSGInfo() },
		{ emMSGRegRenameKey, RegRenameKey::GetMSGInfo() },
		{ emMSGRegPostRenameKey, RegPostRenameKey::GetMSGInfo() },
		{ emMSGRegEnumKey, RegEnumKey::GetMSGInfo() },
		{ emMSGRegPostEnumKey, RegPostEnumKey::GetMSGInfo() },
		{ emMSGRegLoadKey, RegLoadKey::GetMSGInfo() },
		{ emMSGRegPostLoadKey, RegPostLoadKey::GetMSGInfo() },
		{ emMSGRegReplaceKey, RegReplaceKey::GetMSGInfo() },
		{ emMSGRegPostReplaceKey, RegPostReplaceKey::GetMSGInfo() },
		{ emMSGRegDeleteValue, RegDeleteValue::GetMSGInfo() },
		{ emMSGRegPostDeleteValue, RegPostDeleteValue::GetMSGInfo() },
		{ emMSGRegSetValue, RegSetValue::GetMSGInfo() },
		{ emMSGRegPostSetValue, RegPostSetValue::GetMSGInfo() },
		{ emMSGRegQueryValue, RegQueryValue::GetMSGInfo() },
		{ emMSGRegPostQueryValue, RegPostQueryValue::GetMSGInfo() },
		{ emMSGSocketCreate, SocketCreate::GetMSGInfo() },
		{ emMSGSocketControl, SocketControl::GetMSGInfo() },
		{ emMSGSocketPostControl, SocketPostControl::GetMSGInfo() },
		{ emMSGSocketConnect, SocketConnect::GetMSGInfo() },
		{ emMSGSocketPostConnect, SocketPostConnect::GetMSGInfo() },
		{ emMSGSocketSend, SocketSend::GetMSGInfo() },
		{ emMSGSocketRecv, SocketRecv::GetMSGInfo() },
		{ emMSGSocketPostRecv, SocketPostRecv::GetMSGInfo() },
		{ emMSGSocketSendTo, SocketSendTo::GetMSGInfo() },
		{ emMSGSocketRecvFrom, SocketRecvFrom::GetMSGInfo() },
		{ emMSGSocketPostRecvFrom, SocketPostRecvFrom::GetMSGInfo() },
		{ emMSGSocketListen, SocketListen::GetMSGInfo() },
		{ emMSGSocketPostListen, SocketPostListen::GetMSGInfo() },
		{ emMSGSocketAccept, SocketAccept::GetMSGInfo() },
		{ emMSGSocketPostAccept, SocketPostAccept::GetMSGInfo() },
		{ emMSGWFPTcpConnect, WFPTcpConnect::GetMSGInfo() },
		{ emMSGWFPUdpConnect, WFPUdpConnect::GetMSGInfo() },
		{ emMSGHTTPRequest, HTTPRequest::GetMSGInfo() },
	};
	return table;
}

} // namespace proto
//******************************************************************************
inline const proto::MSGInfo& GetMSGInfo(ULONG Type)
{
	static proto::MSGInfo empty_info = { 0, L"", 0, NULL };
	static auto infos = proto::GetMSGInfoTable();

	auto it = infos.find(Type);

	if (it == infos.end())
		return empty_info;

	return it->second;
}
//******************************************************************************
inline const proto::MSGInfo& GetMSGInfo(const char* TypeName)
{
	static proto::MSGInfo empty_info = { 0, L"", 0, NULL };
	static auto infos = proto::GetMSGInfoTable();

	if (!TypeName)
		return empty_info;

	CString name = CA2T(TypeName);

	for (auto& it : infos) {
		if (0 == _wcsicmp(it.second.Name, name))
			return it.second;
	}

	return empty_info;
}
//******************************************************************************
