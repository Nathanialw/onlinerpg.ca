'use strict'
import { Draw_Tooltip, Remove_Tooltip } from '../frontend/tooltip.js';
import { Send_Web_Socket_Message } from './socket.js';


export function Set_Send_On_Map_Click_Listener(objectDisplay, x, y) {
    if  (x < 10) {
        x = "0" + x;
    }
    if  (y < 10) {
        y = "0" + y;
    }
    objectDisplay.eventMode = 'static';
    objectDisplay.cursor = 'pointer';

    let message = "5" + x + y;

    objectDisplay.on('pointerdown', (event) => { 
        Send_Web_Socket_Message(message); 
    }); 
}


export function Set_Send_On_Loot_Click_Listener(item, panel, i) {
    //send the index of the item in the loot array
    item.eventMode = 'static';
    item.cursor = 'pointer';

    item.on('mouseover', async (event) => { 
        //display a sprite that shows the item stats in a frame
        // Get mouse position
        const mousePosition = event.data.global;
        console.log("Mouse position (over):", mousePosition);
        await Draw_Tooltip(mousePosition.x, mousePosition.y);
    });

    item.on('mouseout', (event) => { 
        //remove the sprite that shows the item stats in a frame from the stage
        Remove_Tooltip();
    }); 

    //
    item.on('mousedown', (event) => { 
        console.log("Left mouse button clicked on item, open conext menu to decide action");
        // Optionally, you can handle right mouse button click event

    });

    //DEKTOP ONLY
    item.on('rightclick', (event) => { 
        console.log("Right mouse button clicked on item");
        // Optionally, you can handle right mouse button click event
        let message;
        //if ctrl clicked
        if (event.ctrlKey) {
            message = "2" + panel + "c" + i;
        }
        //if shift clicked
        else if (event.shiftKey) {
            message = "2" + panel + "s" + i;
        }
        //if alt clicked
        else if (event.altKey) {
            message = "2" + panel + "a" + i;
        }    
        else {
            message = "2" + panel + "0" + i;
        }  
        
        console.log("message: ", message);
        Send_Web_Socket_Message(message); 
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