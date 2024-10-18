import { createWebSocket, socket } from '/js/networking/socket.js';
import { classes } from '/js/frontend/classes.js';
import { Init_Title, Music_Play } from '../sound/sound.js';

document.addEventListener('DOMContentLoaded', () => {
    Init_Title();
    Music_Play("title");

    Buttons(races);
    Buttons(genders);
    Buttons(unitClasses);
    Buttons(alignments);

    document.getElementById("Human").style.backgroundColor = getComputedStyle(document.documentElement).getPropertyValue('--primary-500')
    document.getElementById("Male").style.backgroundColor = getComputedStyle(document.documentElement).getPropertyValue('--primary-500')
    document.getElementById("Fighter").style.backgroundColor = getComputedStyle(document.documentElement).getPropertyValue('--primary-500')
    document.getElementById("Good").style.backgroundColor = getComputedStyle(document.documentElement).getPropertyValue('--primary-500')  


    document.getElementById('hero-class').value = classes.get(races.value + genders.value + unitClasses.value + alignments.value);

    document.getElementById('name').addEventListener('input', function() {
        const nameInput = document.getElementById('name');
        if (nameInput.value.length >= 3) {
            nameInput.classList.remove('error'); // Remove error class if valid
        }
    });

    updateHeroClass()
})

function Buttons(Option) {
    Option.options.forEach((value, key) => {
        document.getElementById(key).addEventListener('click', (event) => {            
            //highlight selected    
            document.getElementById(key).style.backgroundColor = getComputedStyle(document.documentElement).getPropertyValue('--primary-500');
            ;
            Option.value = value;
            //remove highlight from other
            Option.options.forEach((value, key) => {
                if (key != event.target.id) {
                    document.getElementById(key).style.backgroundColor = getComputedStyle(document.documentElement).getPropertyValue('--black-800"');
                }
            });
            updateHeroClass() 
        })
    });
}



let races = {
    options: new Map([["Human", "7"],["Elf", "4"]]),
    value: "7"
}

let genders = {
    options: new Map([["Male", "0"],["Female", "1"]]),
    value: '0'
}

let unitClasses = {
    options:  new Map([["Fighter", "0"],["Mystic", "1"]]),
    value: '0'
}

let alignments = {
    options: new Map([["Good", "0"],["Neutral", "1"],["Evil", '2']]),
    value: '0'
}

function updateHeroClass() {
    const heroClass = document.getElementById('hero-class');

    const key = races.value + genders.value + unitClasses.value + alignments.value;
    heroClass.textContent = classes.get(key) || 'Unknown Class'; // Default to 'Unknown Class' if key is not found
}

let name;
let gender;
let race;
let unitClass;
let alignment;

//send data to server
function Send() {
    let conn = socket()
    
    //get data from form
    name = document.getElementById("name").value;
    
    const nameInput = document.querySelector('.nameInput');
    if (nameInput) {
        nameInput.remove();
    }
    
    gender = genders.value;
    race = races.value;
    unitClass = unitClasses.value;
    alignment = alignments.value;

    if (conn.isConnected) {
        conn.websocket.send("3" + name + gender + race + unitClass + alignment);       
        console.log("char create Data sent to server")
    }
    else {
        console.log("Error: Server is not connected")
    }    
}

export function ReSend() {
    let conn = socket()
    
    if (conn.isConnected) {
        conn.websocket.send("3" + name + gender + race + unitClass + alignment);       
        console.log("char create Data sent to server")
    }
    else {
        console.log("Error: Server is not connected")
    }    
}

function Remove_Elements() {
    const description = document.querySelector('.wrapper');
    if (description) {
        description.remove();
    }

    const options = document.querySelector('.options-container');
    if (options) {
        options.remove();
    }

     const className = document.querySelector('.hero-wrapper');
    if (className) {
        className.remove();
    }

    const nameInput = document.querySelector('.nameInput');
    if (nameInput) {
        nameInput.remove();
    }
        
     const btnSection = document.querySelector('.startButton');
    if (btnSection) {
        btnSection.remove();
    }
}

function Load_Scripts() {
    // Function to dynamically load a script
    function loadScript(src, type = 'text/javascript') {
        const script = document.createElement('script');
        script.src = src;
        script.type = type;
        document.body.appendChild(script);
    }
    
    // Load required JavaScript files
    loadScript('/js/frontend/game.js', 'module');
    loadScript('/js/networking/receive.js', 'module');
    loadScript('/js/input/keyboard.js', 'module');
    loadScript('/js/graphics/scale.js', 'module');  
    loadScript('/js/db/db.js', 'module');  
}

function Set_Canvas() {
    const canvas = document.querySelector('.canvasContainer');
    if (canvas) {
        canvas.style.height = 'calc(100vh - 3.5rem - 125px)';
    }
}

document.getElementById('startGame').addEventListener('click', async (event) => {
    const nameInput = document.getElementById('name');
    const nameError = document.getElementById('nameError');

    if (nameInput.value.length >= 3) {
        nameInput.classList.remove('error'); // Remove error class if valid
        nameError.style.display = 'none'; // Hide error message

        try {
            await createWebSocket();
            Set_Canvas();
            Load_Scripts();
            Send();
            Remove_Elements();
        } catch (error) {
            console.error("Failed to establish WebSocket connection:", error);
        }
    } else {
        event.preventDefault(); // Prevent form submission
        nameInput.classList.add('error'); // Add error class to input
        nameError.style.display = 'block'; // Show error message
    }
});

export function OnReconnect() {
    Set_Canvas();
    Load_Scripts();
    Remove_Elements();
}

// let species = ["human", "elf"];

