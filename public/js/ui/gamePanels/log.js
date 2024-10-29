'use strict';
import { Create_Combat_Log_Line } from '../../graphics/graphics.js';
import { SoundAttack } from '../../sound/sound.js';


let log = [];
let logDisplay = [];

let maxLines = 18;
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
        logLine = -11;
        beginLine = log.length - maxLines;
    }
    else {
        logLine = 7 - log.length;
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
    if (isDead === 0) {
        text += " and killed it!";
    }
    SoundAttack(); //play attack sound based on weapon equipped
    Add_Line(text);
}


export function Update_Log(species, damage, isDead) {
    Display_Damage(species, damage, isDead);
    Render_Log();
}