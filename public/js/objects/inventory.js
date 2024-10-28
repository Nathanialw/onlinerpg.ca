'use strict'
import { Clear_Sprite_Array, Draw_Inventory_Icons, Draw_Bag_Icons, itemFramePath } from '../graphics/graphics.js';
import { Get_Icon_Path } from '../db/db.js';
import { Set_Send_On_Loot_Click_Listener_inv, Set_Send_On_Loot_Click_Listener } from '../networking/send.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

let iconPath = "assets/graphics/icons/"

//defines an item, used for Inventory, Equipment and Loot
export let item = {
    iconPath: 0,
    durability: 0,
    rarity: 0,
    modStringsUIDArray: [],
    modStrings: [] //add teh mods that are like to display as consolidated values ie. if there are 2 + fire damage mods, add them together and save the string here to display
}

export let inventory = []
export let bags = [];


//stores all the inventory items and bags
export let inventorys = [ 
    { uID: 0, iconPath: '', items: [] },
    { uID: 0, iconPath: '', items: [] },
    { uID: 0, iconPath: '', items: [] },
    { uID: 0, iconPath: '', items: [] },
    { uID: 0, iconPath: '', items: [] }
]
    
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

export function Parse_Inventory(data, startBag) {
    bags.length = 0;
    for (let i = 0; i < 5; i++) {
        let bag = [];
        //save to draw the bag icons
        let bagID = data.substring(startBag, startBag + 3);
        //get from DB
        let item = Get_Icon_Path(bagID);
        if (item === undefined) {
            console.log(bagID, "uID is undefined in the db")
            continue;
        }
        //save icon path
        let iconPath = "assets/graphics/icons/"

        bags[i] = {path: iconPath + item.icon, itemID: bagID};
        let numItems = item.slots; 
        startBag = Parse(numItems, (startBag + 3), data, Query_Inventory, 5, bag);
        inventory[i] = bag
    }
    return startBag;
}

const defaultInventoryIcon = 'assets/graphics/ui/inventory/slot_empty.png'
const defaultBagIcon = 'assets/graphics/ui/inventory/bags_empty_background.png'

const copperIcon = 'assets/graphics/ui/inventory/coin_copper.png'
const silverIcon = 'assets/graphics/ui/inventory/coin_silver.png'
const goldIcon = 'assets/graphics/ui/inventory/coin_gold.png'

const itemBorders = [
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
    }    
    // Clear_Sprite_Array(bags);

    const numBags = 5;
    for (let i = 0; i < numBags; i++) {
        if (bags[i].path === undefined || bags[i].path === "none") {
            let bag = await Draw_Bag_Icons(defaultBagIcon, i, 2)
            let border = await Draw_Bag_Icons(itemFramePath, i, 2) //border
        }
        else {
            let bag = await Draw_Bag_Icons(bags[i].path, i, 2)
            let border = await Draw_Bag_Icons(itemFramePath, i, 2) //border
            Set_Send_On_Loot_Click_Listener(bag, '3', i, bags[i].itemID, Draw_Bag_Icons, 2);   //1 means inventory panel
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
