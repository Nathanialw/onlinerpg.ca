'use strict'

//parses the inventory data string and saves it to the inventory object

import {item, inventory} from "../objects/inventory.js";

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


function Parse_Item(numItems, start, data, Query, size, items) {
    removeEventListenersFromArray(items);
    items.length = 0; // Clear the array without reassigning it
    if (numItems > 0) {
        items.push(...Query(numItems, data, start));
    }    
    
    return start + (numItems * size); 
}


//takes in a  string of data and returns a structure of the data
export function Parse_Inventory(dataStr) {
    let start = 0;

    bags.length = 0;
    for (let i = 0; i < 5; i++) {
        //save to draw the bag icons
        let uID = data.substring(start, start + 3);
        //get from DB
        let item = Get_Icon_Path(uID);
        if (item === undefined) {
            console.log(uID, "uID is undefined in the db")
            continue;
        }
        //save icon path
        let iconPath = "assets/graphics/icons/" + item.icon;
        
        // //save rarity border path
        // let rarityID = data.substring(startBag + 3, startBag + 4);
        // //query db for rarity path
        // let rarityPath;                                                  //1
        // //save durability value
        // let durabilityValue = data.substring(startBag + 4, startBag + 7);
        // //sav modifier uIDs to look up in the db
        // let numMods = data.substring(startBag + 7, startBag + 8);
        // let modifiers = [numMods]                       
        // let strPosBegin = startBag + 8;
        // let strPosEnd = startBag + 11;
        // for (let j = 0; j < item.modifiers.length; j++) {
        //     let modID = data.substring(strPosBegin, strPosEnd)
        //     strPosBegin += 3;
        //     strPosEnd += 3;
        //     modifiers.push(item.modifiers[j]);                             //3 * j
        // }
        // startBag = strPosBegin;
        // bags[i] = {path: iconPath + item.icon, itemID: bagID, rarity: rarityPath, durability: durabilityValue, modifierStringsArray: modifiers};

        inventory[i] = {uID: uID, iconPath: iconPath};
        let numItems = item.slots; 

        let items = []; //items in the bag
        start = Parse(numItems, (start + 3), data, Query_Inventory, 5, items);
        inventory[i].items = items

        return remainingStr;
    }




    return remainingStr;
}