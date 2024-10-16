'use strict'
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

    
    item.on('pointerdown', (event) => { 
        console.log("Pointer Down: ", message);        
    }); 

    item.on('pointerover', (event) => { 
        let message = "2" + panel + "0" + i;
        console.log("Hover message: ", message);
        // Optionally, you can send a message on hover
        // Send_Web_Socket_Message(message); 
    });

    item.on('pointerout', (event) => { 
        console.log("Pointer out of item");
        // Optionally, you can handle pointer out event
    });

    //TOO SPAMMY
    // item.on('pointermove', (event) => { 
    //     console.log("Pointer moving over item");
    //     // Optionally, you can handle pointer move event
    // });

    item.on('pointertap', (event) => { 
        console.log("Item tapped");
        // Optionally, you can handle pointer tap event
    });

    // item.on('rightdown', (event) => { 
    //     console.log("Right mouse button down on item");
    //     // Optionally, you can handle right mouse button down event
    // });

















    item.on('rightup', (event) => { 
        console.log("Right mouse button up on item");
        // Optionally, you can handle right mouse button up event
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


    
    // item.on('rightdown', (event) => { 
    //     console.log("Right mouse button clicked on item");
    //     // Prevent the context menu
    //     event.preventDefault();
    //     event.stopPropagation();
    //     console.log("Context menu prevented");
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