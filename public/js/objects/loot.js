'use strict'
import { Clear_Sprite_Array, Draw_Loot_Icons, loot } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener } from '../networking/send.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box


export function Query_Loot(numItems, data, start) {
    let drops = []
    for (let i = 0; i < numItems; i++) {
        //isert teh path
        let itemID = parseInt(data.substring(start + (i * 3), start + ((i + 1) * 3), 10));
        let item = Get_Icon_Path(itemID);
        drops.push({index: i, itemID: itemID, path: item.icon, name: item.name});    
        console.log(drops[i]);
    }
    return drops;
}

export async function Draw_Loot(items) {
    Clear_Sprite_Array(loot);

    for (let i = 0; i < items.length; i++) {
        if (items[i].path === undefined || items[i].path === "none") {
            continue
        }
        // draw loot background and border
        let item = await Draw_Loot_Icons(items[i].path, i, 1, 2.5, 2.5, items[i].name);        
        //draw loot name
        Set_Send_On_Loot_Click_Listener(item, '0', i, items[i].itemID);  //0 means loot panel
    }
}

