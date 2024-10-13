'use strict'
import { app, Create_Combat_Log_Line, Draw_UI, Draw_UI_Phone, Draw_Vision_Background, Draw_Vision_Background_Phone} from '../graphics/graphics.js';
import { Make_Map, Draw_Map, Draw_Map_Phone} from '../map/map.js';
import { characterInfo, Species} from '../units/unitdef.js';
import { Render_Target_Stats } from './stats.js';   
import { SoundAttack } from '../sound/sound.js';
import { Query_Loot, Draw_Loot } from '../objects/loot.js';

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
    SoundAttack();
    Add_Line(text);
}

let visionWidth;
let direction;
let species;
let damage;
let isDead;
let serverMap;
// let numItems;
let items = [];
// let numInventory;
let inventory = [];

export function Map(data) {
    visionWidth = parseInt(data.substring(0, 2), 10);
    direction = data.substring(2,3);
    species = Species[data.substring(3,4)];
    damage = data.substring(4,6);
    isDead = data.substring(6,7);
    // let damageTaken = data.substring(4,6);
    // let currentHealth = data.substring(6,8);
    
    const numItems = data.substring(7,8);
    items = [];
    if (numItems > "0") {
        items = Query_Loot(numItems, data);
    }    
    const endLoot = 8 + (numItems * 3);

    const numInventory = data.substring(endLoot, endLoot + 1);
    inventory = [];
    if (numInventory > "0") {
        console.log("numInventory: ", numInventory);
        // inventory = Query_Loot(numItems, data);
    }    
    const endInventory = (endLoot + 1) + (numInventory * 3);


    serverMap = data.substring(endInventory);

    // serverMap = data.substring(8);
    Update_Screen();
}


export function Update_Screen_Phone() {
    console.log("Clearing screen");
    app.stage.removeChildren();
    
    Draw_UI_Phone(characterInfo);
    Draw_Vision_Background_Phone(visionWidth);
    Make_Map(serverMap, visionWidth);
    Draw_Map_Phone(visionWidth, direction);
    
    // Display_Damage_Taken(species, damageTaken);
    // Display_Damage(species, damage, isDead)
    // Render_Log();
    // Render_Target_Stats();

}

export function Update_Screen() {
    console.log("Clearing screen");
    app.stage.removeChildren();
    
    Draw_UI(characterInfo);
    Draw_Vision_Background(visionWidth);
    Make_Map(serverMap, visionWidth);
    Draw_Map(visionWidth, direction);
    
    Draw_Loot(items);

    // Display_Damage_Taken(species, damageTaken);
    Display_Damage(species, damage, isDead)
    Render_Log();
    Render_Target_Stats();
}
