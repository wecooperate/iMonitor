import { RegisterMessageColumn, RegisterMessageMatcher } from '@wecooperate/imonitor';
import * as path from 'path';

RegisterMessageColumn("JavaScript.FileExt", class FileExtColumn {
    constructor() {
        this.align = 2 /* MessageColumnAlign.Right */;
    }
    GetString(msg) {
        if (msg.Type > 301 /* MessageType.RegCreateKey */) {
            return "";
        }
        return path.extname(msg.Path);
    }
    GetTextColor(msg) {
        return 0x0000FF;
    }
    GetBackgroundColor(msg) {
        return 0x554444;
    }
    GetIcon(msg) {
        return msg.Process.Icon;
    }
});

RegisterMessageMatcher("JavaScript.FileExt.PE",  class FileExtMatcher {
    IsMatch(msg) {
        if (msg.Type > 301 /* MessageType.RegCreateKey */) {
            return false;
        }
        let ext = path.extname(msg.Path).toLowerCase();
        return ext === '.exe' || ext === ".dll" || ext === ".sys";
    }
});
