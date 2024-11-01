import { Get_Item_Stats, Get_By_UID_With_Zero } from '../db/db.js';
import { Get_Item_Effect_UID } from '../db/itemEffects.js';
import { app, cellSize, Create_Text_Line, Draw_Sprite, minimapCellSize } from '../graphics/graphics.js';

let tooltip;
let properties = [];

function Set_From_Right(textSprite, frameWidth) {
    textSprite.x = textSprite.x + frameWidth - textSprite.width;
}

export async function Draw_Tooltip(x, y, item) {
    Remove_Tooltip();
    console.log("Item hovered: ", item)

    const tooltipTexture = await PIXI.Assets.load('assets/graphics/ui/tooltip/tooltip.png');

    //read in the properties from the db
    const itemStatsArray = await Get_Item_Stats(item.ItemID);
    const itemStats = itemStatsArray[0];
 
    properties.push(itemStats.name.charAt(0).toUpperCase() + itemStats.name.slice(1));
    if (itemStats.equipSlot === "notEquippable") {
        properties.push("");
    }
    else {
        properties.push(itemStats.equipSlot + " ");               
    }    
    
    if (itemStats.material0) {
        properties.push(itemStats.material0.charAt(0).toUpperCase() + itemStats.material.slice(1));
    }
    if (itemStats.material1) {
        properties.push(itemStats.material1.charAt(0).toUpperCase() + itemStats.material.slice(1));
    }
    if (itemStats.material2) {
        properties.push(itemStats.material2.charAt(0).toUpperCase() + itemStats.material.slice(1));
    }
    
    if (itemStats.minDamage !== null && itemStats.maxDamage !== null) {
        properties.push("Damage: " + itemStats.minDamage + "-" + itemStats.maxDamage);
    }
    if (itemStats.AC !== null) {
        properties.push("Armour: " + itemStats.AC);
    }
    if (item.Durability !== null && item.Durability !== undefined) {
        //TODO: query db for max durability
        properties.push("Durability: " + (item.Durability/255 * itemStats.durability) + "/" + (itemStats.durability)); 
    }
    // properties.push("Speed: 1.5");
    if (itemStats.equipSlot == "consumable") {
        const consumable = await Get_By_UID_With_Zero("description", "itemEffects", Get_Item_Effect_UID(item.ItemID));
        properties.push(consumable.description);
    }
    else {
        if (itemStats.description !== null) {
            properties.push(itemStats.description);
        }
    }
    properties.push("");

    //keep track of the longest line
    let maxLengthLine = 10;
    for (let i = 0; i < properties.length; i++) {
        if (properties[i]) {
            if (properties[i].length > maxLengthLine) {
                maxLengthLine = properties[i].length;
            }
        }
    }
    maxLengthLine += 2;


    //keep track of the number of lines
    let numLines = properties.length;

    tooltip = new PIXI.Sprite(tooltipTexture);
    const frameWidth = maxLengthLine * cellSize;
    const frameHeight = numLines * cellSize;

    Draw_Sprite(x, y, frameWidth, frameHeight, tooltip);
    x =  x / cellSize;
    y =  y / cellSize;
    for (let i = 0; i < numLines; i++) {
        properties[i] = Create_Text_Line(properties[i], cellSize, i, x, y);
        if (i === 1) {
            Set_From_Right(properties[1], (frameWidth * .95))            
        }
    }
}

export function Remove_Tooltip() {
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