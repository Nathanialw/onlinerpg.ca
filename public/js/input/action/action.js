'use strict'

import {socket} from "../../networking/socket.js"

//up movement locally
//send movement to server
//recieve position from server
//replace local with server position of they aren't the same

export function Actions(keyName) {
    console.log("Move");
    let conn = socket()

    
    if (keyName === "Space") {
        // Move_Player(cell_size, 0);
        //move camera right
        if (conn.isConnected) {
            conn.websocket.send("0Space");       
        }
        //send to server
        return true;
    }
    return false;
}