import { libfren } from "./libfren.ts";
import { cstring, u32, u8 } from "./typeguard.ts";

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