'use strict'
import { Draw_Equipment_Icons, itemFramePath, itemBorders } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener } from '../networking/send.js';
import { item } from "./item.js";
import { Parse_Equipment } from '../parse/equipment.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

let iconPath = "assets/graphics/icons/"


const equipSlots = 14;
let equipment = Array(equipSlots).fill().map(() => ({ ...item }))

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


export function Update_Equipment(dataStr) {
    console.log("Parsing equipment")
    console.log("dataStr: ", dataStr)
    dataStr = Parse_Equipment(dataStr, equipment)
    equipment.forEach(item => {
        item.IconPath = Set_Icon(item.ItemID);
        item.Modifiers.forEach(mod => {
            //get the values
            //get the text
        })
    })
    return dataStr;
}

const defaultEquipmentIcons = [
    'assets/graphics/ui/equipment/empty_helmet.png',
    'assets/graphics/ui/equipment/empty_amulet.png',
    'assets/graphics/ui/equipment/empty_cloak.png',
    'assets/graphics/ui/equipment/empty_chest.png',
    'assets/graphics/ui/equipment/empty_belt.png',
    'assets/graphics/ui/equipment/empty_gloves.png',
    'assets/graphics/ui/equipment/empty_pants.png',
    'assets/graphics/ui/equipment/empty_boots.png',
    'assets/graphics/ui/equipment/empty_ring.png',
    'assets/graphics/ui/equipment/empty_ring.png',    
    'assets/graphics/ui/equipment/empty_hand.png',
    'assets/graphics/ui/equipment/empty_hand.png',
    'assets/graphics/ui/equipment/empty_ranged.png',
    'assets/graphics/ui/equipment/ammo_slot.png',
]

let chain = 'assets/graphics/ui/equipment/chain_link.png'
let ammobg = 'assets/graphics/ui/equipment/slot_frame_ammo.png'

export async function Draw_Equipment() {
    for (let i = 0; i < equipment.length; i++) {
        if (equipment[i].IconPath === undefined || equipment[i].IconPath === "none") {
            equipment[i].Texture = await Draw_Equipment_Icons(defaultEquipmentIcons[i], i, 2.5)        
            equipment[i].Border = await Draw_Equipment_Icons(itemFramePath, i, 2.5) //border
        }
        else {
            equipment[i].Texture = await Draw_Equipment_Icons(equipment[i].IconPath, i, 2.5)        
            equipment[i].Border = await Draw_Equipment_Icons(itemBorders[equipment[i].Rarity], i, 2.5) //border
            Set_Send_On_Loot_Click_Listener(equipment[i].Texture, '2', i, equipment[i].ItemID, Draw_Equipment_Icons, 2.5);   //1 means inventory panel
        }
    }
}
