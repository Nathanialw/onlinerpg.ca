//
// Created by desktop on 10/12/24.
//

#include "items.h"

namespace Items {

     static std::unordered_map<ItemID, ItemEffectUID> itemEffects = {};

     std::unordered_map<ItemID, ItemEffectUID> &Get_Item_Effect_Array() {
	     return itemEffects;
     }

     ItemEffectUID Get_Item_Effect(ItemID itemID) {
	     return itemEffects[itemID];
     }
}