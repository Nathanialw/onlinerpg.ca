'use strict'

//defines an item, used for Inventory, Equipment and Loot
export let item = {
    Texture: null,
    Border: null,
    ItemID: "0",
    Rarity: 0,
    Durability: "",
    Modifiers: [],
    ModStrings: [],
    IconPath: "none"
};

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


let modType = [
    "damage",
    "armor",
    "health",
    "mana",
    "strength",
    "dexterity",
    "intelligence",
    "wisdom",
    "constitution",
    "luck",
    "speed",
    "attack speed",
    "crit chance",
    "crit damage",
    "block chance",
    "block amount",
    "dodge chance",
    "health regen",
    "mana regen",
    "life steal",
    "mana steal",
    "experience",
    "gold",
    "magic find",
    "item find",
    
    "fire resistance",
    "ice resistance",
    "lightning resistance",
    "poison resistance",
    "arcane resistance",

    "fire damage",
    "ice damage",
    "lightning damage",
    "poison damage",
    "arcane damage",

    "fire penetration",
    "ice penetration",
    "lightning penetration",
    "poison penetration",
    "arcane penetration",

    "fire absorption",
    "ice absorption",
    "lightning absorption",
    "poison absorption",
    "arcane absorption",
    
    "fire reflection",
    "ice reflection",
    "lightning reflection",
    "poison reflection",
    "arcane reflection",
]



export let Mod = {
    type: 0,    //modType index
    minValue: 0,
    maxValue: 0,
    text: ""    
}


function removeEventListenersFromArray(item) {
    //removes the listeners and clear the texture
    if (item.Texture && item.removeAllListeners) {
        item.removeAllListeners();
    }

}
