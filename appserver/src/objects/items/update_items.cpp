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

namespace Update_Items {

     void Update(const std::string &msg, Game::Instance &game) {
	     //      response = "2";
	     std::cout << "message: " << msg << std::endl;
	     auto type = msg.substr(1, 1);
	     auto mod = msg.substr(2, 1);
	     auto bag = msg.substr(3, 1);
	     auto index = msg.substr(4);
	     std::cout << "panel clicked: " << type << std::endl;

	     if (type == "0") {
		     std::cout << "Looting item at index: " << index << std::endl;
		     Loot::Pick_Up_Item(
			game.Get_Items(), game.Get_Player().pack.inventory, game.Get_Player().pack.maxSlots, stoi(index));
	     } else if (type == "1") {
		     std::cout << "interacting with inventory at index: " << index << std::endl;
		     if (mod == "c") { // throw away
			     std::cout << "control clicked: " << mod << std::endl;
			     Inventory::Drop_Item(game.Get_Player().pack.inventory, game.Get_Items(), stoi(bag), stoi(index));
		     } else if (mod == "a") { // equip offhand
			     std::cout << "alt clicked: " << mod << std::endl;
			     Equipment::Equip_Second_Item(game.Get_Player().pack, game.Get_Items(), game.Get_Player().equipment, stoi(index), stoi(bag));
		     } else if (mod == "s") { //
			     std::cout << "shift clicked, thusfar unused" << std::endl;
		     } else { // equip standard / use item
			     std::cout << "unmodded clicked: " << mod << std::endl;
			     Equipment::Use_Item(game.Get_Player().pack, game.Get_Items(), game.Get_Player().equipment, stoi(index), stoi(bag));
		     }
	     } else if (type == "2") {
		     std::cout << "interacting with equipment at index: " << index << std::endl;
		     Equipment::Unequip_Item(game.Get_Player().pack.inventory, game.Get_Player().equipment, index, game.Get_Player().pack.maxSlots);
	     } else if (type == "3") {
		     std::cout << "interacting with bags at index: " << index << std::endl;
		     if (mod == "c") { // unequip bag
			     std::cout << "control clicked: " << mod << std::endl;
			     //          Backpack::Unequip_Bag(game.Get_Player().pack, stoi(index));
		     } else if (mod == "a") { // equip second bag
			     std::cout << "alt clicked: " << mod << std::endl;
		     } else if (mod == "s") { //
			     std::cout << "shift clicked, thusfar unused" << std::endl;
		     } else { // equip standard / use item
			     std::cout << "unmodded clicked: " << mod << std::endl;
		     }
	     }
     }

}
