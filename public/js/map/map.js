'use strict'

import {Create_Object_Sprite, Create_Map_Line, Create_MiniMap_Line, Create_MiniMap_Line_Phone, Draw_Vision_Background} from '../graphics/graphics.js';
import {Set_Enemies, Set_Player, Set_Objects} from '../objects/objects.js';
import {Set_Send_On_Map_Click_Listener} from '../networking/send.js';

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
            // let newLine = update + " " * (width - visionWidth);
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
        let mapWidth = (x + 6 + 1);
        if (mapWidth > maxX) {
            let rebuiltMinimap = "";
            let vision = 0;
            for (let i = 0; i < height; i++) {
                // vision++
                let appendLine = " ";
                // if (vision < height) {
                    let start = (i * visionWidth) + visionWidth - 1;
                    let end = start + 1;
                    appendLine = mapString.substring(start, end);
                // }

                let insertPos = (mapWidth - 1) * i;
                let insertEnd = insertPos + mapWidth - 1;
                
                let newMapLine = minimap.substring(insertPos, insertEnd)
                let line = newMapLine + appendLine;
                // minimapDisplay[i] = Create_MiniMap_Line(line, i);
                
                let tempmap = rebuiltMinimap
                rebuiltMinimap = tempmap + line;
            }
            minimap = rebuiltMinimap;
            maxX++;
            width++;
        }
    }
    else if (direction == 'm') {
    }
    else if (direction == 'c') {
    }
    else if (direction == 'r') {
    }
    else if (direction == ' ') {
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
            let tempMap = updatedMap;
            updatedMap = tempMap + mapLine;
        }
        // Rebuid_Map(visionWidth, updatedMap, direction);
        return true;
    }
    return false;
}

export function Draw_Map(visionWidth, direction) {
    //get postion of player
    //update the section of the map that the player is in
    if (Update_Map(visionWidth, direction)) {
        for (let i = 0; i < height; i++) {
            let start = i * width;
            let end = start + width;
            let mapLine = minimap.substring(start, end);
            minimapDisplay[i] = Create_MiniMap_Line(mapLine, i);
        }
    }
    else {
    }
}   

export function Draw_Map_Phone(visionWidth, direction) {
    //get postion of player
    //update the section of the map that the player is in
    if (Update_Map(visionWidth, direction)) {
        for (let i = 0; i < height; i++) {
            let start = i * width;
            let end = start + width;
            let mapLine = minimap.substring(start, end);
            minimapDisplay[i] = Create_MiniMap_Line_Phone(mapLine, i);
        }
    }
    else {
    }
}   


function Clear_Space(serverMap, i) {
    serverMap = serverMap.substring(0, i) + " " + serverMap.substring(i + 1);
}

// instead this function should create a blank map of . and it should get filled in in 8x8 chunks from the server as the player moves, 
let objects = []
let objectDisplay = []

export function Make_Map(serverMap, visionWidth) { 
    //parse the map and pull out the characters and replace with spaces
    //create a sprite at the location of the space that is clickable
    //query the server using the x and y of the sprite to get the sprite data
    objects.length = 0;;
    objectDisplay.length = 0;
    for (let i = 0; i < serverMap.length; i++) {
        if (serverMap[i] == "^") {
            objects.push([i, "˛"]); // save the location of the enemy
            objects.push([i, "▲"]); // save the location of the enemy            
            serverMap = serverMap.substring(0, i) + " " + serverMap.substring(i + 1); //background char
        }
        else if (serverMap[i] == ".") {
            serverMap = serverMap.substring(0, i) + " " + serverMap.substring(i + 1); //background char
        }
        else if ((serverMap[i] == ",")) {
            // serverMap = serverMap.substring(0, i) + "ô" + serverMap.substring(i + 1); //background char
            objects.push([i, "ô"]); // save the location of the enemy
            serverMap = serverMap.substring(0, i) + " " + serverMap.substring(i + 1); //background char
        }
        else {
            objects.push([i, serverMap[i]]); // save the location of the enemy
            serverMap = serverMap.substring(0, i) + " " + serverMap.substring(i + 1); //background char
        }
        //bag      
    }

    mapString = "";    
    for (let i = 0; i < visionWidth; i++) {
        let mapLine = serverMap.substring(i * visionWidth, (i * visionWidth) + visionWidth); // 0, 13 -> 13, 26 -> 26, 39
        mapString += mapLine;
        mapDisplay[i] = Create_Map_Line(mapLine, i, visionWidth);
    }

    for (let i = 0; i < objects.length; i++) {
        let x = objects[i][0] % visionWidth;
        let y = Math.floor(objects[i][0] / visionWidth);
        objectDisplay[i] = Create_Object_Sprite(objects[i][1], x, y, visionWidth);
        Set_Send_On_Map_Click_Listener(objectDisplay[i], x, y);
    }
    //draw the units on top of the map
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
