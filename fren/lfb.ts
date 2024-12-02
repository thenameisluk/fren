import type { context } from "./ctx.ts";
import { cstring, u32 } from "./typeguard.ts";

//loading library stuff
let libName;

switch (Deno.build.os) {
    case "linux":
        libName = "./libfren-lfb-" + Deno.build.arch + ".so";
        break;
    default:
        console.log("os not supported yet");
        Deno.exit(-1);
}
console.log("loading " + libName);

const libfren = Deno.dlopen(libName, {
    //debug
    "externUwU": {
        parameters: [],
        result: "void",
    },
    //window management
    "getFB": {
        parameters: [],
        result: "pointer",
    },
    "destroyFB": {
        parameters: ["pointer"],
        result: "void",
    },
    "drawFBFrame": {
        parameters: ["pointer"],
        result: "void",
    },
    "getFBctx":{
        parameters:["pointer"],
        result:"pointer"
    }
});

//window creation/event related stuff
export type fb = Deno.PointerValue<unknown>;

export function externUwU(){libfren.symbols.externUwU()}

export function getFB(){
    return libfren.symbols.getFB() as fb
}

export function destroyFB(window:fb){
    libfren.symbols.destroyFB(window);
}

export function drawFBFrame(window:fb){
    libfren.symbols.drawFBFrame(window);
}

export function getFBctx(framebuffer:fb){
    return libfren.symbols.getFBctx(framebuffer) as context;
}