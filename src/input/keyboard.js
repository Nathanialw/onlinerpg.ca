import {Move} from "../movement/movement.js"

var sound = new Howl ({
    src: ['../assets/swish_2.wav'],
    html5: true
});


document.addEventListener("keydown", (event) => {
    const keyName = event.key;
    
    if (Move(keyName)) {
        return; 
    }
    
    if (keyName === "Enter") {
        sound.play();
        return;
    }

    if (event.ctrlKey) {
    // Even though event.key is not 'Control' (e.g., 'a' is pressed),
    // event.ctrlKey may be true if Ctrl key is pressed at the same time.
        return;            
    }

    // W, A, S, D || UP, DOWN, LEFT, RIGHT
    // 1, 2, 4, 5, 6, etc... TO CAST SPELLS
    // B, C, P, I, etc... UI BUTTONS
    },
    false,
);

    document.addEventListener("keyup", (event) => {
        const keyName = event.key;

        // As the user releases the Ctrl key, the key is no longer active,
        // so event.ctrlKey is false.
        if (keyName === "Control") {
        }
    },
    false,
);
