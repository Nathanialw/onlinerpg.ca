'use strict'
import {Send_Web_Socket_Message, socket} from "../networking/socket.js"


function Spell(keyName) {
    console.log("spell", keyName)
    let conn = socket()
    console.log("sending key", keyName)
    if (conn.isConnected) {
        conn.websocket.send("1" + keyName);
        // conn.websocket.send("1".concat(keyName));
        return true;       
    }
    return false;
}


let actionBar = {
    q: Spell,
    e: Spell,
    r: Spell,
    f: Spell,

    2: Spell,
    3: Spell,
    4: Spell,
    5: Spell,
    6: Spell,
    7: Spell,
    8: Spell,
    9: Spell,
    0: Spell,
}


export function Action_Bar(keyName) {
    actionBar[keyName](keyName)
}