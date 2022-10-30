import { IMessage, IMessageInternal } from "./message";
import { Icon } from "./message_process";
export declare const enum MessageColumnAlign {
    Default = 0,
    Left = 1,
    Right = 2,
    Center = 4
}
export declare interface IMessageColumnInternal {
    GetName(): string;
    GetDescription(): string;
    GetString(msg: IMessageInternal): string;
    GetAlign?(): MessageColumnAlign;
    GetWidth?(): number;
    GetToolTips?(msg: IMessageInternal): string;
    GetTextColor?(msg: IMessageInternal): number;
    GetBackgroundColor?(msg: IMessageInternal): number;
    GetIcon?(msg: IMessageInternal): Icon;
}
export interface IMessageColumn {
    align?: MessageColumnAlign;
    width?: number;
    description?: string;
    GetString(msg: IMessage): string;
    GetToolTips?(msg: IMessage): string;
    GetTextColor?(msg: IMessage): number;
    GetBackgroundColor?(msg: IMessage): number;
    GetIcon?(msg: IMessage): Icon;
}
declare global {
    interface iMonitor {
        RegisterMessageColumn(column: IMessageColumnInternal): boolean;
    }
}
export declare function MessageColumn<T extends {
    new (...args: any[]): IMessageColumn;
}>(name: string): (constructor: T) => void;
export declare function RegisterMessageColumn<T extends {
    new (...args: any[]): IMessageColumn;
}>(name: string, constructor: T): void;
