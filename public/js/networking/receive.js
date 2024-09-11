'use strict'

import {Make_Map, Populate_Map} from '../map/map.js';
//import {websocket} from './socket.js';
function CreateWebsocket() {
    return new WebSocket("ws://www.onlinerpg.ca/ws");
    setInterval(() => websocket.send(JSON.stringify({ event: "ping" })), 10000);
}
var websocket = CreateWebsocket();

export function socket() {
    if (websocket && websocket.readyState === WebSocket.OPEN) {
        return { websocket: websocket, isConnected: true };
    }
    else if (websocket && websocket.readyState === WebSocket.CONNECTING ){
        console.log("connecting websocket...")
        return { websocket: websocket, isConnected: false };
    }
    else {
        websocket = CreateWebsocket();
        console.log("reconnecting websocket")
        return { websocket: websocket, isConnected: false };
    }
}

function Message(data) {
    console.log(data)
}

function Map(data) {
    let mapWidth = parseInt(data.substring(0, 2), 10);
    let serverMap = data.substring(2);
    Make_Map(serverMap, mapWidth);
}

let Update = {
    0: Message,
    1: Map,
    2: Populate_Map,
}

socket().websocket.onmessage = function(event) {    
    if (event.data === 0) {
        return
    }

    let type = event.data[0];
    let data = event.data.substring(1);
    console.log(type, data)
    //need to use a hash map
    Update[type](data);
    
    
    //populate map on startup
    //on periodic update
      //update positions
      //update damage
      //get new chunk to emplace in map array
};
