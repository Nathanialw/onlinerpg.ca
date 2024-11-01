'use strict'

export function Parse_Item(dataStr, item) {
    [item.ItemID, dataStr] = [parseInt(dataStr.substring(0, 3)), dataStr.substring(3)];
    //save rarity border path
    [item.Rarity, dataStr] = [parseInt(dataStr.substring(0, 1)), dataStr.substring(1)];
    //save durability value
    [item.Durability, dataStr] = [parseInt(dataStr.substring(0, 3)), dataStr.substring(3)];
    
    //sav modifier uIDs to look up in the db
    const numMods = parseInt(dataStr.substring(0, 1));
    dataStr = dataStr.substring(1);

    item.Modifiers.length = 0;
    for (let j = 0; j < numMods; j++) {
        item.Modifiers[j] = (dataStr.substring(0, 3));
        dataStr = dataStr.substring(3)
    }

    return dataStr;
}

// async function fetchAndParseItems() {
//     let dataStr1 = "00120302001002"; // Example data string for item 1
//     let dataStr2 = "00210402002003"; // Example data string for item 2

//     let item1 = { Modifiers: [] };
//     let item2 = { Modifiers: [] };

//     Parse_Item(dataStr1, item1);
//     Parse_Item(dataStr2, item2);

//     console.log("Item 1:", item1);
//     console.log("Item 2:", item2);
// }

// // Example usage
// fetchAndParseItems();