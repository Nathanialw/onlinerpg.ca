'use strict'

import { Parse_Item } from "./item.js";

//parses the inventory data string and saves it to the inventory object

//should I save the strings in a data structure or just get the data from the db when I need to desplay it?

// how to use:
    //query the num NAME ICONPATH BAGSLOTS DESCRIPTIO with bagID
    //query the num ICONPATH with rarityID
    //query the num NAME ICONPATH DESCRIPTION EQUIPSLOT ETC with itemID
    //query the num NAME EFFECTS with modifierID
        //add like modifiers together before displaying

//takes in a  string of data and returns a structure of the data

export function Parse_Inventory(dataStr, inventory) {
    const numBags = 4;
    
    for (let i = 0; i < numBags; i++) {
        const numItems = parseInt(dataStr.substring(0, 2))
        dataStr = dataStr.substring(2);
        
        if (numItems == 0 && inventory[i].BagID) {            
            continue
        }

        [inventory[i].BagID, dataStr] = [parseInt(dataStr.substring(0, 3)), dataStr.substring(3)];
        
        if (numItems == 0) {            
            continue
        }

        for (let k = 0; k < numItems; k++) {
            const invIndex = parseInt(dataStr.substring(0, 2))
            dataStr = dataStr.substring(2);
            dataStr = Parse_Item(dataStr, inventory[i].Items[invIndex]);
        }
    }
    return dataStr
}

// console.log(Parse_Inventory("00020010000111001001010022100300200300402001000011100100101002210030020030040200100001110010010100221003002003004", inventory))