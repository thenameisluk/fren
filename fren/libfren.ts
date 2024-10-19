//loading library stuff
let libName;

switch (Deno.build.os){
    case "linux":
    libName = "./libfren-"+Deno.build.arch+".so";
    break;
    default:
        console.log("os not supported");
        Deno.exit(-1)
}
console.log("loading "+libName)
export const libfren = Deno.dlopen(libName,{
    //debug
    "externUwU":{
        parameters:[],
        result:"void",
    },
    //window management
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
        result:"i32"
    },
    "getEventY":{
        parameters:["pointer"],
        result:"i32"
    },
    "destroyEvent":{
        parameters:["pointer"],
        result:"void"
    },
    //drawing context
    "getColor":{
        parameters:["u8","u8","u8"],
        result:"u32"
    },
    "drawLineLeftRight":{
        parameters:["pointer","i32","i32","i32","u32"],
        result:"void"
    },
    "drawLineUpDown":{
        parameters:["pointer","i32","i32","i32","u32"],
        result:"void"
    },
    "fillRect":{
        parameters:["pointer","i32","i32","u32","u32","u32"],
        result: "void"
    },
    "drawRect":{
        parameters:["pointer","i32","i32","u32","u32","u32"],
        result: "void"
    },
    "fill":{
        parameters:["pointer","u32"],
        result:"void"
    },
    "drawLine":{
        parameters:["pointer","i32","i32","i32","i32","u32"],
        result:"void"
    },
    "drawTriangle":{
        parameters:["pointer","i32","i32","i32","i32","i32","i32","u32"],
        result:"void"
    },
    "fillTriangle":{
        parameters:["pointer","i32","i32","i32","i32","i32","i32","u32"],
        result:"void"
    },
    "print":{
        parameters:["pointer","buffer","i32","i32","u32","u32"],
        result:"void"
    },
    "printNumber":{
        parameters:["pointer","i32","i32","i32","u32","u32"],
        result:"void"
    }
})