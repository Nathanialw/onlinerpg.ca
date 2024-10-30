//
// Created by desktop on 10/30/24.
//
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
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
		     auto &effectsArray = Items::Get_Item_Effect_Array();
		     effectsArray[std::stoi(PotionIDs[i])] = std::stoi(effects[i]);
	     }
     }


     std::string Activate(Unit::Unit &unit, ItemEffectUID effectID) {
	     if (effectID == 0) {
		     std::cout << "Not usable." << int(effectID) << std::endl;
		     return "";
	     }
	     std::cout << "Using Item!" << (int) effectID << std::endl;

	     std::cout << "unit: " << unit.stats.health << std::endl;
	     unit.stats.health += Utils::Random(20, 40);
	     std::cout << "unit: " << unit.stats.health << std::endl;
	     //TODO: add item effects
	     //it needs to have an effect on the unit that uses it
	     //units are defined by                       units game.levels.objects.unitPosition[location][position]

	     return Utils::Prepend_Zero_By_Digits(effectID, 3);
     };


     void Update_Known_Usable_Effects(Unit::Unit &unit, std::unordered_map<ItemID, ItemEffectUID> &knownUsables, const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server,  const ItemEffectUID &itemEffect) {
	     auto effectStr =  Activate(unit, itemEffect);

	     if (!effectStr .empty()) {
		     auto bag = stoi(msg.substr(3, 1));
		     auto index = stoi(msg.substr(4));

		     ItemID ItemID = unit.pack.inventory[bag][index].Get_uID();
		     std::cout << "adding effect: for item: " << ItemID << " effect: " << itemEffect << std::endl;
		     knownUsables[ItemID] = itemEffect;
		     std::cout << "new index value: " << knownUsables[ItemID] << std::endl;

		     std::string updateItemEffects = "9";
		     updateItemEffects += Utils::Prepend_Zero_By_Digits(ItemID, 3) + effectStr;
		     print_server.send(hdl, updateItemEffects, websocketpp::frame::opcode::text);
	     }
     }
}

