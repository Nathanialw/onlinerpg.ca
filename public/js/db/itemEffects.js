'use strict'
import { Strip_Leading_Zeroes } from '../utils/utils.js';

let knownUsables = new Map();

//keeps track of known item effects
export function Save_Item_Effect(dataStr) {
    const ItemID = Strip_Leading_Zeroes(dataStr.substring(0, 3))
    const EffectID = Strip_Leading_Zeroes(dataStr.substring(3));
    knownUsables.set(ItemID, EffectID)
    console.log("itemEffects: ", knownUsables)
}

