'use strict'

import { Game_Update } from '../frontend/ui.js';
import { UpdatePlayerInfo } from '../units/unitdef.js';
import { Get_Target_Stats_From_Server } from '../ui/gamePanels/targetStats.js';
import { OnReconnect } from '../frontend/newGame.js';
import { Send_Web_Socket_Message } from './socket.js';
import { Save_Item_Effect } from '../db/itemEffects.js';

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

function Resume_Game() {
    console.log("Resuming game");  
    Send_Web_Socket_Message("9")
}

async function Create_Resume_Btn(data) {
    //close connection
    const newGameButton = document.getElementById('newGame')
    const menuButtons = document.querySelector('.menuButtons');

    const resumeButton = document.createElement('button');
    resumeButton.id = 'resumeGame';
    resumeButton.classList.add('btn', 'btn-center');
    resumeButton.textContent = 'Continue';        

    //append as adjecent sibling of newGameButton
    menuButtons.insertBefore(resumeButton, newGameButton.nextSibling);
    
    resumeButton.addEventListener('click', Resume_Game)
}


export let Update = {
    0: Message,
    1: Game_Update,
    2: Update_Inventory,
    3: UpdatePlayerInfo,
    4: Reconnect,
    5: Get_Target_Stats_From_Server,
    // 6: Startup,
    // 7: Quit,
    8: Create_Resume_Btn,
    9: Save_Item_Effect,
}

//periodically check if the websocket has reconnected
//if it has, reset listener
//if it hasn't, keep checking


    