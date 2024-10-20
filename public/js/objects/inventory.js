'use strict'
import { Clear_Sprite_Array, Draw_Inventory_Icons, inventory, itemFramePath } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener } from '../networking/send.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

export function Query_Inventory(numItems, data, start) {
    let inv = []
    for (let i = 0; i < numItems; i++) {
        //isert teh path
        let str = data.substring(start + (i * 5), start + ((i + 1) * 5), 10);        
        let invIndex = parseInt(str.substring(0, 2));
        let itemID = parseInt(str.substring(2, 5));

        inv.push({index: i, itemID: itemID, path: Get_Icon_Path(itemID).icon});        
    }
    return inv;
}

export async function Draw_Inventory(items) {
    Clear_Sprite_Array(inventory);

    for (let i = 0; i < items.length; i++) {
        if (items[i].path === undefined || items[i].path === "none") {
            continue
        }
        //clear event listene from index i

        let item = await Draw_Inventory_Icons(items[i].path, i, 2.5)            
        let border = await Draw_Inventory_Icons(itemFramePath, i, 2.5) //border
        Set_Send_On_Loot_Click_Listener(item, '1', i, items[i].itemID, Draw_Inventory_Icons);   //1 means inventory panel
    }
}
