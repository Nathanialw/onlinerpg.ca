'use strict'
import { Clear_Sprite_Array, Draw_Inventory_Icons, Draw_Bag_Icons, inventory, itemFramePath, bags } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener_inv } from '../networking/send.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

let iconPath = "assets/graphics/icons/"
    
export function Query_Inventory(numItems, data, start) {
    let inv = []
    for (let i = 0; i < numItems; i++) {
        //isert teh path
        let str = data.substring(start + (i * 5), start + ((i + 1) * 5), 10);        
        let invIndex = parseInt(str.substring(0, 2));
        let itemID = parseInt(str.substring(2, 5));

        let item = Get_Icon_Path(itemID);
        let icon = item.icon
        if (icon === undefined || icon === "none") {
            inv.push({index: i, itemID: itemID, path: icon}); 
        }
        else {
            let path = iconPath + icon;
            inv.push({index: i, itemID: itemID, path: path}); 
        }     
    }
    return inv;
}

const defaultInventoryIcon = 'assets/graphics/ui/inventory/slot_empty.png'
const defaultBagIcon = 'assets/graphics/ui/inventory/bags_empty_background.png'

const copperIcon = 'assets/graphics/ui/inventory/coin_copper.png'
const silverIcon = 'assets/graphics/ui/inventory/coin_silver.png'
const goldIcon = 'assets/graphics/ui/inventory/coin_gold.png'

const itemBorders =[
    'public/assets/graphics/ui/inventory/item_quality_1.png',
    'public/assets/graphics/ui/inventory/item_quality_2.png', 
    'public/assets/graphics/ui/inventory/item_quality_3.png',
    'public/assets/graphics/ui/inventory/item_quality_4.png', 
    'public/assets/graphics/ui/inventory/item_quality_5.png', 
    'public/assets/graphics/ui/inventory/item_quality_6.png', 
    'public/assets/graphics/ui/inventory/item_quality_7.png', 
    'public/assets/graphics/ui/inventory/item_quality_8.png',
]

export async function Draw_Inventory(bags, items) {
    for (let i = 0; i < inventory.length; i++) {
        Clear_Sprite_Array(inventory[i]);
    }    Clear_Sprite_Array(bags);
    const numBags = 5;
    for (let i = 0; i < numBags; i++) {
        //draw bag icon
        if (bags[i] === undefined || bags[i] === "none") {
            let bag = await Draw_Bag_Icons(defaultBagIcon, i, 2)
            let border = await Draw_Bag_Icons(itemFramePath, i, 2) //border
        }
        else {
            let bag = await Draw_Bag_Icons(bags[i], i, 2)
            let border = await Draw_Bag_Icons(itemFramePath, i, 2) //border
        }
    }

    for (let j = 0; j < items.length; j++) {
        let num = 0;
        for (let i = 0; i < items[j].length; i++) {
            if (items[j][i].path === undefined || items[j][i].path === "none") {
                let item = await Draw_Inventory_Icons(defaultInventoryIcon, num, j, 2.5)            
                let border = await Draw_Inventory_Icons(itemFramePath, num, j, 2.5) //border
            }
            //clear event listene from index i
            else {
                let item = await Draw_Inventory_Icons(items[j][i].path, num, j, 2.5)            
                //check the rarity of the item
                let border = await Draw_Inventory_Icons(itemFramePath, num, j, 2.5) //border
                Set_Send_On_Loot_Click_Listener_inv(item, '1', num, j, items[j][i].itemID, Draw_Inventory_Icons);   //1 means inventory panel
            }
            num++
        }
    }
}
