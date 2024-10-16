import { app, cellSize, Create_Text_Line, Draw_Sprite } from '../graphics/graphics.js';

let tooltip;
let lines = [];

export async function Draw_Tooltip(x, y) {
    Remove_Tooltip();

    const tooltipTexture = await PIXI.Assets.load('assets/graphics/ui/tooltip/tooltip.png');

    let maxLengthLine = 10;
    let numLines = 12;
    tooltip = new PIXI.Sprite(tooltipTexture);
    Draw_Sprite(x, y, maxLengthLine * cellSize, numLines * cellSize, tooltip);
    lines[0] = Create_Text_Line("This is a test", cellSize, 1, x, y);
    lines[1] = Create_Text_Line("This is a test line 2", cellSize, 2, x, y);
}

export function Remove_Tooltip() {
    if (lines) {
        for (let i = 0; i < lines.length; i++) {
            app.stage.removeChild(lines[i]);
        }
        lines.length = 0;
    }

    if (tooltip) {
        app.stage.removeChild(tooltip);
        tooltip = null;
    }
}