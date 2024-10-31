//
// Created by desktop on 10/22/24.
//

#include "update_items.h"
#include "backpack.h"
#include "equipment.h"
#include "game.h"
#include "inventory.h"
#include "items.h"
#include "loot.h"
#include "string"
#include <iostream>
#include "array"

namespace Update_Items {

     enum Panel {
	NONE,
	ALT,
	CTRL,
	SHIFT,
     };

     std::unordered_map<std::string, Panel> panelMap = {
	{"0", Panel::NONE},
	{"a", Panel::ALT},
	{"c", Panel::CTRL},
	{"s", Panel::SHIFT}
     };

     struct Item {
	Panel modKey = Panel::NONE;
	uint8_t bag = 0;
	uint8_t index = 0;
     };


     std::pair<ItemID, ItemEffectUID> Loot(Game::Instance &game, const Item &item) {
	     std::cout << "Looting item at index: " << item.index << std::endl;
	     Loot::Pick_Up_Item(game.Get_Items(), game.Get_Player().pack.inventory, game.Get_Player().pack.maxSlots, item.index, game.updateInventory);
	     return {0, 0};
     }

     std::pair<ItemID, ItemEffectUID> Inventory(Game::Instance &game, const Item &item) {
	     std::cout << "interacting with inventory at index: " << item.index << std::endl;
	     switch (item.modKey) {
		     case NONE: { // equip standard / use item
			     std::cout << "unmodded clicked: " << item.modKey << std::endl;
			     return Equipment::Use_Item(game.Get_Player().pack, game.Get_Items(), game.Get_Player().equipment, item.index, item.bag, game.updateInventory, game.updateEquipment, game.updateBag);
		     }
		     case CTRL: { // throw away
			     std::cout << "control clicked: " << item.modKey << std::endl;
			     Inventory::Drop_Item(game.Get_Player().pack.inventory, game.Get_Items(), item.bag, item.index, game.updateInventory);
			     break;
		     }
		     case ALT: { // equip offhand
			     std::cout << "alt clicked: " << item.modKey << std::endl;
			     Equipment::Equip_Second_Item(game.Get_Player().pack, game.Get_Items(), game.Get_Player().equipment, item.index, item.bag, game.updateInventory, game.updateEquipment, game.updateBag);
			     break;
		     }
		     case SHIFT: { //
			     std::cout << "shift clicked, thusfar unused" << std::endl;
			     break;
		     }
	     }
	     return {0, 0};
     }

     std::pair<ItemID, ItemEffectUID> Equipment(Game::Instance &game, const Item &item) {
	     std::cout << "interacting with equipment at index: " << item.index << std::endl;
	     Equipment::Unequip_Item(game.Get_Player().pack.inventory, game.Get_Player().equipment, item.index, game.Get_Player().pack.maxSlots, game.updateInventory, game.updateEquipment);
	     return {0, 0};
     }

     std::pair<ItemID, ItemEffectUID> Bags(Game::Instance &game, const Item &item) {
	     std::cout << "interacting with bags at index: " << item.index << std::endl;
	     switch (item.modKey) {
		     case NONE: {  // equip standard / use item
			     std::cout << "unmodded clicked: " << item.modKey << std::endl;
		     }
		     case CTRL: {  // unequip bag
			     std::cout << "control clicked: " << item.modKey << std::endl;
			     //          Backpack::Unequip_Bag(game.Get_Player().pack, stoi(index));
		     }
		     case ALT: {  // equip second bag
			     std::cout << "alt clicked: " << item.modKey << std::endl;
		     }
		     case SHIFT: {  //
			     std::cout << "shift clicked, thusfar unused" << std::endl;
		     }
	     }
	     return {0, 0};
     }

     std::array<std::function<std::pair<ItemID, ItemEffectUID>(Game::Instance &game, const Item &item)>, 4> itemInteractions = {
	Loot,
	Inventory,
	Equipment,
	Bags
     };

     std::pair<ItemID, ItemEffectUID> Update(const std::string &msg, Game::Instance &game) {
	     std::cout << "message: " << msg << std::endl;
	     Item item;
	     item.modKey = panelMap[msg.substr(2, 1)];
	     item.bag = stoi(msg.substr(3, 1));
	     item.index = stoi(msg.substr(4));
	     std::cout << "panel clicked: " << msg.substr(1, 1) << std::endl;

	     uint8_t panel = stoi(msg.substr(1, 1));

	     return itemInteractions[panel](game, item);
     }
}
