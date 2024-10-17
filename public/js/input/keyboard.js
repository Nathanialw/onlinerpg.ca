'use strict'

import {Move} from "../movement/movement.js"
import {Actions} from "./action/action.js"
import {SoundPlay} from "../sound/sound.js"
import {Send_Web_Socket_Message} from "../networking/socket.js"
import {ReSend} from "../frontend/charCreate.js"

//restart with all the same input stats
function Restart(data) {
    Send_Web_Socket_Message("6")
    ReSend();
    //set proper html
}

//quit to main page
function Quit(data) {
    Send_Web_Socket_Message("7")
    //set proper html
}

function Spell(keyName) {
    console.log("spell", keyName)
}

let actionBar = {
    1: Spell,
    2: Spell,
    3: Spell,
    4: Spell,
    5: Spell,
    6: Spell,
    7: Spell,
    8: Spell,
    9: Spell,
    0: Spell,
}


function Action_Bar(keyName) {
    actionBar[keyName](keyName)
}


let Update = {
    Enter: Actions,
    a: Move,
    w: Move,
    s: Move,
    d: Move,
    r: Move,
    ' ': Move,
    p: Restart,
    Escape: Quit,
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
}

document.addEventListener("keypress", (event) => {
    //key held down
})
			  
document.addEventListener("keydown", (event) => {
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
    //use a hash map instead
    if (Update[keyName](keyName)) {
	    return;
    }
    
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
