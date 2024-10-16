import { app, cellSize, Create_Text_Line, Draw_Sprite } from '../graphics/graphics.js';

let tooltip;
let lines = [];

export async function Draw_Tooltip(x, y) {
    Remove_Tooltip();

    const tooltipTexture = await PIXI.Assets.load('assets/graphics/ui/tooltip/tooltip.png');

    maxLengthLine = 10;
    numLines = 12;
    tooltip = new PIXI.Sprite(tooltipTexture);
    Draw_Sprite(x, y, maxLengthLine * cellSize, numLines * cellSize, tooltip);
    Create_Text_Line("This is a test", cellSize, 1, x, y);
    Create_Text_Line("This is a test line 2", cellSize, 2, x, y);
}

export function Remove_Tooltip() {
    if (tooltip) {
        app.stage.removeChild(tooltip);
        tooltip = null;
    }
}