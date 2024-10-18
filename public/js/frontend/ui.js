'use strict'
import { app, Create_Combat_Log_Line, Draw_UI, Draw_UI_Phone, Draw_Vision_Background, Draw_Vision_Background_Phone} from '../graphics/graphics.js';
import { Make_Map, Draw_Map, Draw_Map_Phone} from '../map/map.js';
import { characterInfo, Species} from '../units/unitdef.js';
import { SoundAttack } from '../sound/sound.js';
import { Query_Loot, Draw_Loot } from '../objects/loot.js';
import { Draw_Inventory, Query_Inventory } from '../objects/inventory.js';
import { Query_Equipment, Draw_Equipment } from '../objects/equipment.js';
import { Draw_Game_Menu, gamePanelIndex } from '../ui/menus/gameMenu.js';
import { Draw_Main_Menu } from '../ui/menus/mainMenu.js';
import { Render_Game_Panel } from '../ui/gamePanels/gamePanels.js';

// import {Create_Map_Line, Create_MiniMap_Line, Draw_UI, Draw_Vision_Background} from '../graphics/graphics.js';
// import {Set_Enemies, Set_Player, Set_Objects} from '../objects/objects.js';
// import {characterInfo} from '../units/unitdef.js';

let log = [];
let logDisplay = [];

let maxLines = 10;
let currentLine = maxLines;

function Add_Line(line) {
    log.push(line)
    for (let i = 0; i < log.length; i++) {
        currentLine--;
    }
}

function Render_Log() {
    let logLine;
    let beginLine;
    let endLine = log.length;
    if (log.length > maxLines) {
        logLine = 0;
        beginLine = log.length - maxLines;
    }
    else {
        logLine = 9 - log.length;
        beginLine = 0;
    }
    for (let i = beginLine; i < endLine; i++) {
        logDisplay[logLine] = Create_Combat_Log_Line(log[i], logLine);
        logLine++;
    }
}

function Display_Damage_Taken(species, damageTaken) {
    if (damage === "  ") {
        return
    }
    let text = "You have been struck by a " + species + " for " + damageTaken + " damage"
    Add_Line(text);
}

function Display_Damage(species, damage, isDead) {
    if (damage === "  ") {
        return
    }
    let text = "You have done " + damage + " damage to a " + species; 
    if (isDead === "0") {
        text += " and killed it!";
    }
    SoundAttack(); //play attack sound based on weapon equipped
    Add_Line(text);
}

let visionWidth;
let direction;
let species;
let damage;
let isDead;
let serverMap;
// let numItems;
let loot = [];
// let numInventory;
let inventory = [];
let equipment = []; //list of item {slot, itemID, path string)

function Parse(numItems, start, data, Query, size, items) {
    removeEventListenersFromArray(items);
    items.length = 0; // Clear the array without reassigning it
    if (numItems > 0) {
        items.push(...Query(numItems, data, start));
    }    
    
    return start + (numItems * size); 
}

export function Map(data) {
    visionWidth = parseInt(data.substring(0, 2), 10);
    direction = data.substring(2,3);
    species = Species[data.substring(3,4)];
    damage = data.substring(4,6);
    isDead = data.substring(6,7);
    // let damageTaken = data.substring(4,6);
    // let currentHealth = data.substring(6,8);

    loot.length = 0;
    inventory.length = 0;
    equipment.length = 0;
    const endLoot = Parse(data.substring(7,8), 8, data, Query_Loot, 3, loot);
    const endInventory = Parse(data.substring(endLoot, endLoot + 2), (endLoot + 2), data, Query_Inventory, 5, inventory);
    const endEquipment = Parse(data.substring(endInventory, endInventory + 2), (endInventory + 2), data, Query_Equipment, 5, equipment);
 
    serverMap = data.substring(endEquipment);

    // serverMap = data.substring(8);
    Update_Screen();
}


export function Update_Screen_Phone() {
    app.stage.removeChildren();
    
    Draw_UI_Phone(characterInfo);
    Draw_Vision_Background_Phone(visionWidth);
    Make_Map(serverMap, visionWidth);
    // Draw_Map_Phone(visionWidth, direction);
    
    // Display_Damage_Taken(species, damageTaken);
    // Display_Damage(species, damage, isDead)
    // Render_Log();
    // Render_Target_Stats();

}

export function Update_Screen() {
    app.stage.removeChildren();
    
    Draw_UI(gamePanelIndex);
    Draw_Vision_Background(visionWidth);
    Make_Map(serverMap, visionWidth);
    // Draw_Map(visionWidth, direction);
    
    Draw_Loot(loot);
    Draw_Inventory(inventory);
    Draw_Equipment(equipment); //pass the list of the strings of the path to the icons

    Draw_Main_Menu();
    Draw_Game_Menu();

    // Display_Damage_Taken(species, damageTaken);
    Display_Damage(species, damage, isDead)
    Render_Log();
    
    //render fame panel ie. target stats, spell book, combat log, minimap, crafting
    Render_Game_Panel(gamePanelIndex);    
}

// Function to remove event listeners from an array of objects
function removeEventListenersFromArray(array) {
    array.forEach(item => {
        if (item && item.removeAllListeners) {
            item.removeAllListeners();
        }
    });
}
