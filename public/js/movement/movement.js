'use strict'

import {socket} from "../networking/socket.js"

//up movement locally
//send movement to server
//recieve position from server
//replace local with server position of they aren't the same

export function Move(keyName) {
    let conn = socket()
    if (conn.isConnected) {
        conn.websocket.send("1" + keyName);
        // conn.websocket.send("1".concat(keyName));
        return true;       
    }
    return false;
}

