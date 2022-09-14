//******************************************************************************
/*++
    FileName:        iMonitor.h
    Description:

--*/
//******************************************************************************
#ifndef __iMonitor_H__
#define __iMonitor_H__
//******************************************************************************
// clang-format off
//******************************************************************************
#define MONITOR_VERSION                       2000
#define MONITOR_LICENSE_VERSION               1
#define MONITOR_MAX_BUFFER                    260
//******************************************************************************
#ifndef BIT
#define BIT(n) (1 << n)
#endif
//******************************************************************************
#ifndef FlagOn
#define FlagOn(n, x) ((n) & (x))
#endif
//******************************************************************************
enum emMSGType
{
    emMSGInternal                             = 0,
    emMSGProcess                              = 100,
    emMSGFile                                 = 200,
    emMSGRegistry                             = 300,
    emMSGSocket                               = 400,
    emMSGWFP                                  = 500,
    emMSGHTTP                                 = 600,
    emMSGMax                                  = 1000,
};
//******************************************************************************
#define MSG_GET_GROUP(type) (type / 100)

enum emMSGGroup {
	emMSGGroupInternal                        = 0,
	emMSGGroupProcess                         = 1,
	emMSGGroupFile                            = 2,
	emMSGGroupRegistry                        = 3,
	emMSGGroupSocket                          = 4,
	emMSGGroupWFP                             = 5,
    emMSGGroupHTTP                            = 6,
	emMSGGroupMax,
};
//******************************************************************************
enum emMSGTypeInternal
{
    emMSGInternalEnumProcess = emMSGInternal + 1,
    emMSGInternalEnumProtectRule,
    emMSGInternalEnd,
};
//******************************************************************************
enum emMSGTypeProcess
{
    emMSGProcessCreate = emMSGProcess + 1,
    emMSGProcessExit,
    emMSGProcessOpen,
    emMSGThreadCreate,
    emMSGThreadExit,
    emMSGThreadOpen,
    emMSGImageLoad,
    emMSGProcessStart,
    emMSGThreadStart,
};
//******************************************************************************
enum emMSGTypeFile
{
    emMSGFileCreate = emMSGFile + 1,
    emMSGFilePostCreate,
    emMSGFileQueryOpen,
    emMSGFilePostQueryOpen,
    emMSGFileCleanup,
    emMSGFilePostCleanup_nosupport,
    emMSGFileCreateSection,
    emMSGFilePostCreateSection,
    emMSGFileRead,
    emMSGFilePostRead,
    emMSGFileWrite,
    emMSGFilePostWrite,
    emMSGFileCreateHardLink,
    emMSGFilePostCreateHardLink,
    emMSGFileRename,
    emMSGFilePostRename,
    emMSGFileDelete,
    emMSGFilePostDelete,
    emMSGFileSetSize,
    emMSGFilePostSetSize,
    emMSGFileSetBasicInfo,
    emMSGFilePostSetBasicInfo,
    emMSGFileFindFile,
    emMSGFilePostFindFile,
};
//******************************************************************************
enum emMSGTypeRegistry
{
    emMSGRegCreateKey = emMSGRegistry + 1,
    emMSGRegPostCreateKey,
    emMSGRegOpenKey,
    emMSGRegPostOpenKey,
    emMSGRegDeleteKey,
    emMSGRegPostDeleteKey,
    emMSGRegRenameKey,
    emMSGRegPostRenameKey,
    emMSGRegEnumKey,
    emMSGRegPostEnumKey,
    emMSGRegLoadKey,
    emMSGRegPostLoadKey,
    emMSGRegReplaceKey,
    emMSGRegPostReplaceKey,
    emMSGRegDeleteValue,
    emMSGRegPostDeleteValue,
    emMSGRegSetValue,
    emMSGRegPostSetValue,
    emMSGRegQueryValue,
    emMSGRegPostQueryValue,
};
//******************************************************************************
enum emMSGTypeSocket
{
    emMSGSocketCreate = emMSGSocket + 1,
    emMSGSocketPostCreate_nosupport,
    emMSGSocketControl,
    emMSGSocketPostControl,
    emMSGSocketConnect,
    emMSGSocketPostConnect,
    emMSGSocketSend,
    emMSGSocketPostSend_nosupport,
    emMSGSocketRecv,
    emMSGSocketPostRecv,
    emMSGSocketSendTo,
    emMSGSocketPostSendTo,
    emMSGSocketRecvFrom,
    emMSGSocketPostRecvFrom,
    emMSGSocketListen,
    emMSGSocketPostListen,
    emMSGSocketAccept,
    emMSGSocketPostAccept,
};
//******************************************************************************
enum emMSGTypeWFP
{
    emMSGWFPTcpConnect = emMSGWFP + 1,
    emMSGWFPUdpConnect,
    emMSGWFPTcpAccept,
    emMSGWFPUdpAccept,
};
//******************************************************************************
enum emMSGTypeHTTP
{
    emMSGHTTPRequest = emMSGHTTP + 1,
    emMSGHTTPRequestEnd = emMSGHTTPRequest + 100,
};
//******************************************************************************
enum emMSGConfig
{
    emMSGConfigDefault                         = 0,
    emMSGConfigPost                            = BIT(0),
    emMSGConfigSend                            = BIT(1),
    emMSGConfigRule                            = BIT(2),
    emMSGConfigEnable                          = emMSGConfigPost | emMSGConfigSend | emMSGConfigRule,
    emMSGConfigIncludeKernelEvent              = BIT(10),
};
//******************************************************************************
enum emMSGAction
{
    emMSGActionDefault                         = 0,
    emMSGActionPass                            = 0,
    emMSGActionBlock                           = BIT(0),
    emMSGActionRedirect                        = BIT(1),
    emMSGActionGrantedAccess                   = BIT(2),
    emMSGActionTerminateProcess                = BIT(3),
    emMSGActionTerminateThread                 = BIT(4),
    emMSGActionLoadLibrary                     = BIT(5),
    emMSGActionRecord                          = BIT(20),
};
//******************************************************************************
enum emMSGDataType
{
    //
    //    基本类型
    //
    emMSGDataUnknown                           = 0,
    emMSGDataULONG                             = 0x10000,
    emMSGDataULONGLONG                         = 0x20000,
    emMSGDataString                            = 0x30000,
    emMSGDataPath                              = 0x40000,
    emMSGDataBinary                            = 0x50000,
    emMSGDataCallstack                         = 0x60000,

#define MSG_GET_BASE_TYPE(type)                (type & 0xFFFF0000)

