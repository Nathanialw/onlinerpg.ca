'use strict'

import {Create_Map_Line, Create_MiniMap_Line, Draw_UI, Draw_Vision_Background} from '../graphics/graphics.js';
import {Set_Enemies, Set_Player, Set_Objects} from '../objects/objects.js';
import {characterInfo} from '../units/unitdef.js';

let mapDisplay = [];
let mapString = "";

let minimapDisplay = [];
let minimap = "                \
         j      \
         j      \
         j      \
         j      \
         j      \
         j      \
         j      \
d        j     d\
         j      \
         j      \
         j      \
         j      \
         j      \
         j      \
         j      ";

function Update_Map() {
    if (mapString.length > 0) {
        let mapSize = Math.sqrt(mapString.length) //this only really needs to updated when the vision is updated
        let updatedMap = "";

        for (let j = 0; j < mapSize; j++) {
            let start = j * mapSize;
            let end = start + mapSize;
            let mapLine = mapString.substring(start, end);
            console.log(mapLine);
            updatedMap += mapLine;
        }
        minimap = updatedMap;
        console.log(minimap);
        return true;
    }
    return false;
}

function Draw_Map() {
    //get postion of player
    //update the section of the map that the player is in
    let width = 16;
    if (Update_Map()) {
        for (let i = 0; i < width; i++) {
            let mapLine = minimap.substring(i * width, width);
            minimapDisplay[i] = Create_MiniMap_Line(mapLine, i);
        }
    }
    else {
        console.log("Map not updated");
    }
}   

// instead this function should create a blank map of . and it should get filled in in 8x8 chunks from the server as the player moves, 
export function Make_Map(serverMap, visionWidth) {
    console.log("Redrawing Game");
    Draw_UI(characterInfo);
    Draw_Vision_Background(visionWidth);
    mapString = "";
    for (let i = 0; i < visionWidth; i++) {
        // render lines of the map
        let mapLine = serverMap.substring(i * visionWidth, (i * visionWidth) + visionWidth); // 0, 13 -> 13, 26 -> 26, 39
        mapString += mapLine;
        mapDisplay[i] = Create_Map_Line(mapLine, i, visionWidth);
    }
    Draw_Map();
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
