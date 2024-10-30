//
// Created by desktop on 10/30/24.
//
#include "unordered_map"
#include "types.h"

namespace Use {

     //TODO: on game start load the item db effects into this array and randomly assign them to scrolls and potions
     static std::unordered_map<ItemID, ItemEffectUID> itemEffects = {};

     ItemEffectUID Get_Item_Effect(ItemID itemID) {
	     return itemEffects[itemID];
     }

     void Init() {
	     for (int i = 0; i < itemEffects.size(); i++) {
		     itemEffects[i] = i;
	     }
     }

}