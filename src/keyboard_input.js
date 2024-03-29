import {player} from "./index.js"
import {socket} from "./receive.js"


var sound = new Howl ({
    src: ['../assets/swish_2.wav'],
    html5: true
});

const cell_size = 24;

document.addEventListener("keydown", (event) => {
    const keyName = event.key;
    
    if (keyName === "w") {
        player.y -= cell_size;
        // socket.send("1w");       
        //send to server
        return;
    }
    
    if (keyName === "a") {
        player.x -= cell_size;
        // socket.send("1a");       
        //send to server
        return;
    }
    
    if (keyName === "s") {
        player.y += cell_size;
        // socket.send("1s");       
        //send to server
        return;
    }
    
    if (keyName === "d") {
        player.x += cell_size;
        // socket.send("1d");       
        //send to server
        return;
    }
    
    if (keyName === "Enter") {
        sound.play();
        socket.send("The Spacebar has been pressed");            
        return;
    }

    if (event.ctrlKey) {
    // Even though event.key is not 'Control' (e.g., 'a' is pressed),
    // event.ctrlKey may be true if Ctrl key is pressed at the same time.
        sound.play();    
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
