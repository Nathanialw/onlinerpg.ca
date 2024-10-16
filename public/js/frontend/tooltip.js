import { app, cellSize, Create_Text_Line, Draw_Sprite, minimapCellSize } from '../graphics/graphics.js';

let tooltip;
let properties = [];

export async function Draw_Tooltip(x, y) {
    Remove_Tooltip();

    const tooltipTexture = await PIXI.Assets.load('assets/graphics/ui/tooltip/tooltip.png');

    //get the itemID of the item in the loot array

    //read in the properties from the db
        
    properties.push("");
    properties.push("Iron Sword");
    properties.push("Damage: 1-5");
    properties.push("Speed: 1.5");
    properties.push("Range: 1");
    properties.push("Durability: 10");
    properties.push("Weight: 1");
    properties.push("");

    //keep track of the longest line
    let maxLengthLine = 10;
    for (let i = 0; i < properties.length; i++) {
        if (properties[i].length > maxLengthLine) {
            maxLengthLine = properties[i].length + 2;
        }
    }
    //keep track of the number of lines
    let numLines = properties.length;

    tooltip = new PIXI.Sprite(tooltipTexture);
    Draw_Sprite(x, y, maxLengthLine * cellSize, numLines * cellSize, tooltip);

    for (let i = 0; i < numLines; i++) {
        properties[i] = Create_Text_Line(" " + properties[i] + " ", minimapCellSize, i, x / cellSize, y / cellSize);
    }
    console.log("lines:", properties.length);

}

export function Remove_Tooltip() {
    console.log("lines:", properties.length);
    if (properties) {
        for (let i = 0; i < properties.length; i++) {
            app.stage.removeChild(properties[i]);
        }
        properties.length = 0;
    }

    if (tooltip) {
        app.stage.removeChild(tooltip);
        tooltip = null;
    }
}