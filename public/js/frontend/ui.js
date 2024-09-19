'use strict'
import {Create_Combat_Log_Line, Draw_UI} from '../graphics/graphics.js';
import {Make_Map, Draw_Map} from '../map/map.js';
import {characterInfo, Species} from '../units/unitdef.js';

// import {Create_Map_Line, Create_MiniMap_Line, Draw_UI, Draw_Vision_Background} from '../graphics/graphics.js';
// import {Set_Enemies, Set_Player, Set_Objects} from '../objects/objects.js';
// import {characterInfo} from '../units/unitdef.js';

let combatLog = [];
let combatLogDisplay = [];

let maxLines = 10;
let currentLine = maxLines;

function Add_Line(line) {
    combatLog.push(line)
    for (let i = 0; i < combatLog.length; i++) {
        currentLine--;
    }
}

function Render_Log() {
    let beginLine;
    let endLine;
    //when lenght > 10 only grab the last 10 lines
    if (combatLog.length > maxLines) {
        beginLine = combatLog.length - maxLines;
        endLine = combatLog.length;
    }
    else {
        beginLine = 0;
        endLine = combatLog.length;
    }
    let logLine = 0;
    if (combatLog.length < maxLines) {
        for (let i = beginLine; i < endLine; i++) {
            combatLogDisplay[logLine] = Create_Combat_Log_Line(combatLog[i], i);
            logLine++;
        }
    }
}

function Dpsiplay_Health(species, damageTaken) {
    console.log("You have been struck by a " + species + " for " + damageTaken + " damage");
}

function Display_Damage(species, damage, isDead) {
    if (damage === "  ") {
        return
    }
    let damageText = "You have done " + damage + " damage to a " + species; 
    if (isDead === "0") {
        damageText += " and killed it!";
    }
    Add_Line(damageText);
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
    Display_Damage(species, damage, isDead)
    Render_Log();
}