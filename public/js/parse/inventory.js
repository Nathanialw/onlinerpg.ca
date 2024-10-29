'use strict'
//parses the inventory data string and saves it to the inventory object



//should I save the strings in a data structure or just get the data from the db when I need to desplay it?

// how to use:
    //query the num NAME ICONPATH BAGSLOTS DESCRIPTIO with bagID
    //query the num ICONPATH with rarityID
    //query the num NAME ICONPATH DESCRIPTION EQUIPSLOT ETC with itemID
    //query the num NAME EFFECTS with modifierID
        //add like modifiers together before displaying


function Get_Item(dataStr, item) {
    item.ItemID = parseInt(dataStr.substring(0, 3));
    dataStr = dataStr.substring(3);

    //save rarity border path
    item.Rarity = parseInt(dataStr.substring(0, 1));
    dataStr = dataStr.substring(1);
    //save durability value
    item.Durability = parseInt(dataStr.substring(0, 3));
    dataStr = dataStr.substring(3);
    //sav modifier uIDs to look up in the db
    const numMods = parseInt(dataStr.substring(0, 1));
    dataStr = dataStr.substring(1);

    for (let j = 0; j < numMods; j++) {
        item.Modifiers.push(parseInt(dataStr.substring(0, 3)));
        dataStr = dataStr.substring(3)
    }

    return dataStr;
}

//takes in a  string of data and returns a structure of the data
export function Parse_Inventory(dataStr, inventory) {
    const numBags = 4;
    
    for (let i = 0; i < numBags; i++) {
        const numItems = parseInt(dataStr.substring(0, 2))
        dataStr = dataStr.substring(2);
        if (numItems == 0) {
            continue
        }

        inventory[i].BagID = dataStr.substring(0, 3)
        dataStr = dataStr.substring(3);

        for (let k = 0; k < numItems; k++) {

            const invIndex = parseInt(dataStr.substring(0, 2))
            dataStr = dataStr.substring(2);
            dataStr = Get_Item(dataStr, inventory[i].Items[invIndex]);
        }
    }
    return dataStr
}

// console.log(Parse_Inventory("00020010000111001001010022100300200300402001000011100100101002210030020030040200100001110010010100221003002003004", inventory))