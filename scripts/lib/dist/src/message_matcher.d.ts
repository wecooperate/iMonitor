import { IMessage, IMessageInternal } from "./message";
export declare interface IMessageMatcherInternal {
    GetName(): string;
    GetDescription(): string;
    IsMatch(msg: IMessageInternal): boolean;
}
export interface IMessageMatcher {
    description?: string;
    IsMatch(msg: IMessage): boolean;
}
declare global {
    interface iMonitor {
        RegisterMessageMatcher(matcher: IMessageMatcherInternal): boolean;
    }
}
export declare function MessageMatcher<T extends {
    new (...args: any[]): IMessageMatcher;
}>(name: string): (constructor: T) => void;
export declare function RegisterMessageMatcher<T extends {
    new (...args: any[]): IMessageMatcher;
}>(name: string, constructor: T): void;
