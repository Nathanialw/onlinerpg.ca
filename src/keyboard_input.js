import * as Howl from '../libs/howler.core.js';


var sound = new Howl ({
    src: ['swish_2.wav'],
    html5: true
});

document.addEventListener("keydown", (event) => {
        const keyName = event.key;

        if (keyName === "a") {
            sound.play();                
        // do not alert when only Control key is pressed.
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
