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

    for (let j = 0; j < numMods; j++) {
        item.Modifiers.push(parseInt(dataStr.substring(0, 3)));
        dataStr = dataStr.substring(3)
    }

    return dataStr;
}
