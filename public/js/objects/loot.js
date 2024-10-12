'use strict'
import { Draw_Icons } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

export async function Draw_Loot(items) {
    console.log('Drawing loot');


    for (let i = 0; i < items.length; i++) {
        await Draw_Icons(items[i], i, 1, 2, 2.5)
    }
}

export function Query_Loot(numItems, data) {
    let items = [];
    for (let i = 0; i < numItems; i++) {
        //isert teh path
        items.push(Get_Icon_Path(parseInt(data.substring(8 + (i * 3), 8 + ((i + 1) * 3)), 10)));
    }

    return items;
}