export const mode: string;
export namespace entry {
    const app: string;
}
export namespace experiments {
    const outputModule: boolean;
}
export namespace module {
    const rules: {
        test: RegExp;
        use: string;
        exclude: RegExp;
    }[];
}
export namespace resolve {
    const extensions: string[];
}
export namespace output {
    const filename: string;
    const path: string;
    namespace library {
        const type: string;
    }
}
