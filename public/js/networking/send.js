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
        console.log("Click Message sent: ", message); 
    }); //query the server for the object data
}

export function Set_Send_On_Loot_Click_Listener(item, panel, i) {
    //send the index of the item in the loot array
    item.eventMode = 'static';
    item.cursor = 'pointer';

    let message = "2" + panel + i;

    item.on('pointerdown', (event) => { 
        Send_Web_Socket_Message(message); 
        console.log("Click Message sent: ", message); 
    }); //query the server for the object data
}