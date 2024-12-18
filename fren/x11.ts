import type { context } from "./ctx.ts";
import { cstring, u32 } from "./typeguard.ts";

//loading library stuff
let libName;

switch (Deno.build.os) {
    case "linux":
        libName = "./libfren-x11-" + Deno.build.arch + ".so";
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
    "getWindow": {
        parameters: ["u32", "u32", "buffer"],
        result: "pointer",
    },
    "destroyWindow": {
        parameters: ["pointer"],
        result: "void",
    },
    "drawFrame": {
        parameters: ["pointer"],
        result: "void",
    },
    "getWindowctx":{
        parameters: ["pointer"],
        result:"pointer"
    },
    "getEvent": {
        parameters: ["pointer"],
        result: "pointer",
    },
    "getEventType": {
        parameters: ["pointer"],
        result: "u8",
    },
    "getEventKey": {
        parameters: ["pointer"],
        result: "u8",
    },
    "getEventX": {
        parameters: ["pointer"],
        result: "i32",
    },
    "getEventY": {
        parameters: ["pointer"],
        result: "i32",
    },
    "destroyEvent": {
        parameters: ["pointer"],
        result: "void",
    }
});

//window creation/event related stuff
export type Surface = Deno.PointerValue<unknown>;

export enum eventType{
    none = 0,
    MouseDown = 1,
    MouseUp = 2,
    MouseMove = 3,
    KeyDown = 4,
    KeyUp = 5,
    close = 6
};

export type Event = {
    type : eventType.none|eventType.close
}|{
    type : eventType.KeyDown|eventType.KeyUp
    key:string
}|{
    type : eventType.MouseDown|eventType.MouseUp|eventType.MouseMove
    x:number
    y:number
}

export function externUwU(){libfren.symbols.externUwU()}

export function getWindow(width:number,height:number,name:string=""){
    return libfren.symbols.getWindow(u32(width),u32(height),cstring(name)) as Surface
}

export function destroyWindow(window:Surface){
    libfren.symbols.destroyWindow(window);
}

export function drawFrame(window:Surface){
    libfren.symbols.drawFrame(window);
}

export function getWindowctx(window:Surface){
    return libfren.symbols.getWindowctx(window) as context;
}

export function getEvent(window:Surface){
    const rawEvent = libfren.symbols.getEvent(window);
    let event: Event;


    const type = libfren.symbols.getEventType(rawEvent) as eventType;

    switch (type){
        case eventType.none:
        case eventType.close: 
            event = {type:type};/* falls through */
            break;
        case eventType.MouseDown:
        case eventType.MouseUp:
        case eventType.MouseMove:{
            const x = libfren.symbols.getEventX(rawEvent) /* falls through */
            const y = libfren.symbols.getEventY(rawEvent)
            event = {type:type,x:x,y:y}
            break;}
        case eventType.KeyDown:
        case eventType.KeyUp:{
            const keyCode = libfren.symbols.getEventKey(rawEvent); /* falls through */
            const key = String.fromCharCode(keyCode);
            event = {type:type,key:key}
            break;}
    }

    //since event is a pointer we need to delete it
    libfren.symbols.destroyEvent(rawEvent);

    return event;
}