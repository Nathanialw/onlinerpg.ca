'use strict'
import { Clear_Sprite_Array, Draw_Main_Menu_Icons, gameMenuSprites } from '../graphics/graphics.js';
import { Send_Web_Socket_Message } from '../networking/socket.js';

//STATIC MENUS

//create menu button sprite
//add event listener
//send message to server on click

export let gamePanelIndex = 0;

function Target(i) {
    gamePanelIndex = i;
}
function Spellbook(i) {
    gamePanelIndex = i;
}
function Combat_Log(i) {
    gamePanelIndex = i;
}
function Minimap(i) {
    gamePanelIndex = i;
}
function Crafting(i) {
    gamePanelIndex = i;
}

const functions = [
    Target,     // target stats  
    Spellbook,  // spellbook
    Combat_Log, // extended combat log
    Minimap,    // minimap  
    Crafting,       // 
]

let set = false;

export function  Init_Game_Menu() { //set listers on the sprites stored
    for (let i = 0; i < gameMenuSprites.length; i++) {
        Set_Send_On_Menu_Click_Listener(button, functions[i]);
    }
}

export async function Draw_Game_Menu() {
    // Clear_Sprite_Array(mainMenuSprites);
    for (let i = 0; i < gameMenuSprites.length; i++) {
        let button = await Draw_Main_Menu_Icons(gameMenuSprites, i, 71.4)           
        
        if (!set) { //set listers only once
            Set_Send_On_Menu_Click_Listener(button, functions[i], i);
            if (i == gameMenuSprites.length - 1) {
                set = true;
            }
        }
    }
}


function Set_Send_On_Menu_Click_Listener(item, action, index) {
    //send the index of the item in the loot array
    item.eventMode = 'static';
    item.cursor = 'pointer';

    item.on('mouseover', async (event) => { 
        //display a sprite that shows the item stats in a frame
        // Get mouse position
        const mousePosition = event.data.global;
        console.log("Mouse position (over):", mousePosition);
    });

    item.on('mouseout', (event) => { 
        //remove the sprite that shows the item stats in a frame from the stage
    }); 

    //
    item.on('mousedown', (event) => { 
        console.log("change game panel to: ", index);
        // Optionally, you can handle right mouse button click event
        functions(index);        
        // Send_Web_Socket_Message(message); 
    });

    //DEKTOP ONLY
    // item.on('rightclick', (event) => { 
    //     console.log("Right mouse button clicked on item");
    //     // Optionally, you can handle right mouse button click event
    //     let message;
    //     //if ctrl clicked
    //     if (event.ctrlKey) {
    //     }
    //     //if shift clicked
    //     else if (event.shiftKey) {
    //     }
    //     //if alt clicked
    //     else if (event.altKey) {
    //     }    
    //     else {
    //     }  
        
    //     console.log("message: ", message);
    //     Send_Web_Socket_Message(message); 
    // });
}

// In PIXI.js, you can use various mouse and pointer event listeners to handle different types of user interactions. Here are some common event listeners you can use:

// pointerdown:         Triggered when a pointer (mouse, touch, pen) is pressed down.
// pointerup:           Triggered when a pointer is released.
// pointerupoutside:    Triggered when a pointer is released outside the element.
// pointermove:         Triggered when a pointer moves over the element.
// pointerover:         Triggered when a pointer moves onto the element.
// pointerout:          Triggered when a pointer moves out of the element.
// pointertap:          Triggered when a pointer is tapped (quick press and release).
// rightdown:           Triggered when the right mouse button is pressed down.
// rightup:             Triggered when the right mouse button is released.
// rightupoutside:      Triggered when the right mouse button is released outside the element.
// mousedown:           Triggered when the left mouse button is pressed down.
// mouseup:             Triggered when the left mouse button is released.
// mouseupoutside:      Triggered when the left mouse button is released outside the element.
// mousemove:           Triggered when the mouse moves over the element.
// mouseover:           Triggered when the mouse moves onto the element.
// mouseout:            Triggered when the mouse moves out of the element.
// click:               Triggered when the left mouse button is clicked.
// rightclick:          Triggered when the right mouse button is clicked.