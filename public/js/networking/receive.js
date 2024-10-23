'use strict'

import { Populate_Map } from '../map/map.js';
import { Parse_Game_Update } from '../frontend/ui.js';
import { UpdatePlayerInfo } from '../units/unitdef.js';
import { Get_Target_Stats_From_Server } from '../ui/gamePanels/targetStats.js';
import { OnReconnect } from '../frontend/newGame.js';
import { Send_Web_Socket_Message } from './socket.js';

function Message(data) {
    console.log(data)
}

function Reconnect(data) {
    console.log("Reconnected to server")
    //set proper html
    OnReconnect();
}

function Update_Inventory(data) {
    if (data === " ") {
        console.log("inventory is full")
        return
    }

    //zero out inventory
    //redraw inventory
    //redraw loot panel
}

function Update_Loot(data) {
    
}

function Update_Equipment(data) {
}

function Update_Minimap(data) {

}

function Update_Merchant_Panel(data) {

}

function Update_Building_Panel(data) {

}

function Update_Spellbook(data) {

}

function Update_(data) {

}


async function Resume(data) {
    //close connection
    const newGameButton = document.getElementById('newGame').remove();

    const resumeButton = document.createElement('button');
    resumeButton.id = 'exitGame';
    resumeButton.classList.add('btn', 'btn-center');
    resumeButton.textContent = 'Exit';        

    //append as adjecent sibling of newGameButton
    menuButtons.insertBefore(exitButton, newGameButton.nextSibling);

    const resumeGame = (event) => {
        console.log("Resuming game");  
    };
    resumeButton.addEventListener('click', resumeGame)


}




export let Update = {
    0: Message,
    1: Parse_Game_Update,
    2: Update_Inventory,
    3: UpdatePlayerInfo,
    4: Reconnect,
    5: Get_Target_Stats_From_Server,
    // 6: Restart,
    // 7: Quit,
    8: Resume,
}

//periodically check if the websocket has reconnected
//if it has, reset listener
//if it hasn't, keep checking


    