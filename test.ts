const lib = Deno.dlopen("./libfren.so",{
    "externUwU":{
        parameters:[],
        result:"void",
    },
    "getWindow":{
        parameters:["u32","u32","buffer"],
        result: "pointer"
    },
    "destroyWindow":{
        parameters:["pointer"],
        result:"void"
    },
    "drawFrame":{
        parameters:["pointer"],
        result:"void"
    },
    "getEvent":{
        parameters:["pointer"],
        result:"pointer"
    },
    "getEventType":{
        parameters:["pointer"],
        result:"u8"
    },
    "getEventKey":{
        parameters:["pointer"],
        result:"u8"
    },
    "getEventX":{
        parameters:["pointer"],
        result:"u32"
    },
    "getEventY":{
        parameters:["pointer"],
        result:"u32"
    },
    "destroyEvent":{
        parameters:["pointer"],
        result:"void"
    }
})



type Window = Deno.PointerValue<unknown>;

enum eventType{
    none = 0,
    MouseDown = 1,
    MouseUp = 2,
    MouseMove = 3,
    KeyDown = 4,
    KeyUp = 5,
    close = 6
};

type Event = {
    type : eventType.none|eventType.close
}|{
    type : eventType.KeyDown|eventType.KeyUp
    key:string
}|{
    type : eventType.MouseDown|eventType.MouseUp|eventType.MouseMove
    x:number
    y:number
}

export function externUwU(){lib.symbols.externUwU()}

export function getWindow(width:number,height:number,name:string){
    return lib.symbols.getWindow(width,height,new TextEncoder().encode(name)) as Window
}

export function destroyWindow(window:Window){
    lib.symbols.destroyWindow(window);
}

export function drawFrame(window:Window){
    lib.symbols.drawFrame(window);
}

export function getEvent(window:Window){
    const rawEvent = lib.symbols.getEvent(window);
    let event: Event;


    const type = lib.symbols.getEventType(rawEvent) as eventType;

    switch (type){
        case eventType.none:
        case eventType.close: 
            event = {type:type};/* falls through */
            break;
        case eventType.MouseDown:
        case eventType.MouseUp:
        case eventType.MouseMove:{
            const x = lib.symbols.getEventX(rawEvent) /* falls through */
            const y = lib.symbols.getEventY(rawEvent)
            event = {type:type,x:x,y:y}
            break;}
        case eventType.KeyDown:
        case eventType.KeyUp:{
            const keyCode = lib.symbols.getEventKey(rawEvent); /* falls through */
            const key = String.fromCharCode(keyCode);
            event = {type:type,key:key}
            break;}
    }

    //since event is a pointer we need to delete it
    lib.symbols.destroyEvent(rawEvent);

    return event;
}

//test stuff

const window = getWindow(100,100,"hello");

while(true){
    const event = getEvent(window)

    if(event.type == eventType.none)
        continue;
    console.log(event);
}