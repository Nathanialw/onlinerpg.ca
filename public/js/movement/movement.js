'use strict'

import {socket} from "../networking/receive.js"
import {Move_Player} from "../objects/objects.js"
import { sendMessage } from "../networking/send.js";
const cell_size = 24;

//up movement locally
//send movement to server
//recieve position from server
//replace local with server position of they aren't the same

function Move(keyName) {
    console.log("Move");
    let conn = socket()
    
    if (keyName === "w") {
        Move_Player(0, -cell_size);
        //move camera up
        sendMessage("w");
        if (conn.isConnected) {
            conn.websocket.send("1w");       
        }
        //send to server
        return true;
    }
    
    else if (keyName === "a") {
        Move_Player(-cell_size, 0);
        //move camera left
        sendMessage("a");
        if (conn.isConnected) {
            conn.websocket.send("1a");       
        }
        //send to server
        return true;
    }
    
    else if (keyName === "s") {
        Move_Player(0, cell_size)
        //move camera down
        sendMessage("s");
        if (conn.isConnected) {
            conn.websocket.send("1s");       
        }
        //send to server
        return true;
    }
    
    else if (keyName === "d") {
        Move_Player(cell_size, 0);
        //move camera right
        sendMessage("d");
        if (conn.isConnected) {
            conn.websocket.send("1d");       
        }
        //send to server
        return true;
    }
    return false;
}

export {Move}
