'use strict'
import { itemBorders, Draw_Loot_Icons, Draw_Loot_Text, Draw_Loot_Background, itemFramePath } from '../graphics/graphics.js';
import { Get_Icon_Path, Get_Item_Stats } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener_Loot } from '../networking/send.js';
import { item } from "./item.js";
import { Parse_Loot } from '../parse/loot.js';
import { Set_Game_Panel_Index } from '../ui/menus/gameMenu.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

let iconPath = "assets/graphics/icons/"

const groundSlots = 14;



// Array(groundSlots).fill().map(() => ({ Texture: null, Name: null }))
// let loot = Array(groundSlots).fill().map(() => ({ ... item}));
let loot = {
    NumItems: 0,
    Panel: Array(groundSlots).fill().map(() => ({ Texture: null, Name: null })),
    Items: Array(groundSlots).fill().map(() => ({ ... item}))
}

export function Open_Loot_Panel(direction) {
    if (loot.NumItems > 0 && (direction == 'a' || direction == 'd' || direction == 'w' || direction == 's')) {
        Set_Game_Panel_Index(3);
    }
}

function Set_Icon(uID) {
    let item = Get_Icon_Path(uID);
    if (item === undefined) {
        console.log(uID, "uID is undefined in the db")
        return item;
    }
    if (item.icon === undefined || item.icon === "none") {
        return item.icon; 
    }
    let iconPath = "assets/graphics/icons/";
    return iconPath + item.icon;    
}

export function Update_Loot(dataStr, direction) {
    //clear the loot array
    // loot = []
    // loot = Array(groundSlots).fill().map(() => ({ ... item}));
    dataStr = Parse_Loot(dataStr, loot)
    for (let i = 0; i < loot.NumItems; ++i) {            
        loot.Items[i].IconPath = Set_Icon(loot.Items[i].ItemID);
        loot.Items[i].Modifiers.forEach(mod => {
            //get the values
            //get the text
        })
    }

    Open_Loot_Panel(direction);

    return dataStr;
}

export async function Draw_Loot() {

    for (let i = 0; i < loot.NumItems; i++) {
        if (loot.Items[i].IconPath === undefined || loot.Items[i].IconPath === "none") {
            break
        }
        // draw loot background and border
        loot.Panel[i].Texture = await Draw_Loot_Background(itemFramePath, i, 2.5); //background
        loot.Items[i].Texture = await Draw_Loot_Icons(loot.Items[i].IconPath, i, 2.5);   
        let stats = await Get_Item_Stats(loot.Items[i].ItemID)
        // const name = name.charAt(0).toUpperCase() + name.slice(1);
        loot.Panel[i].Name = await Draw_Loot_Text(stats[0].name.charAt(0).toUpperCase() + stats[0].name.slice(1), i, 2.5) //text
        loot.Items[i].Border = await Draw_Loot_Icons(itemBorders[loot.Items[i].Rarity], i, 2.5) //border

        console.log("pan", loot.Panel[i])
        console.log("loo", loot.Items[i])

        Set_Send_On_Loot_Click_Listener_Loot(loot.Panel[i], loot.Items[i], '0', i, Draw_Loot_Background, 2.5);  //0 means loot panel
    }
}
