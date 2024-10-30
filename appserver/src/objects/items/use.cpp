//
// Created by desktop on 10/30/24.
//
#include "unordered_map"
#include "types.h"
#include "db.h"
#include "vector"
#include "procgen.h"
//#include "items.h"
#include "unit.h"

namespace Use {

     //TODO: on game start load the item db effects into this array and randomly assign them to scrolls and potions


     void Init() {
	     std::vector<std::pair<std::string, std::string>> whereEquals;
	     whereEquals = {{"type", "potion"}};
	     auto PotionIDs = DB::Get_List("uID", "Items", whereEquals);
	     auto effects = DB::Get_List("uID", "itemEffects", whereEquals);

	     std::cout << "PotionIDs: " << PotionIDs.size() << std::endl;
	     std::cout << "effects: " << effects.size() << std::endl;

	     for (int i = 0; i < PotionIDs.size(); i++) {
		     Items::itemEffects[std::stoi(PotionIDs[i])] = std::stoi(effects[i]);
	     }
     }




     void Activate(Unit::Unit &unit, ItemEffectUID effectID) {
	     if (effectID == 0) {
		     std::cout << "Not usable." << int(effectID) << std::endl;
		     return;
	     }
	     std::cout << "Using Item!" << (int)effectID << std::endl;

	     std::cout<< "unit: " << unit.stats.health << std::endl;
	     unit.stats.health += Utils::Random(20, 40);
	     std::cout<< "unit: " << unit.stats.health << std::endl;
	     //TODO: add item effects
	     //it needs to have an effect on the unit that uses it
	     //units are defined by                       units game.levels.objects.unitPosition[location][position]

     };
}