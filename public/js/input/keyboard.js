import {Move} from "../movement/movement.js"

var sound = new Howl ({
    src: ['../../assets/sounds/swish_2.wav'],
    html5: true
});

function SoundPlay(keyName) {
    sound.play;
    return true
}


let Update = {
    Enter: SoundPlay,
    a: Move,
    w: Move,
    s: Move,
    d: Move,
}

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
}, false,);

document.addEventListener("keyup", (event) => {
    const keyName = event.key;

    // As the user releases the Ctrl key, the key is no longer active,
    // so event.ctrlKey is false.
    if (keyName === "Control") {
	
    }
}, false,);