    //
    //    扩展类型
    //
    emMSGDataBool = emMSGDataULONG + 1,
    emMSGDataHex,
    emMSGDataProcessAccess,
    emMSGDataThreadAccess,
    emMSGDataFileAccess,
    emMSGDataFileShareAccess,
    emMSGDataFileAttributes,
    emMSGDataFileDisposition,
    emMSGDataFileOptions,
    emMSGDataFilePageProtection,
    emMSGDataRegAccess,
    emMSGDataRegOptions,
    emMSGDataRegType,
    emMSGDataSocketIP,
    emMSGDataSocketPort,

    emMSGDataTime = emMSGDataULONGLONG + 1,
};
//******************************************************************************
enum emMSGField
{
    //
    //    基本字段
    //
    emMSGFieldInvalid = -1,
    emMSGFieldCallstack = 0,
    emMSGFieldCurrentProcessCreateTime,
    emMSGFieldCurrentProcessName,
    emMSGFieldCurrentProcessPath,
    emMSGFieldCurrentProcessCommandline,
    emMSGFieldPrivateBegin,
    emMSGFieldPath = emMSGFieldPrivateBegin,

    //
    // 基本字段默认配置
    //
    emMSGFieldDefault = ~BIT(emMSGFieldCallstack),
    emMSGFieldInternal = -1 << emMSGFieldPrivateBegin,

    //
    // 扩展字段
    //
    emMSGFieldExtension = 32,
    emMSGFieldType,
    emMSGFieldSeqId,
    emMSGFieldStatus,
    emMSGFieldCurrentProcessId,
    emMSGFieldCurrentThreadId,
    emMSGFieldTime,
    emMSGFieldDetail,
    emMSGFieldModifiable,
    emMSGFieldModified,

    //
    // 用户扩展字段
    //
    emMSGFieldCustomExtension = 1000,
};
//******************************************************************************
enum emMSGStatus
{
    emMSGStatusEnumBegin = 0x10000000,
    emMSGStatusEnumEnd,
};
//******************************************************************************
//
//    【驱动 --> 应用层】
//
//******************************************************************************
struct cxMSGHeader
{
    ULONG                Type;
    ULONG                Length;
    ULONG                Status;
    ULONG                Config;
    ULONG                SeqId;
    ULONG                Fields;
    ULONG                CurrentProcessId;
    ULONG                CurrentThreadId;
    ULONG                Modifiable:1;
    ULONG                Modified:1;
    ULONG                Reserved0:30;
    ULONG                Reserved1;
    ULONGLONG            Time;

    //
    //    后面跟着多个cxMSGDataHeader + Data
    //
};
//******************************************************************************
struct cxMSGDataHeader 
{
    ULONG                Type;
    ULONG                Length;
    
    template<typename T>
    T*      GetData     (void)                { return (T*)(this + 1); }
    PVOID   GetData     (void)                { return (PVOID)(this + 1); }

    cxMSGDataHeader* Next(void)               { return (cxMSGDataHeader*)((ULONG_PTR)this + Length); }
};
//******************************************************************************
struct cxMSGAction
{
    ULONG                Action;
    union {
        ULONG            Params[3];
        ULONG            Access;
        struct {
            ULONG        ProcessId;
            ULONG        IP;
            ULONG        Port;
        };
    };
};
//******************************************************************************
//
//    【用户层 --> 驱动层】
//
//******************************************************************************
struct cxMSGUserHeader 
{
    ULONG                Type;
    ULONG                LicenseVersion                = MONITOR_LICENSE_VERSION;
};
//******************************************************************************
template<ULONG TYPE, typename T = void>
struct cxMSGUser : public cxMSGUserHeader, public T
{
    static constexpr auto TYPE = TYPE;

