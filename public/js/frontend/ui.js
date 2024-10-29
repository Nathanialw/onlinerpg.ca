'use strict'
import { app, Draw_UI, Draw_UI_Phone, Draw_Vision_Background, Draw_Vision_Background_Phone} from '../graphics/graphics.js';
import { Make_Map} from '../map/map.js';
import { characterInfo, Species} from '../units/unitdef.js';
import { Query_Loot } from '../objects/loot.js';
import { Draw_Inventory, Update_Inventory } from '../objects/inventory.js';
import { Query_Equipment, Draw_Equipment } from '../objects/equipment.js';
import { Draw_Game_Menu, gamePanelIndex } from '../ui/menus/gameMenu.js';
import { Draw_Main_Menu } from '../ui/menus/mainMenu.js';
import { Render_Game_Panel } from '../ui/gamePanels/gamePanels.js';
import { Update_Log } from '../ui/gamePanels/log.js';
import { loot, Open_Loot_Panel } from '../ui/gamePanels/loot.js';
import { Get_Icon_Path } from '../db/db.js';
// import { Parse_Inventory } from '../parse/inventory.js';

// import {Create_Map_Line, Create_MiniMap_Line, Draw_UI, Draw_Vision_Background} from '../graphics/graphics.js';
// import {Set_Enemies, Set_Player, Set_Objects} from '../objects/objects.js';
// import {characterInfo} from '../units/unitdef.js';


let visionWidth;
let direction;
let species;
let damage;
let isDead;
let serverMap;
// let numItems;
// let loot = [];
// let numInventory;
let equipment = []; //list of item {slot, itemID, path string)

function Parse(numItems, start, data, Query, size, items) {
    removeEventListenersFromArray(items);
    items.length = 0; // Clear the array without reassigning it
    if (numItems > 0) {
        items.push(...Query(numItems, data, start));
    }    
    
    return start + (numItems * size); 
}

// visionWidth = parseInt(data.substring(0, 2), 10);
// direction = data.substring(2,3);
// species = Species[data.substring(3,4)];
// damage = data.substring(4,6);
// isDead = data.substring(6,7);

function Parse_Player_Update(dataStr) {
    [visionWidth, dataStr] = [parseInt(dataStr.substring(0, 2), 10), dataStr.substring(2)];
    [direction, dataStr]   = [dataStr.substring(0, 1), dataStr.substring(1)];
    [species, dataStr]     = [parseInt(dataStr.substring(0, 2), 10), dataStr.substring(2)];
    [damage, dataStr]      = [parseInt(dataStr.substring(0, 2), 10), dataStr.substring(2)];
    [isDead, dataStr]      = [parseInt(dataStr.substring(0, 1), 10), dataStr.substring(1)];
    return dataStr
}

export function Parse_Game_Update_Full(data) {

}

export function Parse_Game_Update(data) {
    //call individual parse functions
    //each function returns the remaining string to be parsed
    //pass the remaining string to the next function

    data = Parse_Player_Update(data);

    const startBag = Parse(data.substring(0, 2), 2, data, Query_Loot, 3, loot);
    Open_Loot_Panel(direction);
    data = data.substring(startBag);
    
    data = Update_Inventory(data);
    
    const endEquipment = Parse(data.substring(0, 2), 2, data, Query_Equipment, 5, equipment);
    serverMap = data.substring(endEquipment);

    Update_Screen();
}

export function Update_Screen() {
    app.stage.removeChildren();

    //equal 3 when loot is stepped on, only trigger when initially stepping on loot

    Draw_UI(gamePanelIndex);
    Draw_Vision_Background(visionWidth);
    Make_Map(serverMap, visionWidth);
    // Draw_Map(visionWidth, direction);
    
    Draw_Main_Menu();
    Draw_Game_Menu();

    Update_Log(species, damage, isDead);  
    Render_Game_Panel(gamePanelIndex);    //render fame panel ie. target stats, spell book, combat log, minimap, crafting

    Draw_Inventory();
    Draw_Equipment(equipment); //pass the list of the strings of the path to the icons
}

// Function to remove event listeners from an array of objects
function removeEventListenersFromArray(array) {
    array.forEach(item => {
        if (item && item.removeAllListeners) {
            item.removeAllListeners();
        }
    });

}
