'use strict'
import {Send_Web_Socket_Message} from "../networking/socket.js"


function Spell(keyName) {
    console.log("spell", keyName)
}

let actionBar = {
    1: Spell,
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