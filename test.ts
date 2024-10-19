//test stuff

import { drawLine, fillRect, fillTriangle, getColor } from "./fren/ctx.ts";
import { drawFrame, eventType, getEvent, getWindow } from "./fren/window.ts";

const window = getWindow(100,100,"hello");

let x=0,y=0;

while(true){
    const event = getEvent(window)
    fillRect(window,0,0,100,100,getColor(255,0,0));
    fillTriangle(window,30,0,50,20,10,50,getColor(0,255,0));
    drawLine(window,0,0,x,y,getColor(0,0,255));

    
    drawFrame(window);

    if(event.type == eventType.MouseMove){
        x = event.x
        y = event.y
    }

    if(event.type == eventType.none)
        continue;

    console.log(event);

    if(event)

    if(event.type == eventType.close)
        Deno.exit(0);
}