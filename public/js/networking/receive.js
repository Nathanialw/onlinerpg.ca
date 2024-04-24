import {Make_Map, Populate_Map} from '../map/map.js';
var websocket = new WebSocket("ws://www.saycum.com/ws");

export function socket() {
    let promise = new Promise((resolve, reject) => {
	if (websocket.readyState === WebSocket.OPEN) {
	    resolve("socket open")
	}
	else if (websocket.readystate === WebSocket.Connecting ){
	    resolve("socket connecting")
	}
	else {
	    websocket = new WebSocket("ws://www.saycum.com/ws");
	    reject("new socket opened")
	}
    })
    //needs to wait for it to connect before it returns
    promise.then((message) => {
	console.log(message)
	return websocket
    }).catch((message) => {
	console.log(message)
	return websocket
    })
    
    return websocket
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

socket().onmessage = function(event) {    
    if (event.data === 0) {
        return
    }

    let type = event.data[0];
    let data = event.data.substring(1);

    //need to use a hash map
    Update[type](data);
    
    
    //populate map on startup
    //on periodic update
      //update positions
      //update damage
      //get new chunk to emplace in map array
};
