//
// Created by desktop on 10/30/24.
//
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
#include "types.h"
#include "db.h"
#include "vector"
#include "procgen.h"
#include "unit.h"
#include "use_effects.h"

namespace Use {


     //funciton pointer to the effect


     //TODO: on game start load the item db effects into this array and randomly assign them to SCROLLS as well
     void Init() {
	     auto PotionIDs = DB::Get_List("uID", "Items", {{"type", "potion"}, {"equipSlot", "consumable"}});
	     auto effects = DB::Get_List("uID", "itemEffects", {{"type", "potion"}});
	     std::cout << "PotionIDs size: " << PotionIDs.size() << std::endl;
	     std::cout << "effects size: " << effects.size() << std::endl;

	     Items::Init_Item_Effects_Array(PotionIDs, effects);
	     Use_Effects::Init();
     }


//TODO: when creating a new game send a message to the client to clear the knownUsables map on the client side
     void Update_Known_Usable_Effects(std::unordered_map<ItemID, ItemEffectUID> &knownUsables, Unit::Unit &unit, const websocketpp::connection_hdl &hdl, websocketpp::server<websocketpp::config::asio> &print_server, const std::pair<ItemID, ItemEffectUID> &itemEffect) {
	     //TODO: read in max value from the db
	     if (itemEffect.second == 0)
		     return;
	     uint8_t value = 40;
	     Use_Effects::Trigger_Effect(unit, itemEffect.second, value);
	     knownUsables[itemEffect.first] = itemEffect.second;
	     std::cout << "new index value: " << (int)knownUsables[itemEffect.first] << std::endl;

	     std::string updateItemEffects = "9";
	     updateItemEffects += Utils::Prepend_Zero_By_Digits(itemEffect.first, 3) + Utils::Prepend_Zero_By_Digits(itemEffect.second, 3);
	     print_server.send(hdl, updateItemEffects, websocketpp::frame::opcode::text);
     }
}

