'use strict'
import { Draw_Inventory_Icons } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener } from '../networking/send.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

export async function Draw_Invetory(items) {
    console.log('Drawing Inventory');


    for (let i = 0; i < items.length; i++) {
        let item = await Draw_Inventory_Icons(items[i], i, 1, 2.5, 2.5)        
        Set_Send_On_Loot_Click_Listener(item, '1', i);   //1 means inventory panel
    }
}

export function Query_Invetory(numItems, data) {
    let items = [];
    for (let i = 0; i < numItems; i++) {
        //isert teh path
        items.push(Get_Icon_Path(parseInt(data.substring(8 + (i * 3), 8 + ((i + 1) * 3)), 10)));
    }

    return items;
}