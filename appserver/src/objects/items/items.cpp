//
// Created by desktop on 10/12/24.
//

#include "items.h"
#include "vector"
#include <algorithm>
#include <random>

namespace Items {

     std::unordered_map<ItemID, ItemEffectUID> itemEffects = {};

     void Init_Item_Effects_Array(std::vector<std::string> &PotionIDs, std::vector<std::string> &effects) {
	     std::random_device rd;
	     std::mt19937 g(rd());
	     std::shuffle(effects.begin(), effects.end(), g);

	     for (int i = 0; i < PotionIDs.size(); i++) {
		     itemEffects[std::stoi(PotionIDs[i])] = std::stoi(effects[i]);
	     }
     }

     ItemEffectUID Get_Item_Effect(ItemID itemID) {
	     return itemEffects[itemID];
     }
}