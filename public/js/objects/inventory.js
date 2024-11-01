'use strict'
import { Draw_Inventory_Icons, Draw_Bag_Icons, itemFramePath, itemBorders } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener_inv, Set_Send_On_Loot_Click_Listener } from '../networking/send.js';
import { Parse_Inventory, Parse_Bags } from '../parse/inventory.js';
import { deepCopyItem } from "./item.js";

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box


const numBags = 4;
const maxItems = 12;

function Create_Bag() {
    return {
        ItemID: "",
        Texture: null,
        IconPath: "none",
        Border: null,
        Items: Array(maxItems).fill().map(() => ( deepCopyItem() ))
    };
}


let inventory = [];
for (let i = 0; i < numBags; i++) {
    inventory.push(Create_Bag());
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

export function Update_Inventory(dataStr) {
    dataStr = Parse_Bags(dataStr, inventory);
    dataStr = Parse_Inventory(dataStr, inventory);

    //update the entire inventory vs just the ones sent
    inventory.forEach(bag => {
        bag.IconPath = Set_Icon(bag.ItemID);    
        let bagSize = Get_Icon_Path(bag.ItemID).slots
        for (let i = 0; i < bagSize; ++i) {            
            bag.Items[i].IconPath = Set_Icon(bag.Items[i].ItemID);    
            bag.Items[i].Modifiers.forEach(mod => {
                //get the values
                //get the text
            }
            ///combine the like mods store the string
        )};
    });
    return dataStr;
}

const defaultInventoryIcon = 'assets/graphics/ui/inventory/slot_empty.png'
const defaultBagIcon = 'assets/graphics/ui/inventory/bags_empty_background.png'

const copperIcon = 'assets/graphics/ui/inventory/coin_copper.png'
const silverIcon = 'assets/graphics/ui/inventory/coin_silver.png'
const goldIcon = 'assets/graphics/ui/inventory/coin_gold.png'

const bagIconSize = 2.5;
const iconSize = 3.5;

export async function Draw_Inventory() {   
    for (let i = 0; i < numBags; i++) {
        if (inventory[i].IconPath === undefined || inventory[i].IconPath === "none") {
            inventory[i].Texture = await Draw_Bag_Icons(defaultBagIcon, i, bagIconSize)
            inventory[i].Border = await Draw_Bag_Icons(itemFramePath, i, bagIconSize) //border
        }
        else {
            inventory[i].Texture = await Draw_Bag_Icons(inventory[i].IconPath, i, bagIconSize)
            inventory[i].Border = await Draw_Bag_Icons(itemFramePath, i, bagIconSize) //border
            Set_Send_On_Loot_Click_Listener(inventory[i], '3', i, Draw_Bag_Icons, bagIconSize);   //1 means inventory panel
        }
    }
    
    for (let j = 0; j < numBags; j++) {
        let num = 0;
                let bagSize = Get_Icon_Path(inventory[j].ItemID).slots
        for (let i = 0; i < bagSize; i++) {
            if (inventory[j].Items[i].IconPath === undefined || inventory[j].Items[i].IconPath === "none") {
                inventory[j].Items[i].Texture = await Draw_Inventory_Icons(defaultInventoryIcon, num, j, iconSize)            
                inventory[j].Items[i].Border = await Draw_Inventory_Icons(itemFramePath, num, j, iconSize) //border
            }
            //clear event listene from index i
            else {
                inventory[j].Items[i].Texture = await Draw_Inventory_Icons(inventory[j].Items[i].IconPath, num, j, iconSize)            
                inventory[j].Items[i].Border = await Draw_Inventory_Icons(itemBorders[inventory[j].Items[i].Rarity], num, j, iconSize) //border
                Set_Send_On_Loot_Click_Listener_inv(inventory[j].Items[i], '1', num, j, Draw_Inventory_Icons, 3.5);   //1 means inventory panel
            }
            num++
        }
    }
}
