'use strict'

import {Populate_Map} from '../map/map.js';
import {Map} from '../frontend/ui.js';
import {Draw_UI} from '../graphics/graphics.js';

import {app} from '../graphics/graphics.js';
import {socket} from './socket.js';
import {UpdatePlayerInfo} from '../units/unitdef.js';
import { Get_Target_Stats_From_Server } from '../frontend/stats.js';


function Message(data) {
    console.log(data)
}

let Update = {
    0: Message,
    1: Map,
    2: Populate_Map,
    3: UpdatePlayerInfo,
    5: Get_Target_Stats_From_Server,
}

socket().websocket.onmessage = function(event) {    
    console.log(event.data)
    
    if (event.data === 0) {
        return
    }

    let type = event.data[0];
    let data = event.data.substring(1);
    console.log(type, data)
    // if empty string
    if (data.length == 0) {
        console.log("received empty string")
        return
    }
    //clear map
    if (type == 1) {
        console.log("Clearing map");
        app.stage.removeChildren();
    }
    //need to use a hash map
    Update[type](data);
    
    
    //populate map on startup
    //on periodic update
      //update positions
      //update damage
      //get new chunk to emplace in map array
     Draw_UI();

};
