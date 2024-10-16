import { app, cellSize, Draw_Sprite } from '../graphics/graphics.js';

let tooltip;

export async function Draw_Tooltip(x, y) {
    Remove_Tooltip();

    const tooltipTexture = await PIXI.Assets.load('assets/graphics/ui/tooltip/tooltip.png');
    tooltip = new PIXI.Sprite(tooltipTexture);
    return Draw_Sprite(x, y, 10*cellSize, 12*cellSize, tooltip);
}

export function Remove_Tooltip() {
    if (tooltip) {
        app.stage.removeChild(tooltip);
        tooltip = null;
    }
}