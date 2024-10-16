import { Get_Item_Stats } from '../db/db.js';
import { app, cellSize, Create_Text_Line, Draw_Sprite, minimapCellSize } from '../graphics/graphics.js';

let tooltip;
let properties = [];

export async function Draw_Tooltip(x, y, itemID) {
    Remove_Tooltip();

    const tooltipTexture = await PIXI.Assets.load('assets/graphics/ui/tooltip/tooltip.png');

    //get the itemID of the item in the loot array

    // HOW???
    const itemID = 2;
    //read in the properties from the db
    const itemStatsArray = await Get_Item_Stats(itemID);
    const itemStats = itemStatsArray[0];

    properties.push("");
    properties.push(itemStats.name);
    properties.push("");
    if (itemStats.equipSlot !== "notEquppable") {
        properties.push("");
    }
    if (itemStats.minDamage !== 0 && itemStats.maxDamage !== 0) {
        properties.push("Damage: " + itemStats.minDamage + "-" + itemStats.maxDamage);
    }
    if (itemStats.AC !== 0) {
        properties.push("Armour: " + itemStats.AC);
    }
    // properties.push("Speed: 1.5");
    properties.push("Range: 1");
    properties.push("");
    properties.push("Durability: 10");
    properties.push("Weight: 1");
    properties.push("");
    if (itemStats.description !== 0) {
        properties.push(itemStats.description);
    }
    properties.push("");

    //keep track of the longest line
    let maxLengthLine = 10;
    for (let i = 0; i < properties.length; i++) {
        if (properties[i].length > maxLengthLine) {
            maxLengthLine = properties[i].length + 2;
        }
    }

    //set equpslot of the right side of the tooltip
    if (itemStats.equipSlot !== "notEquppable") {
        const spaces = " ".repeat(maxLengthLine - itemStats.equipSlot.length - 2);
        properties[3] = spaces + itemStats.equipSlot;
    }

    //keep track of the number of lines
    let numLines = properties.length;

    tooltip = new PIXI.Sprite(tooltipTexture);
    Draw_Sprite(x, y, maxLengthLine * minimapCellSize, numLines * minimapCellSize, tooltip);

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