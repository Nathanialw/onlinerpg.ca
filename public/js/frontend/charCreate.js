import { createWebSocket, socket } from '/js/networking/socket.js';

document.addEventListener('DOMContentLoaded', () => {
    createWebSocket();

    for (let i = 0; i < species.length; i++) {
        document.getElementById(species[i]).addEventListener('click', (event) => {
            //highlight selected    
            console.log("species: ", species[i]);   
            for (let j = 0; j < species.length; j++) {
                if (j != i) {
                    document.getElementById(species[j]).style.backgroundColor = 'white';
                }
            }
            document.getElementById(species[i]).style.backgroundColor = 'yellow';
            race = species.get(species[i]);
        });
    }
});

let species = new Map();
species.set("human", 7);
species.set("elf", 4);

let name;
let gender;
let race = 0;
let unitClass;
let alignment;

//send data to server
function Send() {
    let conn = socket()
    
    //get data from form
    name = document.getElementById("name").value;
    
    gender = document.getElementById("gender").value;
    // let race = document.getElementById("race").value;
    unitClass = document.getElementById("class").value;
    alignment = document.getElementById("alignment").value;

    if (conn.isConnected) {
        conn.websocket.send("3" + name + gender + race + unitClass + alignment);       
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

