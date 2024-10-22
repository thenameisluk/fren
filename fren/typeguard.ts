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
    const txt = new TextEncoder().encode(s)
    const buf = new Uint8Array(txt.length+1)
    buf.set(txt);
    buf[txt.length]=0;
    return buf;
}