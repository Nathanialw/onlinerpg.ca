'use strict'
import { Parse_Item } from "./items.js";



export function Parse_Loot(dataStr, loot) {
    loot.NumItems = parseInt(dataStr.substring(0, 2));
    dataStr = dataStr.substring(2)

    for (let i = 0; i < loot.NumItems; i++) {
        dataStr = Parse_Item(dataStr, loot.Items[i]);
        console.log(loot.Items[i])
    }
    return dataStr;
}