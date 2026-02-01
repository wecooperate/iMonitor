import { MessageColumn, IMessageColumn, IMessage, MessageType, MessageMatcher, IMessageMatcher, MessageColumnAlign, Icon } from '@wecooperate/imonitor';
import * as path from 'path';

@MessageColumn("TypeScript.FileExt")
class FileExtColumn implements IMessageColumn {
    align = MessageColumnAlign.Right;

    GetString(msg: IMessage): string {
        if (msg.Type > MessageType.RegCreateKey) {
            return "";
        }
        return path.extname(msg.Path);
    }
    GetTextColor(msg: IMessage): number {
        return 0x0000FF;
    }
    GetBackgroundColor(msg: IMessage): number {
        return 0x554444;
    }
    GetIcon(msg: IMessage): Icon {
        return msg.Process.Icon;
    }
}

@MessageMatcher("TypeScript.FileExt.PE")
class FileExtMatcher implements IMessageMatcher {
    IsMatch(msg: IMessage): boolean {
        if (msg.Type > MessageType.RegCreateKey) {
            return false;
        }
        let ext = path.extname(msg.Path).toLowerCase();
        return ext === '.exe' || ext === ".dll" || ext === ".sys";
    }
}
