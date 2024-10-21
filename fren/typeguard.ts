export function u8(n:number){
    return n & 0xFF;
}

export function i32(n:number){
    return (n | 0);///Unsigned right shift because TS :3
}

export function u32(n:number){
    return (n & 0xFFFFFFFF) >>> 0;///Unsigned right shift because TS :3
}

export function cstring(s:string){
    return new TextEncoder().encode(s);
}