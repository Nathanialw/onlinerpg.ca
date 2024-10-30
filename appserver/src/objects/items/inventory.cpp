//
// Created by desktop on 10/13/24.
//

#include "inventory.h"
#include "array"
#include "iostream"
#include "items.h"
#include "string"
#include "utils.h"
#include <vector>

namespace Inventory {

     void Drop_Item(Items::Inventory &inventory, Items::Ground &groundItems, uint8_t bag, uint8_t index) {
	     auto item = inventory[bag][index];
	     for (auto &groundItem: groundItems) {
		     if (groundItem.Empty()) {
			     groundItem.Set(item);
			     inventory[bag][index].Set_Empty();
			     inventory[bag][index].Print();
//			     updateInventory .push_back({bag, index});
			     return;
		     }
	     }
	     item.Print();
     }

     //only send update when an inventory change function is called
     std::string Get_Inventory(const Items::Backpack &backpack, const Items::Max_Slots &maxSlots) {
	     std::string inventoryStr;

	     for (int j = 0; j < (int) Items::BagType::SIZE; ++j) {
		     std::string bagStr;
		     std::string newBagStr;
		     uint8_t numItems = 0;

		     for (int i = 0; i < maxSlots[j]; ++i) {
//			     if (backpack.inventory[j][i].Empty() && numItems == 0)
//				     continue;
			     bagStr += Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(backpack.inventory[j][i].Get_uID(), 3);

			     auto slot = Utils::Prepend_Zero_By_Digits(i, 2);
			     auto item = backpack.inventory[j][i].As_Sendable_String();
			     newBagStr += slot + item;
			     numItems++;
		     }

		     auto bagID = Utils::Prepend_Zero_By_Digits(backpack.bags[j].Get_uID(), 3);
		     auto numItemsStr = Utils::Prepend_Zero_By_Digits(numItems, 2);
		     inventoryStr += numItemsStr += bagID + newBagStr;

//		     inventoryStr += Utils::Prepend_Zero_By_Digits(backpack.bags[j].Get_uID(), 3) + bagStr;
		     std::cout << "bag updated " << j << ": " << backpack.Sendable_BagID(j) + bagStr << std::endl;
		     std::cout << "_item updated string: " << newBagStr << std::endl;
	     }
	     return inventoryStr;
     }


     //only send update when an inventory change function is called
     std::string Get_Inventory(const Items::Backpack &backpack, std::vector<std::pair<uint8_t, uint8_t>> updateItems) {

	     //  numBags           bag          numItems          slot       bagID          item
	     //         "0"                    "0"                   "00"               "00"         "000"           "0x"


	     std::string bagStr [(int)Items::BagType::SIZE];
	     uint8_t numItems [(int)Items::BagType::SIZE];


	     for (const auto &update : updateItems) {
		     std::string newBagStr;

		     auto slot = Utils::Prepend_Zero_By_Digits(update.second, 2);
		     auto item = backpack.inventory[update.first][update.second].As_Sendable_String();
		     newBagStr += slot + item;

		     auto bagID = Utils::Prepend_Zero_By_Digits(backpack.bags[update.first].Get_uID(), 3);
		     bagStr[update.first] += bagID + newBagStr;

		     numItems[update.first]++;
	     }

	     uint8_t numBags = 0;
	     for (const auto s: numItems) {
		if (s > 0)
			numBags++;
	     }
	     std::string inventoryStr = Utils::Prepend_Zero_By_Digits(numBags, 1);

	     for (int j = 0; j < (int) Items::BagType::SIZE; ++j) {
		     if (numItems[j] == 0)
			     continue;
		     auto bagIndex = Utils::Prepend_Zero_By_Digits(j, 1);
		     inventoryStr +=  bagIndex;

		     auto numItemsStr = Utils::Prepend_Zero_By_Digits(numItems[j], 2);
		     inventoryStr += numItemsStr + bagStr[j];
	     }

	     updateItems.clear();
	     return inventoryStr;
     }


}; // namespace Inventory
