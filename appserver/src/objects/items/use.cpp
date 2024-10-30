//
// Created by desktop on 10/30/24.
//
#include "unordered_map"
#include "types.h"
#include "db.h"
#include "vector"
#include "procgen.h"

namespace Use {

     //TODO: on game start load the item db effects into this array and randomly assign them to scrolls and potions
     static std::unordered_map<ItemID, ItemEffectUID> itemEffects = {};

     ItemEffectUID Get_Item_Effect(ItemID itemID) {
	     return itemEffects[itemID];
     }

     void Init() {
	     std::vector<std::pair<std::string, std::string>> whereEquals;
	     whereEquals = {{"type", "potion"}};
	     auto PotionIDs = DB::Get_List("uID", "Items", whereEquals);
	     auto effects = DB::Get_List("uID", "itemEffects", whereEquals);

	     std::cout << "PotionIDs: " << PotionIDs.size() << std::endl;
	     std::cout << "effects: " << effects.size() << std::endl;

//	     for (int i = 0; i < itemEffects.size(); i++) {
//		     itemEffects[i] = i;
//	     }
     }

     void Activate(ItemEffectUID effectID) {
	     if (effectID == 0) {
		     std::cout << "Not usable." << std::endl;
		     return;
	     }
	     std::cout << "Using Item!" << (int)effectID << std::endl;
     };
}