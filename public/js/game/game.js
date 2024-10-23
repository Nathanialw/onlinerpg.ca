'use strict'
import {Send_Web_Socket_Message} from "../networking/socket.js"
import {ReSend} from "../frontend/newGame.js"


//restart with all the same input stats
export function Restart(data) {
    Send_Web_Socket_Message("6")
    ReSend();
    //set proper html
}

//quit to main page
export function Quit(data) {
    //go back to start page
    Send_Web_Socket_Message("7")
    window.location.href = "https://www.onlineRPG.ca";
    //set proper html
}

