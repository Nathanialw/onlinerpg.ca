'use strict'

import {Make_Map, Populate_Map} from '../map/map.js';
import {app} from '../frontend/game.js';
import {socket} from './socket.js';

function Message(data) {
    console.log(data)
}

function Map(data) {
    let visionWidth = parseInt(data.substring(0, 2), 10);
    let serverMap = data.substring(2);
    Make_Map(serverMap, visionWidth);
}

function Stats(data) {
    console.log(data)
}

function UpdatePositions(data) {
    console.log(data)
}

let Update = {
    0: Message,
    1: Map,
    2: Populate_Map,
    3: Map,
    4: Populate_Map,
    //3: Stats,
}

socket().websocket.onmessage = function(event) {    
    console.log("websocket");
    
    if (event.data === 0) {
        return
    }

    let type = event.data[0];
    let data = event.data.substring(1);
    console.log(type, data)
    //clear map
    if (type == 1 || type == 3) {
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
};
