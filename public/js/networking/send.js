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

    item.on('hover', (event) => { 
        let message;
        message = "2" + panel + "0" + i;
        
        console.log("message: ", message);
    }); 
}