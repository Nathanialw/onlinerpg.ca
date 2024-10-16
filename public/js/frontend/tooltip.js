import * as PIXI from '/js/libs/pixi.js';
import { tooltip, app, cellSize } from '../graphics/graphics.js';


export async function Draw_Tooltip(x, y) {
    Remove_Tooltip();

    const tooltipTexture = await PIXI.Assets.load('assets/graphics/imgs/human/male/001.jpg');
    tooltip = new PIXI.Sprite(tooltipTexture);
    return Draw_Sprite(x, y, 10*cellSize, 12*cellSize, tooltip);
}

export function Remove_Tooltip() {
    if (tooltip) {
        app.stage.removeChild(tooltip);
        tooltip = null;
    }
}