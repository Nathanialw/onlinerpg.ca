'use strict'
import { Load_Icons, Draw_Sprite, leftPanelWidth, leftPanelHeight, topPanelHeight, cellSize  } from '../graphics/graphics.js';

//when I move on to a new tile
//check if there is loot
//if there is get the indexes of the items
//read from db
//display the icon in the loot box

export function Draw_Loot(items) {
    console.log('Drawing loot');

    let x = (leftPanelWidth / 2) * cellSize
    let y = ((topPanelHeight / 4) + (leftPanelHeight * 2/3)) * cellSize
    // let w = (leftPanelWidth / 2) * cellSize
    // let h = ((leftPanelHeight * 1/3) - (topPanelHeight / 4)) * cellSize, loot;

    for (let i = 0; i < items.length; i++) {
        let item = Load_Icons(items[i], i);
        Draw_Sprite(x + 3, y + 3 + (20 * i), 20, 20, item);
    }
}

export function Query_Loot(numItems, data) {
    let items = [];
    for (let i = 0; i < numItems; i++) {
        //isert as an int
        items.push(parseInt(data.substring(8 + (i * 3), 8 + ((i + 1) * 3)), 10));
    }

    return items;
}