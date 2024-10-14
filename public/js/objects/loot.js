'use strict'
import { Draw_Loot_Icons, loot } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener } from '../networking/send.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

export async function Draw_Loot(items) {
    console.log('Drawing loot');
    loot.length = 0;

    for (let i = 0; i < items.length; i++) {
        if (items[i] === "none") {
            continue
        }
        let item = await Draw_Loot_Icons(items[i], i, 1, 2.5, 2.5)        
        Set_Send_On_Loot_Click_Listener(item, '0', i);  //0 means loot panel
    }
}

export function Query_Loot(numItems, data, start) {
    let items = [];
    for (let i = 0; i < numItems; i++) {
        //isert teh path
        items.push(Get_Icon_Path(parseInt(data.substring(start + (i * 3), start + ((i + 1) * 3)), 10)));
        
    }

    return items;
}