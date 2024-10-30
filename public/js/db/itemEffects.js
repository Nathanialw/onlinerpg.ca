'use strict'
import { Strip_Leading_Zeroes } from '../utils/utils.js';

let itemEffects = new Map();


//keeps track of known item effects
export function Save_Item_Effect(dataStr) {
    ItemID = Strip_Leading_Zeroes(dataStr.substring(0, 3))
    console.log("ItemID: ", ItemID)
    EffectID = Strip_Leading_Zeroes(dataStr.substring(3));
    console.log("EffectID: ", EffectID)
    itemEffects.set(ItemID, EffectID)
    console.log("itemEffects: ", itemEffects)
}