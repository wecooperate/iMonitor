export declare interface Icon {
}
export declare interface IMessageProcessInternal {
    GetProcessId(): number;
    GetParentProcessId(): number;
    GetProcessPath(): string;
    GetProcessName(): string;
    GetCommandline(): string;
    GetIcon(): Icon;
    GetCreateTime(): number;
    GetExitTime(): number;
    GetVersionString(type: string): string;
}
export interface IMessageProcess extends IMessageProcessInternal {
    get ProcessId(): number;
    get ParentProcessId(): number;
    get ProcessPath(): string;
    get ProcessName(): string;
    get Commandline(): string;
    get Icon(): Icon;
    get CreateTime(): number;
    get ExitTime(): number;
}
export declare class MessageProcess implements IMessageProcess {
    internal: IMessageProcessInternal;
    constructor(internal: IMessageProcessInternal);
    GetProcessId(): number;
    GetParentProcessId(): number;
    GetProcessPath(): string;
    GetProcessName(): string;
    GetCommandline(): string;
    GetIcon(): Icon;
    GetCreateTime(): number;
    GetExitTime(): number;
    GetVersionString(type: string): string;
    get ProcessId(): number;
    get ParentProcessId(): number;
    get ProcessPath(): string;
    get ProcessName(): string;
    get Commandline(): string;
    get Icon(): Icon;
    get CreateTime(): number;
    get ExitTime(): number;
}
