// // import { Parse_Player_Update } from './ui.js';
// // import { Update_Loot } from '../objects/loot.js';
// // import { Update_Inventory } from '../objects/inventory.js';
// // import { Update_Equipment } from '../objects/equipment.js';


// let visionWidth;
// let direction;
// let species = "";
// let damage = "";
// let isDead = "";
// let serverMap = "";

// // visionWidth = parseInt(data.substring(0, 2), 10);
// // direction = data.substring(2,3);
// // species = Species[data.substring(3,4)];
// // damage = data.substring(4,6);
// // isDead = data.substring(6,7);

// function Parse_Player_Update(dataStr) {
//     [species, damage, isDead] = ["", "", ""];
//     [visionWidth, dataStr] = [parseInt(dataStr.substring(0, 2), 10), dataStr.substring(2)];
//     [direction, dataStr]   = [dataStr.substring(0, 1), dataStr.substring(1)];
//     if (direction === "m") { //only parse this when an attack is made
//         [species, dataStr]     = [Species[parseInt(dataStr.substring(0, 2), 10)], dataStr.substring(2)];
//         [damage, dataStr]      = [dataStr.substring(0, 2), dataStr.substring(2)];
//         [isDead, dataStr]      = [parseInt(dataStr.substring(0, 1), 10), dataStr.substring(1)];
//     }
//     return dataStr
// }


// const data = "11d01100030314255501122506720808252452555155229228063224129325522520660000.....................^..........^...........................h..^^.........^^..........^..........^....................^^^"

// function Parse_Recieved(test) {

//     console.log(test)
//     test = Parse_Player_Update(test);
//     console.log(test)
//     // test = Update_Loot(test, direction);
//     console.log(test)
//     // test = Update_Inventory(test);
//     // console.log(test)
//     // test = Update_Equipment(test);
//     // console.log(test)

}
// Parse_Recieved(data)


