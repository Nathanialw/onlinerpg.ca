import { socket } from '/js/networking/socket.js';
import { classes } from '/js/frontend/classes.js';

// add html to newGame.html

{/* <section class="options-container">
    <article class='options'>    
        <ul>
            <li class="option"><button id="Human" class='btn btn-block'>Human</button></li>
            <li class="option"><button id="Elf" class='btn btn-block'>Elf</button></li>
            <!-- <li><button id="Orc" class='btn btn-submit'>Orc</button></li> -->
            <!-- <li><button id="Dwarf" class='btn btn-submit'>Dwarf</button></li> -->
            <!-- <li><button id="Goblin" class='btn btn-submit'>Goblin</button></li> -->
        </ul>

        <ul>
            <li class="option"><button id="Male" class='btn btn-block'>Male</button></li>
            <li class="option"><button id="Female" class='btn btn-block'>Female</button></li>
        </ul>

        <ul>
            <li class="option"><button id="Fighter" class='btn btn-block'>Fighter</button></li>
            <li class="option"><button id="Mystic" class='btn btn-block'>Mystic</button></li>
        </ul>

        <ul>
            <li class="option"><button id="Good" class='btn btn-block'>Good</button></li>
            <li class="option"><button id="Neutral" class='btn btn-block'>Neutral</button></li>
            <li class="option"><button id="Evil" class='btn btn-block'>Evil</button></li>
        </ul>
    </section>
</section>

<section class="hero-wrapper">
    <h1 id="hero-class" class="hero-class"></h1>
</section>

<section class='nameInput'>
    <form method='POST' id="myForm">
        <input class="form-input form-row" type="text" id="name" name="name" value="" required minlength="3" maxlength="20" autocomplete="off">
        <br> 
    </form>
</section>

<section class='startButton button'>
    <button id="startGame" class='btn btn-center'>Start Game</button>
    <br> 
    <div id="nameError" class="error-message" style="color: red; display: none;">Name must be at least 3 characters long.</div>
    <div id="loading-text" class="loading-message" style="color: white; display: none;">Loading...</div>
</section> */}

async function Init_Char_Select() {
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
        const nameError = document.getElementById('nameError');
    
        if (nameInput.value.length >= minNameLength && nameInput.value.length <= maxNameLength) {
            nameInput.classList.remove('error'); // Remove error class if valid
            nameError.style.display = 'none'; // Hide error message
        }
    });

    updateHeroClass()
}

const minNameLength = 2;
const maxNameLength = 20;


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
        console.log("char create Data sent to server:", "3" + name + gender + race + unitClass + alignment)
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


export function character_Create() {
    const content = document.getElementById('chracterCreate');

    // Create options container
    const optionsContainer = document.createElement('section');
    optionsContainer.classList.add('options-container');

    const optionsArticle = document.createElement('article');
    optionsArticle.classList.add('options');
    optionsContainer.appendChild(optionsArticle);

    // Create options lists
    const races = ['Human', 'Elf'];
    const genders = ['Male', 'Female'];
    const classes = ['Fighter', 'Mystic'];
    const alignments = ['Good', 'Neutral', 'Evil'];

    const createOptionList = (options) => {
        const ul = document.createElement('ul');
        options.forEach(option => {
            const li = document.createElement('li');
            li.classList.add('option');
            const button = document.createElement('button');
            button.id = option;
            button.classList.add('btn', 'btn-block');
            button.textContent = option;
            li.appendChild(button);
            ul.appendChild(li);
        });
        return ul;
    };

    optionsArticle.appendChild(createOptionList(races));
    optionsArticle.appendChild(createOptionList(genders));
    optionsArticle.appendChild(createOptionList(classes));
    optionsArticle.appendChild(createOptionList(alignments));

    content.appendChild(optionsContainer);

    // Create hero wrapper
    const heroWrapper = document.createElement('section');
    heroWrapper.classList.add('hero-wrapper');
    const heroClass = document.createElement('h1');
    heroClass.id = 'hero-class';
    heroClass.classList.add('hero-class');
    heroWrapper.appendChild(heroClass);
    content.appendChild(heroWrapper);

    // Create name input section
    const nameInputSection = document.createElement('section');
    nameInputSection.classList.add('nameInput');
    const form = document.createElement('form');
    form.method = 'POST';
    form.id = 'myForm';
    const input = document.createElement('input');
    input.classList.add('form-input', 'form-row');
    input.type = 'text';
    input.id = 'name';
    input.name = 'name';
    input.required = true;
    input.minLength = 3;
    input.maxLength = 20;
    input.autocomplete = 'off';
    form.appendChild(input);
    nameInputSection.appendChild(form);
    content.appendChild(nameInputSection);

    // Create start button section
    const startButtonSection = document.createElement('section');
    startButtonSection.classList.add('startButton', 'button');
    const startButton = document.createElement('button');
    startButton.id = 'startGame';
    startButton.classList.add('btn', 'btn-center');
    startButton.textContent = 'Start Game';
    startButtonSection.appendChild(startButton);

    const nameError = document.createElement('div');
    nameError.id = 'nameError';
    nameError.classList.add('error-message');
    nameError.textContent = 'Name must be at least 3 characters long.';
    nameError.style.color = 'red';
    nameError.style.display = 'none';
    startButtonSection.appendChild(nameError);

    const loadingText = document.createElement('div');
    loadingText.id = 'loading-text';
    loadingText.classList.add('loading-message');
    loadingText.textContent = 'Loading...';
    loadingText.style.color = 'white';
    loadingText.style.display = 'none';
    startButtonSection.appendChild(loadingText);

    content.appendChild(startButtonSection);

    //create an exit button


    // document.getElementById('startGame')
    startButtonSection.addEventListener('click', async (event) => {
    const nameInput = document.getElementById('name');
    const nameError = document.getElementById('nameError');
    const loadingText = document.getElementById('loading-text');
    
    if (nameInput.value.length < minNameLength || nameInput.value.length > maxNameLength) {
        event.preventDefault(); // Prevent form submission
        nameInput.classList.add('error'); // Add error class to input
        nameError.style.display = 'block'; // Show error message
        if (nameInput.value.length < minNameLength) {
            nameError.textContent = `Name must be at least ${minNameLength} characters long.`;
        } else {
            nameError.textContent = `Name must be no more than ${maxNameLength} characters long.`;
        }
        
    } else {
        loadingText.classList.add('loading-text'); // Add error class to input
        loadingText.style.color = 'white';
        loadingText.textContent = `Connecting...`;
        loadingText.style.display = 'block'; // Show error message
        try {
            Set_Canvas();
            Load_Scripts();
            Send();
            Remove_Elements();
        } catch (error) {
            console.error("Failed to load game world:", error);
        }  
    }    


    });
    
    Init_Char_Select()
};

export async function OnReconnect() {
    Set_Canvas();
    Load_Scripts();
    Remove_Elements();
}