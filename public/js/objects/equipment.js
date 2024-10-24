'use strict'
import { Clear_Sprite_Array, Draw_Equipment_Icons, equipment, itemFramePath } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener } from '../networking/send.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

let iconPath = "assets/graphics/icons/"

export function Query_Equipment(numItems, data, start) {
    let equipped = []
    for (let i = 0; i < numItems; i++) {
        //isert teh path
        let str = data.substring(start + (i * 5), start + ((i + 1) * 5), 10);        
        let equipmentIndex = parseInt(str.substring(0, 2));
        let itemID = parseInt(str.substring(2, 5));
        let item = Get_Icon_Path(itemID);

        let icon = item.icon
        if (icon === undefined || icon === "none") {
            equipped.push({index: i, itemID: itemID, path: icon}); 
        }
        else {
            let path = iconPath + icon;
            equipped.push({index: i, itemID: itemID, path: path}); 
        }
    }
    return equipped;
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
    'assets/graphics/ui/equipment/empty_trinket.png',
    'assets/graphics/ui/equipment/empty_trinket.png',
    'assets/graphics/ui/equipment/empty_hand.png',
    'assets/graphics/ui/equipment/empty_hand.png',
    'assets/graphics/ui/equipment/empty_ranged.png',
    'assets/graphics/ui/equipment/ammo_slot.png',
]
let chain = 'assets/graphics/ui/equipment/chain_link.png'
let ammobg = 'assets/graphics/ui/equipment/slot_frame_ammo.png'

export async function Draw_Equipment(items) {
    Clear_Sprite_Array(equipment);

    for (let i = 0; i < items.length; i++) {
        if (items[i].path === undefined || items[i].path === "none") {
            let item = await Draw_Equipment_Icons(defaultEquipmentIcons[i], i, 2.5)        
            if (i === 15) {
                let border = await Draw_Equipment_Icons(itemFramePath, i, 2.5) //border
            }
            else {
                let border = await Draw_Equipment_Icons(ammobg, i, 2.5) //border
            }
        }
        else {
            let item = await Draw_Equipment_Icons(items[i].path, i, 2.5)        
            //check the rarity of the item
            if (i === 15) {
                let border = await Draw_Equipment_Icons(itemFramePath, i, 2.5) //border
            }
            else {
                let border = await Draw_Equipment_Icons(ammobg, i, 2.5) //border
            }
            Set_Send_On_Loot_Click_Listener(item, '2', i, items[i].itemID, Draw_Equipment_Icons, 2.5);   //1 means inventory panel
        }
    }
}
