import {MakeMap} from './index.js';
export var socket =  new WebSocket("ws://www.saycum.com/ws");

export let map = [];

// for testing start
// let serverMap = "\
// ####################\
// #......H...........#\
// #..................#\
// #..................#\
// #..................#\
// #..................#\
// #..................#\
// #..................#\
// #..................#\
// #.............g....#\
// #...............g..#\
// #..................#\
// #..................#\
// #g.................#\
// #..................#\
// #..................#\
// #..................#\
// #..................#\
// #....g.g.........o.#\
// ####################";
// let mapWidth = 20;
// MakeMap(serverMap, mapWidth);
// for testing end

socket.onmessage = function(event) {    
    if (event.data === 0) {
        return
    }

    let type = event.data[0];
    let data = event.data.substring(1);
    
    //message
    if (type === "0") {
        console.log(data);
    }
    
    //map
    else if (type === "1") {
        let mapWidth = parseInt(data.substring(0, 2), 10);
        let serverMap = data.substring(2);
        MakeMap(serverMap, mapWidth);
    }

    //update units on map position
    else if (type === "2") {
        let units = event.data;
    }
    
};
