'use strict'

import {Make_Map, Update_Map, Populate_Map} from '../map/map.js';
import {app, Close_Game} from '../frontend/game.js';
//import {websocket} from './socket.js';

let websocket;
let reconnectInterval = 1000; // 1 second

function createWebSocket() {
    websocket = new WebSocket("ws://www.onlinerpg.ca/ws");

    websocket.onopen = () => {
        console.log("WebSocket connection opened");
    };

    websocket.onclose = () => {
        console.log("WebSocket connection closed, attempting to reconnect...");
        setTimeout(() => {
            createWebSocket();
        }, reconnectInterval);
    };

    websocket.onerror = (error) => {
        console.error("WebSocket error:", error);
        websocket.close();
    };

    websocket.onmessage = (event) => {
        console.log("WebSocket message received:", event.data);
        // Handle incoming messages here
    };

    setInterval(() => {
        if (websocket.readyState === WebSocket.OPEN) {
            websocket.send(JSON.stringify({ event: "ping" }));
        }
    }, 2500);
}

createWebSocket();

export function socket() {
    if (websocket && websocket.readyState === WebSocket.OPEN) {
        return { websocket: websocket, isConnected: true };
    } else if (websocket && websocket.readyState === WebSocket.CONNECTING) {
        console.log("Connecting WebSocket...");
        return { websocket: websocket, isConnected: false };
    } else if (websocket && (websocket.readyState === WebSocket.CLOSING || websocket.readyState === WebSocket.CLOSED)) {
        console.log("Reconnecting WebSocket...");
        createWebSocket();
        return { websocket: websocket, isConnected: false };
    } else {
        createWebSocket();
        console.log("Reconnecting WebSocket...");
        return { websocket: websocket, isConnected: false };
    }
}

export function closeWebSocket() {
    if (websocket) {
        websocket.close();
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

socket().websocket.onclose = function(event) {
    Close_Game();
}