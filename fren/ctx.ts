import { cstring, i32, u32, u8 } from "./typeguard.ts";

//loading library stuff
let libName;

switch (Deno.build.os) {
    case "linux":
        libName = "./libctx-" + Deno.build.arch + ".so";
        break;
    default:
        console.log("os not supported yet");
        Deno.exit(-1);
}

console.log("loading " + libName);
const libctx = Deno.dlopen(libName, {
    "getWidth":{
        parameters:["pointer"],
        result:"u32"
    },
    "getHeight":{
        parameters:["pointer"],
        result:"u32"
    },
    "getColor": {
        parameters: ["u8", "u8", "u8"],
        result: "u32",
    },
    "drawLineLeftRight": {
        parameters: ["pointer", "i32", "i32", "i32", "u32"],
        result: "void",
    },
    "drawLineUpDown": {
        parameters: ["pointer", "i32", "i32", "i32", "u32"],
        result: "void",
    },
    "fillRect": {
        parameters: ["pointer", "i32", "i32", "u32", "u32", "u32"],
        result: "void",
    },
    "drawRect": {
        parameters: ["pointer", "i32", "i32", "u32", "u32", "u32"],
        result: "void",
    },
    "fill": {
        parameters: ["pointer", "u32"],
        result: "void",
    },
    "drawLine": {
        parameters: ["pointer", "i32", "i32", "i32", "i32", "u32"],
        result: "void",
    },
    "drawTriangle": {
        parameters: [
            "pointer",
            "i32",
            "i32",
            "i32",
            "i32",
            "i32",
            "i32",
            "u32",
        ],
        result: "void",
    },
    "fillTriangle": {
        parameters: [
            "pointer",
            "i32",
            "i32",
            "i32",
            "i32",
            "i32",
            "i32",
            "u32",
        ],
        result: "void",
    },
    "fillCircle": {
        parameters: ["pointer", "i32", "i32", "u32", "u32"],
        result: "void",
    },
    "fillThickLine": {
        parameters: ["pointer", "i32", "i32", "i32", "i32", "u32", "u32"],
        result: "void",
    },
    "fillThickCurvedLine":{
        parameters: ["pointer", "i32", "i32", "i32", "i32", "i32", "i32", "u32", "u32"],
        result: "void"
    },
    "print": {
        parameters: ["pointer", "buffer", "i32", "i32", "u32", "u32"],
        result: "void",
    },
    "printNumber": {
        parameters: ["pointer", "i32", "i32", "i32", "u32", "u32"],
        result: "void",
    },
});

export type context = Deno.PointerValue<number>;

export type Color = number

//drawing related stuff
export function getWidth(ctx:context){
    return libctx.symbols.getWidth(ctx);
}
export function getHeight(ctx:context){
    return libctx.symbols.getHeight(ctx);
}
export function getColor(r:number,g:number,b:number){
    return libctx.symbols.getColor(u8(r),u8(g),u8(b)) as Color;
}

export function drawLineLeftRight(ctx:context,x:number,y:number,len:number,color:Color){
    libctx.symbols.drawLineLeftRight(ctx,i32(x),i32(y),i32(len),color);
}

export function drawLineUpDown(ctx:context,x:number,y:number,len:number,color:Color){
    libctx.symbols.drawLineUpDown(ctx,i32(x),i32(y),i32(len),color);
}

export function fillRect(ctx:context,x:number,y:number,w:number,h:number,color:Color){
    libctx.symbols.fillRect(ctx,i32(x),i32(y),u32(w),u32(h),color)
}

export function drawRect(ctx:context,x:number,y:number,w:number,h:number,color:Color){
    libctx.symbols.drawRect(ctx,i32(x),i32(y),u32(w),u32(h),color)
}

export function fill(ctx:context,color:Color){
    libctx.symbols.fill(ctx,color)
}

export function drawLine(ctx:context,x1:number,y1:number,x2:number,y2:number,color:Color){
    libctx.symbols.drawLine(ctx,i32(x1),i32(y1),i32(x2),i32(y2),color)
}

export function drawTriangle(ctx:context,x1:number,y1:number,x2:number,y2:number,x3:number,y3:number,color:Color){
    libctx.symbols.drawTriangle(ctx,i32(x1),i32(y1),i32(x2),i32(y2),i32(x3),i32(y3),color)
}

export function fillTriangle(ctx:context,x1:number,y1:number,x2:number,y2:number,x3:number,y3:number,color:Color){
    libctx.symbols.fillTriangle(ctx,i32(x1),i32(y1),i32(x2),i32(y2),i32(x3),i32(y3),color)
}

export function fillCircle(ctx:context,x:number,y:number,radius:number,color:Color){
    libctx.symbols.fillCircle(ctx,i32(x),i32(y),i32(radius),i32(color))
}

export function fillThickLine(ctx:context,x1:number,y1:number,x2:number,y2:number,thickness:number,color:Color){
    libctx.symbols.fillThickLine(ctx,i32(x1),i32(y1),i32(x2),i32(y2),i32(thickness),color)
}

export function fillThickCurvedLine(ctx:context,x1:number,y1:number,x2:number,y2:number,offx:number,offy:number,thickness:number,color:Color){
    libctx.symbols.fillThickCurvedLine(ctx,i32(x1),i32(y1),i32(x2),i32(y2),i32(offx),i32(offy),i32(thickness),color)
}

export function print(ctx:context,text:string,x:number,y:number,size:number,color:Color){
    libctx.symbols.print(ctx,cstring(text),i32(x),i32(y),u32(size),color)
}

export function printNumber(ctx:context,number:number,x:number,y:number,size:number,color:Color){
    libctx.symbols.printNumber(ctx,i32(number),i32(x),i32(y),u32(size),color)
}