'use strict';
import { Create_Combat_Log_Line } from '../../graphics/graphics.js';
import { SoundAttack } from '../../sound/sound.js';
import { Strip_Leading_Zeroes } from '../../utils/utils.js';

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
    if (damage === "__") {
        return
    }
    let text = "You have been struck by a " + species + " for " + damageTaken + " damage"
    Add_Line(text);
}

function Display_Damage(species, damage, isDead) {
    if (damage === "__") {
        return
    }
    let text = "You have done " + Strip_Leading_Zeroes(damage) + " damage to a " + species; 
    if (isDead === 1) {
        text += " and killed it!";
    }
    SoundAttack(); //play attack sound based on weapon equipped
    Add_Line(text);
}

function Resting(species, damage, isDead) {
    Add_Line("You are resting");
}

function Looting(species, damage, isDead) {
    Add_Line("You have looted an item");
}

function Collision(species, damage, isDead) {
    Add_Line("You have bumped into a wall");
}


const action = new Map([
    ['r', Resting],
    ['0', Resting],
    ['m', Display_Damage],
    ['a', Display_Damage],
    ['d', Display_Damage],
    ['w', Display_Damage],
    ['s', Display_Damage],
    ['l', Looting],
    ['c', Collision],
]);


export function Update_Log(direction, species, damage, isDead) {
    // Display_Damage(species, damage, isDead);
    action.get(direction)(species, damage, isDead);
    Render_Log();
}