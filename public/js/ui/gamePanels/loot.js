'use strict'
import { Draw_Loot } from '../../objects/loot.js';

export let loot = [];

// export function Get_Loot() {
//     loot = Query_Loot();
// }

export function Loot() {
    
    Draw_Loot(loot);    
}


export function Open_Loot_Panel(direction) {
    if (loot.length > 0 && (direction == 'a' || direction == 'd' || direction == 'w' || direction == 's')) {
        Set_Game_Panel_Index(3);
    }
}

