'use strict'
import { Parse_Item } from "./items.js";



export function Parse_Loot(dataStr, loot, numItems) {
    numItems = parseInt(dataStr.substring(0, 2));
    dataStr = dataStr.substring(2)

    for (let i = 0; i < numItems; i++) {
        dataStr = Parse_Item(dataStr, loot[i]);
    }
    return dataStr;
}