    cxMSGUser            (void)                { Type = TYPE; }
    T*                   GetData(void)         { return this; }
};
//******************************************************************************
template<ULONG TYPE>
struct cxMSGUser<TYPE, void> : public cxMSGUserHeader
{
    static constexpr auto TYPE = TYPE;

    cxMSGUser            (void)                { Type = TYPE; }
};
//******************************************************************************
enum emMSGUser
{
    emMSGUserBase                              = 0,
    emMSGUserControl                           = 100,
    emMSGUserRule                              = 200,

    emMSGUserConnect                           = emMSGUserBase + 1,
};
//******************************************************************************
struct cxMSGUserConnect : public cxMSGUser<emMSGUserConnect> 
{
    ULONG                Version               = MONITOR_VERSION;
};
//******************************************************************************
enum
{
    emUserSetGlobalConfig = emMSGUserControl + 1,
    emUserGetGlobalConfig,
    emUserSetSessionConfig,
    emUserGetSessionConfig,
    emUserSetMSGConfig,
    emUserGetMSGConfig,
    emUserEnableProtect,
    emUserDisableProtect,
    emUserAddProtectRule,
    emUserRemoveProtectRule,
    emUserRemoveAllProtectRule,
    emUserEnumProtectRule,
};
//******************************************************************************
struct cxUserGlobalConfig
{
    union {
        struct {
            ULONG        SwitchIncludeVS:1;
            ULONG        SwitchIncludeSelf:1;
            ULONG        SwitchOther:30;
            ULONG        LogLevel;
            ULONG        MaxCallstack;
            ULONG        MaxBinaryData;
        };

        ULONG            Data[32];
    };

    cxUserGlobalConfig()
    {
        memset(Data, 0, sizeof(Data));

        MaxCallstack = 64;
        MaxBinaryData = 4096;
        SwitchIncludeVS = TRUE;
    }
};
//******************************************************************************
struct cxUserSessionConfig
{
    union {
		struct {
           ULONG        MSGTimeoutMS;
           ULONG        MSGTimeoutProtectCount;
           ULONG        MSGTimeoutProtectTimeMS;
           ULONG        MSGPostTimeoutMS;
           ULONG        FilterProcessOpenOnlyModifiable:1;
           ULONG        FilterThreadOpenOnlyModifiable:1;
           ULONG        FilterFileCreateOnlyModifiable:1;
           ULONG        FilterFileCloseOnlyModified:1;
           ULONG        FilterRegOpenOnlyModifiable:1;
           ULONG        FilterOther:27;
        };

        ULONG           Data[32];
	};

    cxUserSessionConfig()
    {
        memset(Data, 0, sizeof(Data));
        
        MSGTimeoutMS = 5000;
        MSGPostTimeoutMS = 50000;
    }
};
//******************************************************************************
struct cxUserMSGConfig
{
    ULONG        Config[emMSGMax];
    ULONG        Fields[emMSGMax];

    cxUserMSGConfig()
    {
        for (int i = 0; i < emMSGMax; i++)
            Config[i] = (ULONG)emMSGConfigDefault;

        for (int i = 0; i < emMSGMax; i++)
            Fields[i] = (ULONG)emMSGFieldDefault;
    }
};
//******************************************************************************
enum emUserProtectType
{
    emProtectTypeTrustProcess = BIT(0),
    emProtectTypeProcessPath = BIT(1),
    emProtectTypeFilePath = BIT(2),
    emProtectTypeRegPath = BIT(3),
};
//******************************************************************************
struct cxUserProtectItem
{
    ULONG        ProtectType;
    WCHAR        Path[MONITOR_MAX_BUFFER];
};
//******************************************************************************
typedef cxMSGUser<emUserSetGlobalConfig, cxUserGlobalConfig> cxMSGUserSetGlobalConfig;
typedef cxMSGUser<emUserGetGlobalConfig, cxUserGlobalConfig> cxMSGUserGetGlobalConfig;
typedef cxMSGUser<emUserSetSessionConfig, cxUserSessionConfig> cxMSGUserSetSessionConfig;
typedef cxMSGUser<emUserGetSessionConfig, cxUserSessionConfig> cxMSGUserGetSessionConfig;
typedef cxMSGUser<emUserSetMSGConfig, cxUserMSGConfig> cxMSGUserSetMSGConfig;
typedef cxMSGUser<emUserGetMSGConfig, cxUserMSGConfig> cxMSGUserGetMSGConfig;
typedef cxMSGUser<emUserEnableProtect> cxMSGUserEnableProtect;
typedef cxMSGUser<emUserDisableProtect> cxMSGUserDisableProtect;
typedef cxMSGUser<emUserAddProtectRule, cxUserProtectItem> cxMSGUserAddProtectRule;
typedef cxMSGUser<emUserRemoveProtectRule, cxUserProtectItem> cxMSGUserRemoveProtectRule;
typedef cxMSGUser<emUserRemoveAllProtectRule> cxMSGUserRemoveAllProtectRule;
typedef cxMSGUser<emUserEnumProtectRule> cxMSGUserEnumProtectRule;
//******************************************************************************
#endif
