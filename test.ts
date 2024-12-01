//test stuff
import {fill,fillCircle,getColor,fillThickLine,fillThickCurvedLine} from "./fren/ctx.ts"
import { drawFrame, externUwU, getWindow, getWindowctx } from "./fren/x11.ts";

const window = getWindow(100,100,"hello");

const ctx = getWindowctx(window);

externUwU();


while(true){
    fill(ctx,0);
    fillCircle(ctx,50,50,40,getColor(255,255,255));
    fillThickLine(ctx,20,20,30,70,3,getColor(255,0,0));
    fillThickLine(ctx,20,20,70,30,3,getColor(0,255,0));
    fillThickLine(ctx,30,70,70,30,3,getColor(0,0,255));
    fillThickCurvedLine(ctx,30,70,70,30,20,20,3,getColor(0,255,255));

    drawFrame(window);
}