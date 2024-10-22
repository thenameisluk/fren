//test stuff

import { drawLine, fillRect, fillTriangle, getColor, printNumber } from "./fren/ctx.ts";
import { drawFrame, eventType, externUwU, getEvent, getWindow } from "./fren/window.ts";

const window = getWindow(100,100,"hello");

let x=0,y=0;

externUwU();

while(true){
    const event = getEvent(window)
    fillRect(window,0,0,100,100,getColor(255,0,0));
    fillTriangle(window,30,0,50,20,10,50,getColor(0,255,0));
    drawLine(window,50,50,x,y,getColor(0,0,255));
    drawLine(window,0,0,x,y,getColor(0,0,255));
    drawLine(window,0,0,100,100,getColor(0,0,255));
    drawLine(window,100,100,0,50,getColor(0,0,255));
    drawLine(window,0,50,100,50,getColor(0,0,255));
    drawLine(window,100,50,0,0,getColor(0,0,255));

    //fix infinit loop
    printNumber(window,-2137,0,0,1,getColor(255,255,255));

    
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