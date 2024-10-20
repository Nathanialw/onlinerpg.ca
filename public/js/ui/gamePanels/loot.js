'use strict'
import { Draw_Loot } from '../objects/loot.js';

export let loot = [];

// export function Get_Loot() {
//     loot = Query_Loot();
// }

export function Loot() {
    
    Draw_Loot(loot);    
}



