'use strict'
import {Create_Combat_Log_Line, Draw_UI} from '../graphics/graphics.js';
import {Make_Map, Draw_Map} from '../map/map.js';
import {characterInfo, Species} from '../units/unitdef.js';

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
    Add_Line(text);
}

export function Map(data) {
    let visionWidth = parseInt(data.substring(0, 2), 10);
    let direction = data.substring(2,3);
    let species = Species[data.substring(3,4)];
    let damage = data.substring(4,6);
    let isDead = data.substring(6,7);
    // let damageTaken = data.substring(4,6);
    // let currentHealth = data.substring(6,8);
    let serverMap = data.substring(7);
    console.log("Redrawing Game");
    Draw_UI(characterInfo);
    Make_Map(serverMap, visionWidth);
    Draw_Map(visionWidth, direction);
    
    // Display_Damage_Taken(species, damageTaken);
    Display_Damage(species, damage, isDead)
    Render_Log();
}