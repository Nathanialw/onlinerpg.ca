'use strict'
import { Draw_Tooltip, Remove_Tooltip } from '../frontend/tooltip.js';
import { Send_Web_Socket_Message } from './socket.js';
import { Set_Cursor_Hover } from '../input/mouse.js';
import { Draw_Equipment_Icons } from '../graphics/graphics.js';
import { app } from '../graphics/graphics.js';

//query map object
export function Set_Send_On_Map_Click_Listener(objectDisplay, x, y) {
    if  (x < 10) {
        x = "0" + x;
    }
    if  (y < 10) {
        y = "0" + y;
    }

    Set_Cursor_Hover(objectDisplay, 'enemy');

    let message = "5" + x + y;

    objectDisplay.on('pointerdown', (event) => { 
        Send_Web_Socket_Message(message); 
    }); 
}

let hover = 'assets/graphics/ui/equipment/item_hover_effect.png';
let highlight;

export function Remove_Highlight() {
    if (highlight) {
        app.stage.removeChild(highlight);
        highlight = null;
    }
}

export function Set_Send_On_Loot_Click_Listener(item, panel, i, itemID, inv, iconSize) {
    //send the index of the item in the loot array
    Set_Cursor_Hover(item, 'neutral');

    item.on('mouseover', async (event) => { 
        const mousePosition = event.data.global;

        //toggle the tooltip as drawable / update the tooltip 
        highlight = await inv(hover, i, iconSize) //border
        await Draw_Tooltip(mousePosition.x, mousePosition.y, itemID);
    });

    item.on('mouseout', (event) => { 
        //toggle the tooltip as not drawable
        Remove_Highlight();
        Remove_Tooltip();
    }); 

    //
    item.on('mousedown', (event) => { 
        // console.log("Left mouse button clicked on item, open conext menu to decide action");
        // Optionally, you can handle right mouse button click event

    });

    //DESKTOP ONLY
    item.on('rightclick', (event) => { 
        // console.log("Right mouse button clicked on item");
        // Optionally, you can handle right mouse button click event
        let message;
        //if ctrl clicked
        if (event.ctrlKey) {
            //drop sound
            message = "2" + panel + "c " + i;
        }
        //if shift clicked
        else if (event.shiftKey) {
            message = "2" + panel + "s " + i;
        }
        //if alt clicked
        else if (event.altKey) {
            //equip sound
            message = "2" + panel + "a " + i;
        }    
        else {
            message = "2" + panel + "0 " + i;
        }  
        
        //equip sound
        // console.log("message: ", message);
        Send_Web_Socket_Message(message); 
    });
}

export function Set_Send_On_Loot_Click_Listener_inv(item, panel, i, bag, itemID, inv) {
    //send the index of the item in the loot array
    Set_Cursor_Hover(item, 'neutral');

    item.on('mouseover', async (event) => { 
        const mousePosition = event.data.global;

        //toggle the tooltip as drawable / update the tooltip 
        highlight = await inv(hover, i, bag, 3.5) //border
        await Draw_Tooltip(mousePosition.x, mousePosition.y, itemID);
    });

    item.on('mouseout', (event) => { 
        //toggle the tooltip as not drawable
        Remove_Highlight();
        Remove_Tooltip();
    }); 

    //
    item.on('mousedown', (event) => { 
        // console.log("Left mouse button clicked on item, open conext menu to decide action");
        // Optionally, you can handle right mouse button click event

    });

    //DESKTOP ONLY
    item.on('rightclick', (event) => { 
        // console.log("Right mouse button clicked on item");
        // Optionally, you can handle right mouse button click event
        let message;
        //if ctrl clicked
        if (event.ctrlKey) {
            //drop sound
            message = "2" + panel + "c" + bag + i;
        }
        //if shift clicked
        else if (event.shiftKey) {
            message = "2" + panel + "s" + bag + i;
        }
        //if alt clicked
        else if (event.altKey) {
            //equip sound
            message = "2" + panel + "a" + bag + i;
        }    
        else {
            message = "2" + panel + "0" + bag + i;
        }  
        
        //equip sound
        // console.log("message: ", message);
        Send_Web_Socket_Message(message); 
    });
}


export function Set_Send_On_Loot_Click_Listener_Loot(item, panel, i, itemID, inv) {
    //send the index of the item in the loot array
    Set_Cursor_Hover(item, 'neutral');

    item.on('mouseover', async (event) => { 
        const mousePosition = event.data.global;

        //toggle the tooltip as drawable / update the tooltip 
        highlight = await inv(hover, i, 2.5, "") //border
        await Draw_Tooltip(mousePosition.x, mousePosition.y, itemID);
    });

    item.on('mouseout', (event) => { 
        //toggle the tooltip as not drawable
        Remove_Highlight();
        Remove_Tooltip();
    }); 

    //
    item.on('mousedown', (event) => { 
        // console.log("Left mouse button clicked on item, open conext menu to decide action");
        // Optionally, you can handle right mouse button click event

    });

    //DESKTOP ONLY
    item.on('rightclick', (event) => { 
        // console.log("Right mouse button clicked on item");
        // Optionally, you can handle right mouse button click event
        let message;
        //if ctrl clicked
        if (event.ctrlKey) {
            //drop sound
            message = "2" + panel + "c " + i;
        }
        //if shift clicked
        else if (event.shiftKey) {
            message = "2" + panel + "s " + i;
        }
        //if alt clicked
        else if (event.altKey) {
            //equip sound
            message = "2" + panel + "a " + i;
        }    
        else {
            message = "2" + panel + "0 " + i;
        }  
        
        //equip sound
        // console.log("message: ", message);
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