import {Create_Object, Create_Map_Line} from '../graphics/graphics.js';
import {Set_Enemies, Set_Player, Set_Objects} from '../objects/objects.js';

let mapDisplay = [];
let fill = [];

// for testing start

// let mapString = "\
// ####################\
// #......H...........#\
// #..................#\
// #..................#\
// #..................#\
// #..................#\
// #..................#\
// #..................#\
// #..................#\
// #.............g....#\
// #...............g..#\
// #..................#\
// #..................#\
// #g.................#\
// #..................#\
// #..................#\
// #..................#\
// #..................#\
// #....g.g.........o.#\
// ####################";
// let mapWidth = 20;
// Make_Map();

// for testing end



export function Make_Map(serverMap, mapWidth) {
    for (let i = 0; i < mapWidth; i++) {
        //render lines of the map
        let object = serverMap.substring((i * mapWidth), ((i * mapWidth) + mapWidth));
        mapDisplay[i] = Create_Map_Line(object, i);

        // sent floor under units
        for (let j = 0; j < mapWidth; j++) {
            if (object[j] === 'H') {
                fill.push(Create_Object('.', j, i));
            }
            else if (object[j] === 'g') {
                fill.push(Create_Object('.', j, i));
            }
            else if (object[j] === 'o') {
                fill.push(Create_Object('.', j, i));
            }
        }
    }

    // render units on the map, ensure they are rendered on top of the floor
    for (let i = 0; i < mapWidth; i++) {
        for (let j = 0; j < mapWidth; j++) {
            let object = serverMap.substring([(i * mapWidth)], (i * mapWidth) + mapWidth);
            
            if (object[j] === 'H') {
                Set_Player(Create_Object(object[j], j, i));
            }
            else if (object[j] === 'g') {
                Set_Enemies(Create_Object(object[j], j, i));
            }
            else if (object[j] === 'o') {
                Set_Objects(Create_Object(object[j], j, i));
            }
        }
    }
}
