'use strict'
import { itemBorders, Draw_Loot_Icons, Draw_Loot_Text, Draw_Loot_Background, itemFramePath } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener } from '../networking/send.js';
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



let loot = Array(groundSlots).fill().map(() => ({ ... item}));
let lootBox = Array(groundSlots).fill().map(() => ({ Texture: null, Name: null }));

export function Open_Loot_Panel(direction) {
    if (loot.length > 0 && (direction == 'a' || direction == 'd' || direction == 'w' || direction == 's')) {
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
    loot = []
    loot = Array(groundSlots).fill().map((_, index) => initializeLootItem(index));
    
    dataStr = Parse_Loot(dataStr, loot)
    loot.forEach(item => {
        item.IconPath = Set_Icon(item.ItemID);
        item.Modifiers.forEach(mod => {
            //get the values
            //get the text
        })
    })

    Open_Loot_Panel(direction);

    return dataStr;
}

export async function Draw_Loot() {

    for (let i = 0; i < loot.length; i++) {
        if (loot[i].path === undefined || loot[i].path === "none") {
            break
        }
        // draw loot background and border
        lootBox[i].Texture = await Draw_Loot_Background(itemFramePath, i, 2.5); //background
        loot[i].Texture = await Draw_Loot_Icons(loot[i].IconPath, i, 2.5);   
        let name = await Get_Item_Stats(loot[i].ItemID)[0].name
        // const name = name.charAt(0).toUpperCase() + name.slice(1);
        lootBox[i].Name = await Draw_Loot_Text(name, i, 2.5) //text
        loot[i].Border = await Draw_Loot_Icons(itemBorders[equipment[i].Rarity], i, 2.5) //border

        //draw loot name
        Set_Send_On_Loot_Click_Listener(background, '0', i, loot[i].ItemID, Draw_Loot_Background, 2.5);  //0 means loot panel
    }
}
