'use strict'

import {cellSize, Create_Map_Line, Create_MiniMap_Line, Draw_UI, Draw_Vision_Background} from '../graphics/graphics.js';
import {Set_Enemies, Set_Player, Set_Objects} from '../objects/objects.js';
import {characterInfo} from '../units/unitdef.js';

let mapDisplay = [];
let mapString = "";

let minimapDisplay = [];
let minimap = "";
let minimap2d = [[]];
let mapHeight = 0;

// origin position and vision needs to be loaded from the server
let x = 6;
let minX = 13;
let maxX = 13;
let y = 6;
let minY = 0;
let maxY = 13;
let height = 13;
let width = 13;



let mapCellSize = 64;
//position
function asdasf() {
    let cell = minimap2d[mapCellSize][mapCellSize] //returns a sctring of a cell size 16x16 or 256 chars 64*64=4096
    //when you move far enough in x or -x add a new cell to the array
    //when you move far enough in y or -y add a new cell to the array
    //calculate with cells your viewport intersects and populate them the the correct characters
}


function Rebuid_Map(visionWidth, updatedMap, direction) {
    let rebuiltMinimap = minimap;
    if (direction == 'w') {

        
        y--;
        if ((y - 6) < minY) {
            //add new line to the top of the map
            let update = updatedMap.substring(0, visionWidth);
            rebuiltMinimap = update + minimap;
            minimap = rebuiltMinimap;
            minY--;
            height++;
        }        
    }
    else if (direction == 's') {
        y++;
        if ((y + 6 + 1) > maxY) {
            //add new line to the bottom of the map
            //rebuiltMinimap.substring(0, visionWidth * (visionWidth - 1));
            let update = updatedMap.substring(visionWidth * (visionWidth - 1), visionWidth * visionWidth);
            rebuiltMinimap = minimap + update;
            minimap = rebuiltMinimap;
            maxY++;
            height++;
        }   
        else {
        }     
    }
    else if (direction == 'a') {
        // x--;
        // if (x < minX) {
        //     for (let i = 0; i < height; i++) {
            
        //     }
        //     minX--;
        // }
    }
    else if (direction == 'd') {

        x++;
        let mapWidth = (x + 6);
        if (mapWidth > maxX) {
            
            for (let i = 0; i < height; i++) {
                let start = (i * visionWidth) + visionWidth - 1;
                let end = start + 1;
                // let mapLine = updatedMap.substring(start, end);
                let mapLine = "0";
                console.log(mapLine);

                let insertPos = (mapWidth - 1) * i;
                let insertEnd = insertPos + mapWidth - 1;
                console.log(insertPos, insertEnd);
                
                let newMapLine = minimap.substring(insertPos, insertEnd)
                console.log(newMapLine);
                let line = newMapLine + mapLine;
                console.log(line);
                // minimapDisplay[i] = Create_MiniMap_Line(line, i);
                
                let tempmap = rebuiltMinimap;                
                rebuiltMinimap = tempmap + line;
            }
            minimap = rebuiltMinimap;
            maxX++;
            width++;
        }
    }
    else if (direction == 'm') {
        console.log("melee attacking target");
    }
    else if (direction == 'c') {
        console.log("wall collision");
    }
    else {
        minimap = updatedMap
    }
    //don't clear the minimap, just add to it and update the display
    //need direction to know where to add the new map    
}

function Update_Map(visionWidth, direction) {
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
        Rebuid_Map(visionWidth, updatedMap, direction);
        console.log(minimap);
        return true;
    }
    return false;
}

function Draw_Map(visionWidth, direction) {
    //get postion of player
    //update the section of the map that the player is in
    if (Update_Map(width, direction)) {
        for (let i = 0; i < height; i++) {
            let start = i * width;
            let end = start + width;
            let mapLine = minimap.substring(start, end);
            console.log(mapLine);
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
}

export function Map(data) {
    let visionWidth = parseInt(data.substring(0, 2), 10);
    let direction = data.substring(2,3);
    let serverMap = data.substring(3);
    Make_Map(serverMap, visionWidth);
    Draw_Map(visionWidth, direction);
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
