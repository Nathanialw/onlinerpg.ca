import { createWebSocket, socket } from '/js/networking/socket.js';

document.addEventListener('DOMContentLoaded', () => {
    createWebSocket();
    Buttons(races);
    Buttons(genders);
    Buttons(unitClasses);
    Buttons(alignments);
})

function Buttons(Option) {
    Option.options.forEach((value, key) => {
        document.getElementById(key).addEventListener('click', (event) => {            
            //highlight selected    
            document.getElementById(key).style.backgroundColor = "yellow";
            Option.value = value;
            //remove highlight from other
            Option.options.forEach((value, key) => {
                if (key != event.target.id) {
                    document.getElementById(key).style.backgroundColor = "white";
                }
            });
        })
    });
}


let races = {
    options: new Map([["Human", 7],["Elf", 4]]),
    value: 0
}

let genders = {
    options: new Map([["Male", 0],["Female", 1]]),
    value: 0
}

let unitClasses = {
    options:  new Map([["Fighter", 0],["Mystic", 1]]),
    value: 0
}

let alignments = {
    options: new Map([["Good", 0],["Neutral", 1],["Evil", 2]]),
    value: 0
}

let name = "John";

//send data to server
function Send() {
    let conn = socket()
    
    //get data from form
    name = document.getElementById("name").value;

    if (conn.isConnected) {
        conn.websocket.send("3" + name + genders.value + races.value + unitClasses.value + alignments.value);       
        console.log("char create Data sent to server")
    }
    else {
        console.log("Error: Server is not connected")
    }
}

document.getElementById('startGame').addEventListener('click', (event) => {
    Send();
    //remove form <section class='startButton'>
    const formSection = document.querySelector('.startButton');
    if (formSection) {
        formSection.remove();
    }

    // Function to dynamically load a script
    function loadScript(src, type = 'text/javascript') {
        const script = document.createElement('script');
        script.src = src;
        script.type = type;
        document.body.appendChild(script);
    }

    // Load required JavaScript files
    loadScript('/js/frontend/game.js', 'module');
    loadScript('/js/input/keyboard.js', 'module');
    loadScript('/js/networking/receive.js', 'module');
});



// let species = ["human", "elf"];

