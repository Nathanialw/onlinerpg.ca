'use strict'

import {Move} from "../movement/movement.js"
import {Actions} from "./action/action.js"
import {Action_Bar} from "../spells/spell.js"
import {Restart, Quit} from "../game/game.js"


let Update = {
    a: Move,
    w: Move,
    s: Move,
    d: Move,
    r: Move, //rest
    ' ': Move,
    1: Action_Bar,
    2: Action_Bar,
    3: Action_Bar,
    4: Action_Bar,
    5: Action_Bar,
    6: Action_Bar,
    7: Action_Bar,
    8: Action_Bar,
    9: Action_Bar,
    0: Action_Bar,
    q: Action_Bar,
    e: Action_Bar,
    r: Action_Bar,
    f: Action_Bar,
}

let keyIntervals = {};
const repeatInterval = 200; // 200ms

export function Init_Keybinds() {
    document.addEventListener("keypress", (event) => {
        if (event.repeat) {
            return;
        }
        if (event.ctrlKey) {
            return;
        }
        if (event.altKey) {
            return;
        }
        if (event.shiftKey) {
            return;
        }

        const keyName = event.key;
        if (Update[keyName]) {
            if (!keyIntervals[keyName]) {
                Update[keyName](keyName); // Initial action
                keyIntervals[keyName] = setInterval(() => {
                    Update[keyName](keyName);
                }, repeatInterval);
            }
        }
    });

    document.addEventListener("keyup", (event) => {
        const keyName = event.key;
        if (keyIntervals[keyName]) {
            clearInterval(keyIntervals[keyName]);
            delete keyIntervals[keyName];
        }
    });
    
                
    document.addEventListener("keydown", (event) => {
        
        
        //if cast spell
        //if attack
        //if insteract
        //if UI? maybe

        // W, A, S, D || UP, DOWN, LEFT, RIGHT
        // 1, 2, 4, 5, 6, etc... TO CAST SPELLS
        // B, C, P, I, etc... UI BUTTONS
    });

    document.addEventListener("keyup", (event) => {
        const keyName = event.key;

        // As the user releases the Ctrl key, the key is no longer active,
        // so event.ctrlKey is false.
        
    });
}

Init_Keybinds()