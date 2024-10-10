'use strict'

import { Populate_Map } from '../map/map.js';
import { Map } from '../frontend/ui.js';
import { UpdatePlayerInfo } from '../units/unitdef.js';
import { Get_Target_Stats_From_Server } from '../frontend/stats.js';
import { OnReconnect } from '../frontend/charCreate.js';

function Message(data) {
    console.log(data)
}

function Reconnect(data) {
    console.log("Reconnected to server")
    //set proper html
    OnReconnect();
}

export let Update = {
    0: Message,
    1: Map,
    2: Populate_Map,
    3: UpdatePlayerInfo,
    4: Reconnect,
    5: Get_Target_Stats_From_Server,
}

//periodically check if the websocket has reconnected
//if it has, reset listener
//if it hasn't, keep checking


    