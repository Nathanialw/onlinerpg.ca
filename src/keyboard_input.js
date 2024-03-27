import {sprite} from "./index.js"


var sound = new Howl ({
    src: ['../assets/swish_2.wav'],
    html5: true
});


document.addEventListener("keydown", (event) => {
    const keyName = event.key;
    
    if (keyName === "space") {
        sound.play();                
        // do not alert when only Control key is pressed.
        return;
    }
    
        if (keyName === "w") {
            sprite.y -= 5;
            return;
        }

        if (keyName === "a") {
            sprite.x -= 5;
            return;
        }

        if (keyName === "s") {
            sprite.y += 5;
            return;
        }

        if (keyName === "d") {
            sprite.x += 5;
            return;
        }

        if (event.ctrlKey) {
        // Even though event.key is not 'Control' (e.g., 'a' is pressed),
        // event.ctrlKey may be true if Ctrl key is pressed at the same time.
            sound.play();                
        } 
        else {

        }
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
