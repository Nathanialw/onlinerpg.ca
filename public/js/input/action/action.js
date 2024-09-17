'use strict'

import {socket} from "../../networking/socket.js"

//up movement locally
//send movement to server
//recieve position from server
//replace local with server position of they aren't the same

export function Actions(keyName) {
    console.log("Enter key pressed");
    let conn = socket() 
    
    if (conn.isConnected) {
        conn.websocket.send("1");       
    }    
}