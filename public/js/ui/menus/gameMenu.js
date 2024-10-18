'use strict'
import { Draw_Menu_Icons, gameMenuSprites, buttonHover, buttonNormal } from '../../graphics/graphics.js';
import { Update_Screen } from '../../frontend/ui.js';

//STATIC MENUS

//create menu button sprite
//add event listener
//send message to server on click

export let gamePanelIndex = 0;

export function Set_Game_Panel_Index(index) {
    gamePanelIndex = index;
}

const text = [
    'Target',       //exit game
    'Spells',    //open options menu
    'Log',      //open sound menu
    'Map',   //start new game
    'Craft',   //open graphics menu
]


// export function  Init_Game_Menu() { //set listers on the sprites stored
//     for (let i = 0; i < gameMenuSprites.length; i++) {
    //         Set_Send_On_Menu_Click_Listener(button, i);
    //     }
    // }
    
let set = false;
let hover = false;
export async function Draw_Game_Menu() {
    // Clear_Sprite_Array(mainMenuSprites);
    for (let i = 0; i < gameMenuSprites.length; i++) {
        let button = await Draw_Menu_Icons(gameMenuSprites, i, 71.4, hover, text[i])           
        
        if (!set) { //set listers only once
            Set_Send_On_Menu_Click_Listener(button, i,);
            if (i == gameMenuSprites.length - 1) {
                set = true;
            }
        }
    }
}

// function onButtonDown()
// {
//     this.texture = buttonHover;
// }

function Set_Send_On_Menu_Click_Listener(item, index) {
    //send the index of the item in the loot array
    item.eventMode = 'static';
    item.cursor = 'hover';

    item.on('mouseover', (event) => { 
        //remove the sprite that shows the item stats in a frame from the stage
        hover = true;
        item.texture = buttonHover;
    }); 

    item.on('mouseout', (event) => { 
        //remove the sprite that shows the item stats in a frame from the stage
        hover = false;
        item.texture = buttonNormal;

    }); 

    //
    item.on('mousedown', (event) => { 
        console.log("change game panel to: ", index);
        
        

        Set_Game_Panel_Index(index);
        Update_Screen();
    });
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