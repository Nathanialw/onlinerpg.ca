'use strict'

//defines an item, used for Inventory, Equipment and Loot

let item = {
    ItemID: "0",
    IconPath: "none",
    Texture: null,
    Border: null,
    Rarity: 0,
    Durability: "",
    Modifiers: [],
    ModStrings: [],
};

export function deepCopyItem() {
    return {
        ItemID: item.ItemID,
        IconPath: item.IconPath,
        Texture: item.Texture,
        Border: item.Border,
        Rarity: item.Rarity,
        Durability: item.Durability,
        Modifiers: [...item.Modifiers],
        ModStrings: [...item.ModStrings],
    };
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
