'use strict'

import {Create_Map_Line, Draw_UI, Draw_Vision_Background} from '../graphics/graphics.js';
import {Set_Enemies, Set_Player, Set_Objects} from '../objects/objects.js';
import {characterInfo} from '../units/unitdef.js';

let mapDisplay = [];


export let map = "                \
                \
                \
                \
                \
                \
                \
                \
                \
                \
                \
                \
                \
                \
                \
                ";

                
function Update_Map() {
    let mapSize = Math.sqrt(mapDisplay.length) //this only really needs to updated when the vision is updated
    for (let j = 0; j < mapSize; j++) {
        let mapLine = mapDisplay.substring(i, mapSize);
        map.substring(i, mapSize) = mapLine
    }
}

function Draw_Map() {
    //get postion of player
    //update the section of the map that the player is in
    Update_Map()

    for (let i = 0; i < map.length; i++) {
        // render lines of the map
        let mapLine = serverMap.substring(i * 16, 16);
        Create_Map_Line(mapLine, i, visionWidth);
    }
}   

// instead this function should create a blank map of . and it should get filled in in 8x8 chunks from the server as the player moves, 
export function Make_Map(serverMap, visionWidth) {
    console.log("Redrawing Game");
    Draw_UI(characterInfo);
    Draw_Vision_Background(visionWidth);
    for (let i = 0; i < visionWidth; i++) {
        // render lines of the map
        let mapLine = serverMap.substring(i * visionWidth, (i * visionWidth) + visionWidth); // 0, 13 -> 13, 26 -> 26, 39
        mapDisplay[i] = Create_Map_Line(mapLine, i, visionWidth);
    }
    Update_Map();
}

export function Map(data) {
    let visionWidth = parseInt(data.substring(0, 2), 10);
    let serverMap = data.substring(2);
    Make_Map(serverMap, visionWidth);
}

let Update = {
    "@": Set_Player,
    "g": Set_Enemies,
    "o": Set_Objects,
}

// I should use a seperate function to grab the correct substring from the unitOnMap string
export function Populate_Map(unitsOnMap) {
    for (let i = 0; i < unitsOnMap.length; i += 5) {        
        // let object = Create_Object(unitsOnMap[i], unitsOnMap.substring(i+1,i+3), unitsOnMap.substring(i+3,i+5));
	    // Update[unitsOnMap[i]](object)
        Update[unitsOnMap[i]](unitsOnMap.substring(i, i + 5));
    }
}
