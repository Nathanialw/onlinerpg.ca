import { app, cellSize, Create_Text_Line, Draw_Sprite } from '../graphics/graphics.js';

const font = 12;
let tooltip;
let lines = [];

export async function Draw_Tooltip(x, y) {
    Remove_Tooltip();

    const tooltipTexture = await PIXI.Assets.load('assets/graphics/ui/tooltip/tooltip.png');

    let maxLengthLine = 10;
    let numLines = 12;
    tooltip = new PIXI.Sprite(tooltipTexture);
    Draw_Sprite(x, y, maxLengthLine * cellSize, numLines * cellSize, tooltip);

    lines[0] = Create_Text_Line("This is a test", font, 1, x / cellSize, y / cellSize);
    lines[1] = Create_Text_Line("This is a test line 2", font, 2, x / cellSize, y/ cellSize);
    console.log("lines:", lines.length);

}

export function Remove_Tooltip() {
    console.log("lines:", lines.length);
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