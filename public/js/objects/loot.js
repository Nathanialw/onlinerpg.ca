'use strict'
import { Clear_Sprite_Array, Draw_Loot_Icons, Draw_Loot_Text, Draw_Loot_Background, itemFramePath } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener } from '../networking/send.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

let iconPath = "assets/graphics/icons/"

export function Query_Loot(numItems, data, start) {
    let drops = []
    for (let i = 0; i < numItems; i++) {
        //isert teh path
        let itemID = parseInt(data.substring(start + (i * 3), start + ((i + 1) * 3), 10));

        let item = Get_Icon_Path(itemID);
        let icon = item.icon
        if (icon === undefined || icon === "none") {
            drops.push({index: i, itemID: itemID, path: icon, name: item.name}); 
        }
        else {
            let path = iconPath + icon;
            drops.push({index: i, itemID: itemID, path: path, name: item.name}); 
        }
    }
    return drops;
}

export async function Draw_Loot(items) {

    for (let i = 0; i < items.length; i++) {
        if (items[i].path === undefined || items[i].path === "none") {
            continue
        }
        // draw loot background and border
        let background = await Draw_Loot_Background(itemFramePath, i, 2.5); //background
        let icon = await Draw_Loot_Icons(items[i].path, i, 2.5);   
        let text = await Draw_Loot_Text(items[i].name, i, 2.5) //text
        let border = await Draw_Loot_Icons(itemFramePath, i, 2.5) //border

        //draw loot name
        Set_Send_On_Loot_Click_Listener(background, '0', i, items[i].itemID, Draw_Loot_Background, 2.5);  //0 means loot panel
    }
}
