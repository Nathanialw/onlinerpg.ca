'use strict'
import { Send_Web_Socket_Message } from './socket.js';


export function Set_Send_On_Map_Click_Listener(objectDisplay, x, y) {
    let message = "5" + x + y;

    objectDisplay.on('pointerdown', (event) => { 
        Send_Web_Socket_Message(message); 
        console.log("Click Message sent: ", message); 
    }); //query the server for the object data
}

export function Set_Send_On_Loot_Click_Listener(objectDisplay, i) {
    //send the index of the item in the loot array
    let message = "2" + i;

    objectDisplay.on('pointerdown', (event) => { 
        Send_Web_Socket_Message(message); 
        console.log("Click Message sent: ", message); 
    }); //query the server for the object data
}