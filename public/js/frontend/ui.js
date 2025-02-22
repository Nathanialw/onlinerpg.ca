'use strict'
import { app, Draw_UI, Draw_Vision_Background, Wait_For_Load } from '../graphics/graphics.js';
import { Make_Map } from '../map/map.js';
import { Species, Update_Player_Stats } from '../units/unitdef.js';
import { Update_Loot } from '../objects/loot.js';
import { Draw_Inventory, Update_Inventory } from '../objects/inventory.js';
import { Draw_Equipment, Update_Equipment } from '../objects/equipment.js';
import { Draw_Game_Menu, gamePanelIndex } from '../ui/menus/gameMenu.js';
import { Draw_Main_Menu } from '../ui/menus/mainMenu.js';
import { Render_Game_Panel } from '../ui/gamePanels/gamePanels.js';
import { Update_Log } from '../ui/gamePanels/log.js';


// import { Parse_Inventory } from '../parse/inventory.js';

// import {Create_Map_Line, Create_MiniMap_Line, Draw_UI, Draw_Vision_Background} from '../graphics/graphics.js';
// import {Set_Enemies, Set_Player, Set_Objects} from '../objects/objects.js';
// import {characterInfo} from '../units/unitdef.js';


let visionWidth;
let direction;
let species = "";
let damage = "";
let isDead = "";
let serverMap = "";

// visionWidth = parseInt(data.substring(0, 2), 10);
// direction = data.substring(2,3);
// species = Species[data.substring(3,4)];
// damage = data.substring(4,6);
// isDead = data.substring(6,7);

function Parse_Player_Update(dataStr) {
    [species, damage, isDead] = ["", "", ""];
    [visionWidth, dataStr] = [parseInt(dataStr.substring(0, 2), 10), dataStr.substring(2)];
    [direction, dataStr]   = [dataStr.substring(0, 1), dataStr.substring(1)];
    [species, dataStr]     = [Species[parseInt(dataStr.substring(0, 2), 10)], dataStr.substring(2)];
    [damage, dataStr]      = [dataStr.substring(0, 2), dataStr.substring(2)];
    [isDead, dataStr]      = [parseInt(dataStr.substring(0, 1), 10), dataStr.substring(1)];
    return dataStr
}

function Update_Map(dataStr) {    
    serverMap = dataStr.substring(0, (visionWidth * visionWidth));
    return dataStr.substring(visionWidth * visionWidth);
}

function Parse_Recieved(dataStr) {
    //call individual parse functions
    //each function returns the remaining string to be parsed
    //pass the remaining string to the next function
    dataStr = Parse_Player_Update(dataStr);
    dataStr = Update_Loot(dataStr, direction);
    dataStr = Update_Inventory(dataStr);
    dataStr = Update_Equipment(dataStr);
    dataStr = Update_Map(dataStr);
    dataStr = Update_Player_Stats(dataStr);
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

    Update_Log(direction, species, damage, isDead);  
    Render_Game_Panel(gamePanelIndex);    //render fame panel ie. target stats, spell book, combat log, minimap, crafting

    Draw_Inventory();
    Draw_Equipment(); //pass the list of the strings of the path to the icons
}

export async function Game_Update(dataStr) {
    Parse_Recieved(dataStr);
    await Wait_For_Load();
    Update_Screen();    
}

// Function to remove event listeners from an array of objects
function removeEventListenersFromArray(array) {
    array.forEach(item => {
        if (item && item.removeAllListeners) {
            item.removeAllListeners();
        }
    });

}
