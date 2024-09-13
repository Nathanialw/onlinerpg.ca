'use strict'

import {Create_Object} from '../graphics/graphics.js';


let player;
let enemies = []
let objects = []

export function Set_Player(unitString) {
    // player = Create_Object(unitString[0], unitString.substring(1,3), unitString.substring(3,5));;
    player = Create_Object(unitString[0], 6, 6);;
}

export function Set_Enemies(object) {
    enemies = Create_Object(unitString[0], unitString.substring(1,3), unitString.substring(3,5));;
    //enemies = object;
}

export function Set_Objects(object) {
    objects = object;
}


export function Move_Player(x, y) {
    // player.x += x;
    // player.y += y;
}

export function Move_Enemies(object) {
    enemies.push(object);
}

export function Move_Objects(object) {
    objects.push(object);
}





// export {player, enemies, objects}
