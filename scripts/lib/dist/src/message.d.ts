import { IMessageProcessInternal, MessageProcess } from "./message_process";
export declare const enum MessgaeGroup {
    Internal = 0,
    Process = 1,
    File = 2,
    Registry = 3,
    Socket = 4,
    WFP = 5,
    HTTP = 6,
    Max = 7
}
export declare const enum MessageType {
    ProcessCreate = 101,
    ProcessExit = 102,
    ProcessOpen = 103,
    ThreadCreate = 104,
    ThreadExit = 105,
    ThreadOpen = 106,
    ImageLoad = 107,
    ProcessStart = 108,
    ThreadStart = 109,
    FileCreate = 201,
    FilePostCreate = 202,
    FileQueryOpen = 203,
    FilePostQueryOpen = 204,
    FileCleanup = 205,
    FilePostCleanup_nosupport = 206,
    FileCreateSection = 207,
    FilePostCreateSection = 208,
    FileRead = 209,
    FilePostRead = 210,
    FileWrite = 211,
    FilePostWrite = 212,
    FileCreateHardLink = 213,
    FilePostCreateHardLink = 214,
    FileRename = 215,
    FilePostRename = 216,
    FileDelete = 217,
    FilePostDelete = 218,
    FileSetSize = 219,
    FilePostSetSize = 220,
    FileSetBasicInfo = 221,
    FilePostSetBasicInfo = 222,
    FileFindFile = 223,
    FilePostFindFile = 224,
    RegCreateKey = 301,
    RegPostCreateKey = 302,
    RegOpenKey = 303,
    RegPostOpenKey = 304,
    RegDeleteKey = 305,
    RegPostDeleteKey = 306,
    RegRenameKey = 307,
    RegPostRenameKey = 308,
    RegEnumKey = 309,
    RegPostEnumKey = 310,
    RegLoadKey = 311,
    RegPostLoadKey = 312,
    RegReplaceKey = 313,
    RegPostReplaceKey = 314,
    RegDeleteValue = 315,
    RegPostDeleteValue = 316,
    RegSetValue = 317,
    RegPostSetValue = 318,
    RegQueryValue = 319,
    RegPostQueryValue = 320,
    SocketCreate = 401,
    SocketPostCreate_nosupport = 402,
    SocketControl = 403,
    SocketPostControl = 404,
    SocketConnect = 405,
    SocketPostConnect = 406,
    SocketSend = 407,
    SocketPostSend_nosupport = 408,
    SocketRecv = 409,
    SocketPostRecv = 410,
    SocketSendTo = 411,
    SocketPostSendTo = 412,
    SocketRecvFrom = 413,
    SocketPostRecvFrom = 414,
    SocketListen = 415,
    SocketPostListen = 416,
    SocketAccept = 417,
    SocketPostAccept = 418,
    WFPTcpConnect = 501,
    WFPUdpConnect = 502,
    WFPTcpAccept = 503,
    WFPUdpAccept = 504,
    HTTPRequest = 601,
    HTTPRequestEnd = 701
}
export declare const enum emMSGDataType {
    Number = 0,
    String = 1,
    Binary = 2
}
export declare interface IMessageInternal {
    GetType(): number;
    GetIndex(): number;
    GetSeqId(): number;
    GetStatus(): number;
    GetCurrentProcessId(): number;
    GetCurrentThreadId(): number;
    GetTime(): number;
    GetGroupType(): number;
    GetPath(): string;
    GetTypeName(): string;
    GetFieldCount(): number;
    GetFieldType(index: number): emMSGDataType;
    GetFieldName(index: number): string;
    GetFieldIndex(name: string): number;
    GetNumber(index: number): number;
    GetString(index: number): string;
    GetBinary(index: number): ArrayBuffer;
    GetProcess(): IMessageProcessInternal;
}
export interface IMessage extends IMessageInternal {
    get Type(): number;
    get Index(): number;
    get SeqId(): number;
    get Status(): number;
    get CurrentProcessId(): number;
    get CurrentThreadId(): number;
    get Time(): number;
    get GroupType(): number;
    get Path(): string;
    get TypeName(): string;
    get FieldCount(): number;
    get Process(): MessageProcess;
}
export declare namespace Message {
    class MessageCommon implements IMessage {
        internal: IMessageInternal;
        constructor(internal?: IMessageInternal);
        GetType(): number;
        GetIndex(): number;
        GetSeqId(): number;
        GetStatus(): number;
        GetCurrentProcessId(): number;
        GetCurrentThreadId(): number;
        GetTime(): number;
        GetGroupType(): number;
        GetPath(): string;
        GetTypeName(): string;
        GetFieldCount(): number;
        GetFieldType(index: number): emMSGDataType;
        GetFieldName(index: number): string;
        GetFieldIndex(name: string): number;
        GetNumber(index: number): number;
        GetString(index: number): string;
        GetBinary(index: number): ArrayBuffer;
        GetProcess(): IMessageProcessInternal;
        GetFieldBool(index: number): boolean;
        GetFieldULONG(index: number): number;
        GetFieldProcessAccess(index: number): number;
        GetFieldThreadAccess(index: number): number;
        GetFieldFileAccess(index: number): number;
        GetFieldFileShareAccess(index: number): number;
        GetFieldFileAttributes(index: number): number;
        GetFieldFileDisposition(index: number): number;
        GetFieldFileOptions(index: number): number;
        GetFieldFilePageProtection(index: number): number;
        GetFieldRegAccess(index: number): number;
        GetFieldRegOptions(index: number): number;
        GetFieldRegType(index: number): number;
        GetFieldSocketIP(index: number): number;
        GetFieldSocketPort(index: number): number;
        GetFieldHex(index: number): number;
        GetFieldULONGLONG(index: number): number;
        GetFieldTime(index: number): number;
        GetFieldString(index: number): string;
        GetFieldPath(index: number): string;
        GetFieldBinary(index: number): ArrayBuffer;
        GetFieldCallstack(index: number): ArrayBuffer;
        get Type(): number;
        get Index(): number;
        get SeqId(): number;
        get Status(): number;
        get CurrentProcessId(): number;
        get CurrentThreadId(): number;
        get Time(): number;
        get GroupType(): number;
        get Path(): string;
        get TypeName(): string;
        get FieldCount(): number;
        get Process(): MessageProcess;
    }
    const enum ProcessCreateField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ProcessId = 6,
        Commandline = 7,
        CreateTime = 8,
        ParentPath = 9,
        ParentProcessId = 10,
        ParentCommandline = 11,
        ParentCreateTime = 12
    }
    class ProcessCreate extends MessageCommon {
        get Path(): string;
        get ProcessId(): number;
        get Commandline(): string;
        get CreateTime(): number;
        get ParentPath(): string;
        get ParentProcessId(): number;
        get ParentCommandline(): string;
        get ParentCreateTime(): number;
    }
    const enum ProcessExitField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ProcessId = 6
    }
    class ProcessExit extends MessageCommon {
        get Path(): string;
        get ProcessId(): number;
    }
    const enum ProcessOpenField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ProcessId = 6,
        ParentProcessId = 7,
        DesiredAccess = 8,
        Duplicate = 9
    }
    class ProcessOpen extends MessageCommon {
        get Path(): string;
        get ProcessId(): number;
        get ParentProcessId(): number;
        get DesiredAccess(): number;
        get Duplicate(): boolean;
    }
    const enum ThreadCreateField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ProcessId = 6,
        ThreadId = 7,
        StartAddress = 8,
        RemoteThread = 9
    }
    class ThreadCreate extends MessageCommon {
        get Path(): string;
        get ProcessId(): number;
        get ThreadId(): number;
        get StartAddress(): number;
        get RemoteThread(): boolean;
    }
    const enum ThreadExitField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ProcessId = 6,
        ThreadId = 7
    }
    class ThreadExit extends MessageCommon {
        get Path(): string;
        get ProcessId(): number;
        get ThreadId(): number;
    }
    const enum ThreadOpenField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ProcessId = 6,
        ParentProcessId = 7,
        DesiredAccess = 8,
        Duplicate = 9,
        ThreadId = 10
    }
    class ThreadOpen extends MessageCommon {
        get Path(): string;
        get ProcessId(): number;
        get ParentProcessId(): number;
        get DesiredAccess(): number;
        get Duplicate(): boolean;
        get ThreadId(): number;
    }
    const enum ImageLoadField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ProcessId = 6,
        ImageBase = 7,
        ImageSize = 8,
        IsKernelImage = 9
    }
    class ImageLoad extends MessageCommon {
        get Path(): string;
        get ProcessId(): number;
        get ImageBase(): number;
        get ImageSize(): number;
        get IsKernelImage(): boolean;
    }
    const enum ProcessStartField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ProcessId = 6,
        Commandline = 7,
        CreateTime = 8,
        ParentPath = 9,
        ParentProcessId = 10,
        ParentCommandline = 11,
        ParentCreateTime = 12
    }
    class ProcessStart extends MessageCommon {
        get Path(): string;
        get ProcessId(): number;
        get Commandline(): string;
        get CreateTime(): number;
        get ParentPath(): string;
        get ParentProcessId(): number;
        get ParentCommandline(): string;
        get ParentCreateTime(): number;
    }
    const enum ThreadStartField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ProcessId = 6,
        ThreadId = 7,
        StartAddress = 8,
        RemoteThread = 9
    }
    class ThreadStart extends MessageCommon {
        get Path(): string;
        get ProcessId(): number;
        get ThreadId(): number;
        get StartAddress(): number;
        get RemoteThread(): boolean;
    }
    const enum FileCreateField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Attributes = 6,
        Access = 7,
        ShareAccess = 8,
        CreateDisposition = 9,
        CreateOptions = 10
    }
    class FileCreate extends MessageCommon {
        get Path(): string;
        get Attributes(): number;
        get Access(): number;
        get ShareAccess(): number;
        get CreateDisposition(): number;
        get CreateOptions(): number;
    }
    const enum FilePostCreateField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Attributes = 6,
        Access = 7,
        ShareAccess = 8,
        CreateDisposition = 9,
        CreateOptions = 10,
        Information = 11
    }
    class FilePostCreate extends MessageCommon {
        get Path(): string;
        get Attributes(): number;
        get Access(): number;
        get ShareAccess(): number;
        get CreateDisposition(): number;
        get CreateOptions(): number;
        get Information(): number;
    }
    const enum FileQueryOpenField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5
    }
    class FileQueryOpen extends MessageCommon {
        get Path(): string;
    }
    const enum FilePostQueryOpenField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        CreationTime = 6,
        LastAccessTime = 7,
        LastWriteTime = 8,
        ChangeTime = 9,
        FileSize = 10,
        FileAttributes = 11
    }
    class FilePostQueryOpen extends MessageCommon {
        get Path(): string;
        get CreationTime(): number;
        get LastAccessTime(): number;
        get LastWriteTime(): number;
        get ChangeTime(): number;
        get FileSize(): number;
        get FileAttributes(): number;
    }
    const enum FileCleanupField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Information = 6
    }
    class FileCleanup extends MessageCommon {
        get Path(): string;
        get Information(): number;
    }
    const enum FileCreateSectionField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        PageProtection = 6
    }
    class FileCreateSection extends MessageCommon {
        get Path(): string;
        get PageProtection(): number;
    }
    const enum FilePostCreateSectionField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        PageProtection = 6
    }
    class FilePostCreateSection extends MessageCommon {
        get Path(): string;
        get PageProtection(): number;
    }
    const enum FileReadField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ReadLength = 6,
        Offset = 7,
        Buffer = 8
    }
    class FileRead extends MessageCommon {
        get Path(): string;
        get ReadLength(): number;
        get Offset(): number;
        get Buffer(): number;
    }
    const enum FilePostReadField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ReadLength = 6,
        Offset = 7,
        Buffer = 8,
        ReturnLength = 9
    }
    class FilePostRead extends MessageCommon {
        get Path(): string;
        get ReadLength(): number;
        get Offset(): number;
        get Buffer(): number;
        get ReturnLength(): number;
    }
    const enum FileWriteField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        WriteLength = 6,
        Offset = 7,
        Buffer = 8,
        Data = 9
    }
    class FileWrite extends MessageCommon {
        get Path(): string;
        get WriteLength(): number;
        get Offset(): number;
        get Buffer(): number;
        get Data(): ArrayBuffer;
    }
    const enum FilePostWriteField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        WriteLength = 6,
        Offset = 7,
        Buffer = 8,
        Data = 9,
        ReturnLength = 10
    }
    class FilePostWrite extends MessageCommon {
        get Path(): string;
        get WriteLength(): number;
        get Offset(): number;
        get Buffer(): number;
        get Data(): ArrayBuffer;
        get ReturnLength(): number;
    }
    const enum FileCreateHardLinkField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        LinkPath = 6,
        ReplaceIfExists = 7
    }
    class FileCreateHardLink extends MessageCommon {
        get Path(): string;
        get LinkPath(): string;
        get ReplaceIfExists(): boolean;
    }
    const enum FilePostCreateHardLinkField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        LinkPath = 6,
        ReplaceIfExists = 7
    }
    class FilePostCreateHardLink extends MessageCommon {
        get Path(): string;
        get LinkPath(): string;
        get ReplaceIfExists(): boolean;
    }
    const enum FileRenameField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        NewPath = 6,
        ReplaceIfExists = 7
    }
    class FileRename extends MessageCommon {
        get Path(): string;
        get NewPath(): string;
        get ReplaceIfExists(): boolean;
    }
    const enum FilePostRenameField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        NewPath = 6,
        ReplaceIfExists = 7
    }
    class FilePostRename extends MessageCommon {
        get Path(): string;
        get NewPath(): string;
        get ReplaceIfExists(): boolean;
    }
    const enum FileDeleteField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5
    }
    class FileDelete extends MessageCommon {
        get Path(): string;
    }
    const enum FilePostDeleteField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5
    }
    class FilePostDelete extends MessageCommon {
        get Path(): string;
    }
    const enum FileSetSizeField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Size = 6,
        SizeType = 7
    }
    class FileSetSize extends MessageCommon {
        get Path(): string;
        get Size(): number;
        get SizeType(): number;
    }
    const enum FilePostSetSizeField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Size = 6,
        SizeType = 7
    }
    class FilePostSetSize extends MessageCommon {
        get Path(): string;
        get Size(): number;
        get SizeType(): number;
    }
    const enum FileSetBasicInfoField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        CreationTime = 6,
        LastAccessTime = 7,
        LastWriteTime = 8,
        ChangeTime = 9,
        FileAttributes = 10
    }
    class FileSetBasicInfo extends MessageCommon {
        get Path(): string;
        get CreationTime(): number;
        get LastAccessTime(): number;
        get LastWriteTime(): number;
        get ChangeTime(): number;
        get FileAttributes(): number;
    }
    const enum FilePostSetBasicInfoField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        CreationTime = 6,
        LastAccessTime = 7,
        LastWriteTime = 8,
        ChangeTime = 9,
        FileAttributes = 10
    }
    class FilePostSetBasicInfo extends MessageCommon {
        get Path(): string;
        get CreationTime(): number;
        get LastAccessTime(): number;
        get LastWriteTime(): number;
        get ChangeTime(): number;
        get FileAttributes(): number;
    }
    const enum FileFindFileField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        FindName = 6,
        RestartScan = 7
    }
    class FileFindFile extends MessageCommon {
        get Path(): string;
        get FindName(): string;
        get RestartScan(): boolean;
    }
    const enum FilePostFindFileField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        FindName = 6,
        RestartScan = 7,
        FileName = 8,
        CreationTime = 9,
        LastAccessTime = 10,
        LastWriteTime = 11,
        ChangeTime = 12,
        FileSize = 13,
        FileAttributes = 14
    }
    class FilePostFindFile extends MessageCommon {
        get Path(): string;
        get FindName(): string;
        get RestartScan(): boolean;
        get FileName(): string;
        get CreationTime(): number;
        get LastAccessTime(): number;
        get LastWriteTime(): number;
        get ChangeTime(): number;
        get FileSize(): number;
        get FileAttributes(): number;
    }
    const enum RegCreateKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Options = 6,
        DesiredAccess = 7
    }
    class RegCreateKey extends MessageCommon {
        get Path(): string;
        get Options(): number;
        get DesiredAccess(): number;
    }
    const enum RegPostCreateKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Options = 6,
        DesiredAccess = 7,
        Disposition = 8
    }
    class RegPostCreateKey extends MessageCommon {
        get Path(): string;
        get Options(): number;
        get DesiredAccess(): number;
        get Disposition(): number;
    }
    const enum RegOpenKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Options = 6,
        DesiredAccess = 7
    }
    class RegOpenKey extends MessageCommon {
        get Path(): string;
        get Options(): number;
        get DesiredAccess(): number;
    }
    const enum RegPostOpenKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Options = 6,
        DesiredAccess = 7
    }
    class RegPostOpenKey extends MessageCommon {
        get Path(): string;
        get Options(): number;
        get DesiredAccess(): number;
    }
    const enum RegDeleteKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5
    }
    class RegDeleteKey extends MessageCommon {
        get Path(): string;
    }
    const enum RegPostDeleteKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5
    }
    class RegPostDeleteKey extends MessageCommon {
        get Path(): string;
    }
    const enum RegRenameKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        NewName = 6
    }
    class RegRenameKey extends MessageCommon {
        get Path(): string;
        get NewName(): string;
    }
    const enum RegPostRenameKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        NewName = 6
    }
    class RegPostRenameKey extends MessageCommon {
        get Path(): string;
        get NewName(): string;
    }
    const enum RegEnumKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Index = 6,
        InformationClass = 7,
        InformationLength = 8
    }
    class RegEnumKey extends MessageCommon {
        get Path(): string;
        get Index(): number;
        get InformationClass(): number;
        get InformationLength(): number;
    }
    const enum RegPostEnumKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        Index = 6,
        InformationClass = 7,
        InformationLength = 8,
        ResultLength = 9,
        Information = 10
    }
    class RegPostEnumKey extends MessageCommon {
        get Path(): string;
        get Index(): number;
        get InformationClass(): number;
        get InformationLength(): number;
        get ResultLength(): number;
        get Information(): ArrayBuffer;
    }
    const enum RegLoadKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        FilePath = 6
    }
    class RegLoadKey extends MessageCommon {
        get Path(): string;
        get FilePath(): string;
    }
    const enum RegPostLoadKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        FilePath = 6
    }
    class RegPostLoadKey extends MessageCommon {
        get Path(): string;
        get FilePath(): string;
    }
    const enum RegReplaceKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        OldFilePath = 6,
        NewFilePath = 7
    }
    class RegReplaceKey extends MessageCommon {
        get Path(): string;
        get OldFilePath(): string;
        get NewFilePath(): string;
    }
    const enum RegPostReplaceKeyField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        OldFilePath = 6,
        NewFilePath = 7
    }
    class RegPostReplaceKey extends MessageCommon {
        get Path(): string;
        get OldFilePath(): string;
        get NewFilePath(): string;
    }
    const enum RegDeleteValueField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ValueName = 6
    }
    class RegDeleteValue extends MessageCommon {
        get Path(): string;
        get ValueName(): string;
    }
    const enum RegPostDeleteValueField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ValueName = 6
    }
    class RegPostDeleteValue extends MessageCommon {
        get Path(): string;
        get ValueName(): string;
    }
    const enum RegSetValueField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ValueName = 6,
        DataType = 7,
        Data = 8
    }
    class RegSetValue extends MessageCommon {
        get Path(): string;
        get ValueName(): string;
        get DataType(): number;
        get Data(): ArrayBuffer;
    }
    const enum RegPostSetValueField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ValueName = 6,
        DataType = 7,
        Data = 8
    }
    class RegPostSetValue extends MessageCommon {
        get Path(): string;
        get ValueName(): string;
        get DataType(): number;
        get Data(): ArrayBuffer;
    }
    const enum RegQueryValueField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ValueName = 6
    }
    class RegQueryValue extends MessageCommon {
        get Path(): string;
        get ValueName(): string;
    }
    const enum RegPostQueryValueField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        ValueName = 6
    }
    class RegPostQueryValue extends MessageCommon {
        get Path(): string;
        get ValueName(): string;
    }
    const enum SocketCreateField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5
    }
    class SocketCreate extends MessageCommon {
        get SocketObject(): number;
    }
    const enum SocketControlField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        Code = 6,
        InputLength = 7,
        OutputLength = 8,
        InputData = 9
    }
    class SocketControl extends MessageCommon {
        get SocketObject(): number;
        get Code(): number;
        get InputLength(): number;
        get OutputLength(): number;
        get InputData(): ArrayBuffer;
    }
    const enum SocketPostControlField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        Code = 6,
        InputLength = 7,
        OutputLength = 8,
        InputData = 9,
        OutputData = 10
    }
    class SocketPostControl extends MessageCommon {
        get SocketObject(): number;
        get Code(): number;
        get InputLength(): number;
        get OutputLength(): number;
        get InputData(): ArrayBuffer;
        get OutputData(): ArrayBuffer;
    }
    const enum SocketConnectField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7,
        LocalIP = 8,
        LocalPort = 9,
        SuperConnect = 10
    }
    class SocketConnect extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
        get SuperConnect(): boolean;
    }
    const enum SocketPostConnectField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7,
        LocalIP = 8,
        LocalPort = 9,
        SuperConnect = 10
    }
    class SocketPostConnect extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
        get SuperConnect(): boolean;
    }
    const enum SocketSendField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7,
        LocalIP = 8,
        LocalPort = 9,
        DataLength = 10,
        Data = 11
    }
    class SocketSend extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
        get DataLength(): number;
        get Data(): ArrayBuffer;
    }
    const enum SocketRecvField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7,
        LocalIP = 8,
        LocalPort = 9
    }
    class SocketRecv extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
    }
    const enum SocketPostRecvField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7,
        LocalIP = 8,
        LocalPort = 9,
        DataLength = 10,
        Data = 11
    }
    class SocketPostRecv extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
        get DataLength(): number;
        get Data(): ArrayBuffer;
    }
    const enum SocketSendToField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7,
        LocalIP = 8,
        LocalPort = 9,
        DataLength = 10,
        Data = 11
    }
    class SocketSendTo extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
        get DataLength(): number;
        get Data(): ArrayBuffer;
    }
    const enum SocketRecvFromField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7,
        LocalIP = 8,
        LocalPort = 9
    }
    class SocketRecvFrom extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
    }
    const enum SocketPostRecvFromField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7,
        LocalIP = 8,
        LocalPort = 9,
        DataLength = 10,
        Data = 11
    }
    class SocketPostRecvFrom extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
        get DataLength(): number;
        get Data(): ArrayBuffer;
    }
    const enum SocketListenField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7
    }
    class SocketListen extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
    }
    const enum SocketPostListenField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7
    }
    class SocketPostListen extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
    }
    const enum SocketAcceptField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7,
        LocalIP = 8,
        LocalPort = 9
    }
    class SocketAccept extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
    }
    const enum SocketPostAcceptField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        SocketObject = 5,
        IP = 6,
        Port = 7,
        LocalIP = 8,
        LocalPort = 9
    }
    class SocketPostAccept extends MessageCommon {
        get SocketObject(): number;
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
    }
    const enum WFPTcpConnectField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        IP = 5,
        Port = 6,
        LocalIP = 7,
        LocalPort = 8
    }
    class WFPTcpConnect extends MessageCommon {
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
    }
    const enum WFPUdpConnectField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        IP = 5,
        Port = 6,
        LocalIP = 7,
        LocalPort = 8
    }
    class WFPUdpConnect extends MessageCommon {
        get IP(): number;
        get Port(): number;
        get LocalIP(): number;
        get LocalPort(): number;
    }
    const enum HTTPRequestField {
        Callstack = 0,
        CurrentProcessCreateTime = 1,
        CurrentProcessName = 2,
        CurrentProcessPath = 3,
        CurrentProcessCommandline = 4,
        Path = 5,
        IP = 6,
        Port = 7,
        Host = 8,
        Uri = 9,
        Header = 10,
        Data = 11,
        Status = 12,
        ResponseHeader = 13,
        ResponseData = 14
    }
    class HTTPRequest extends MessageCommon {
        get Path(): string;
        get IP(): number;
        get Port(): number;
        get Host(): string;
        get Uri(): string;
        get Header(): string;
        get Data(): ArrayBuffer;
        get Status(): number;
        get ResponseHeader(): string;
        get ResponseData(): ArrayBuffer;
    }
    function Create(internal: IMessageInternal): MessageCommon;
}
