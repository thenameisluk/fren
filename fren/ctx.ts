import { libfren } from "./libfren.ts";
import { cstring, i32, u32, u8 } from "./typeguard.ts";
import { Surface } from "./window.ts"

type Color = number

//drawing related stuff
export function getColor(r:number,g:number,b:number){
    return libfren.symbols.getColor(u8(r),u8(g),u8(b)) as Color;
}

export function drawLineLeftRight(ctx:Surface,x:number,y:number,len:number,color:Color){
    libfren.symbols.drawLineLeftRight(ctx,i32(x),i32(y),i32(len),color);
}

export function drawLineUpDown(ctx:Surface,x:number,y:number,len:number,color:Color){
    libfren.symbols.drawLineUpDown(ctx,i32(x),i32(y),i32(len),color);
}

export function fillRect(ctx:Surface,x:number,y:number,w:number,h:number,color:Color){
    libfren.symbols.fillRect(ctx,i32(x),i32(y),u32(w),u32(h),color)
}

export function drawRect(ctx:Surface,x:number,y:number,w:number,h:number,color:Color){
    libfren.symbols.drawRect(ctx,i32(x),i32(y),u32(w),u32(h),color)
}

export function fill(ctx:Surface,color:Color){
    libfren.symbols.fill(ctx,color)
}

export function drawLine(ctx:Surface,x1:number,y1:number,x2:number,y2:number,color:Color){
    libfren.symbols.drawLine(ctx,i32(x1),i32(y1),i32(x2),i32(y2),color)
}

export function drawTriangle(ctx:Surface,x1:number,y1:number,x2:number,y2:number,x3:number,y3:number,color:Color){
    libfren.symbols.drawTriangle(ctx,i32(x1),i32(y1),i32(x2),i32(y2),i32(x3),i32(y3),color)
}

export function fillTriangle(ctx:Surface,x1:number,y1:number,x2:number,y2:number,x3:number,y3:number,color:Color){
    libfren.symbols.fillTriangle(ctx,i32(x1),i32(y1),i32(x2),i32(y2),i32(x3),i32(y3),color)
}


export function print(ctx:Surface,text:string,x:number,y:number,size:number,color:Color){
    libfren.symbols.print(ctx,cstring(text),i32(x),i32(y),u32(size),color)
}

export function printNumber(ctx:Surface,number:number,x:number,y:number,size:number,color:Color){
    libfren.symbols.printNumber(ctx,i32(number),i32(x),i32(y),u32(size),color)
}