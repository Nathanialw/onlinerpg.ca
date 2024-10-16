'use strict'
import { Clear_Sprite_Array, Draw_Main_Menu_Icons, mainMenuSprites } from '../graphics/graphics.js';
import { Send_Web_Socket_Message } from '../networking/socket.js';


//STATIC MENUS

//create menu button sprite
//add event listener
//send message to server on click

function Options() {console.log("Options()")}
function Graphics() {console.log("Graphics()")}
function Sound() {console.log("Sound()")}
function New_Game() {console.log("New_Game()")}
function Exit() {console.log("Exit()")}

const functions = [
    Options,    //open options menu
    Graphics,   //open graphics menu
    Sound,      //open sound menu
    New_Game,   //start new game
    Exit,       //exit game
]

let set = false;

export function  Init_Main_Menu() { //set listers on the sprites stored
    for (let i = 0; i < mainMenuSprites.length; i++) {
        Set_Send_On_Menu_Click_Listener(button, functions[i]);
    }
}

export async function Draw_Main_Menu() {
    // Clear_Sprite_Array(mainMenuSprites);

    for (let i = 0; i < mainMenuSprites.length; i++) {
        let button = await Draw_Main_Menu_Icons(mainMenuSprites, i, 4.5)           
        
        if (!set) { //set listers only once
            Set_Send_On_Menu_Click_Listener(button, functions[i]);
            if (i == mainMenuSprites.length - 1) {
                set = true;
            }
        }
    }
}


function Set_Send_On_Menu_Click_Listener(item, action) {
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
        console.log("Left mouse button clicked on item, open conext menu to decide action");
        // Optionally, you can handle right mouse button click event
        action();
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