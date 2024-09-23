'use strict'

import {Move} from "../movement/movement.js"
import {Actions} from "./action/action.js"
import {SoundPlay} from "../sound/sound.js"



let Update = {
    Enter: Actions,
    a: Move,
    w: Move,
    s: Move,
    d: Move,
    r: Move,
    Control: SoundPlay
}

document.addEventListener("keypress", (event) => {
    //key held down
})
			  
document.addEventListener("keydown", (event) => {
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
