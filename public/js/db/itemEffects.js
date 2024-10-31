'use strict'
import { Strip_Leading_Zeroes } from '../utils/utils.js';
import { Get_Consumable } from './db.js';   

let knownUsables = new Map();

//keeps track of known item effects
export function Save_Item_Effect(dataStr) {
    const ItemID = Strip_Leading_Zeroes(dataStr.substring(0, 3))
    const EffectID = Strip_Leading_Zeroes(dataStr.substring(3));
    knownUsables.set(ItemID, EffectID)
}

export async function Init_Item_Effects() {
    //get all potions from the db
    let consumables = await Get_Consumable("uID", "Items", "equipslot", "consumable");
    for (let i = 0; i < consumables.length; ++i) {
        knownUsables.set(String(consumables[i].uID), "0")
    } 
}

export function Get_Item_Effect_UID(ItemID) {
    return knownUsables.get(String(ItemID));
}