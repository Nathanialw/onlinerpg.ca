'use strict'
import { Parse_Item } from ".items.js";



export function Parse_Equipment(dataStr) {
    const numItems = parseInt(dataStr.substring(0, 2));
    dataStr = dataStr.substring(2)

    for (let i = 0; i < numItems; i++) {
        let index = parseInt(dataStr.substring(0, 2));
        dataStr = Parse_Item(dataStr, equipment[index]);
    }
    return dataStr;
}