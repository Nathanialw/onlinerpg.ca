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
	     std::string inventoryStr = Utils::Prepend_Zero_By_Digits((int)Items::BagType::SIZE, 1);

	     for (int j = 0; j < (int) Items::BagType::SIZE; ++j) {
		     uint8_t numItems = 0;
		     std::string bagStr;

		     for (int i = 0; i < maxSlots[j]; ++i) {

			     auto slot = Utils::Prepend_Zero_By_Digits(i, 2);
			     std::cout << "slot: "  << slot << std::endl;
			     auto item = backpack.inventory[j][i].As_Sendable_String();
			     bagStr += slot + item;
			     std::cout << "item : "  << slot  << "   "  << item  << std::endl;
		               numItems++;
		     }
		     std::cout << "items: " << bagStr << std::endl;

		     auto bagIndexStr = Utils::Prepend_Zero_By_Digits(j, 1);
		     auto numItemsStr = Utils::Prepend_Zero_By_Digits(numItems, 2);
		     auto bagIDStr = Utils::Prepend_Zero_By_Digits(backpack.bags[j].Get_uID(), 3);

		     inventoryStr += (bagIndexStr + numItemsStr + bagIDStr + bagStr);
		     std::cout << "bag: "  <<  bagIndexStr + numItemsStr + bagIDStr + bagStr << std::endl;
	     }
	     std::cout << "inventory full update sent: " << inventoryStr << std::endl;
	     return inventoryStr;
     }


     //only send update when an inventory change function is called
     std::string Get_Inventory(const Items::Backpack &backpack,  std::vector<std::pair<uint8_t, uint8_t>> &updateItems) {

	     //  numBags           bag          numItems          slot       bagID          item
	     //         "0"                    "0"                   "00"               "00"         "000"           "0x"
	     if (updateItems.empty())
		     return "0";

	     std::cout << "num items to update: "  <<  updateItems.size() << std::endl;

	     std::string bagStr[(int) Items::BagType::SIZE]{};
	     uint8_t numItems[(int) Items::BagType::SIZE]{};

	     for (const auto &update: updateItems) {
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
		     auto bagIndexStr = Utils::Prepend_Zero_By_Digits(j, 1);
		     inventoryStr += bagIndexStr;

		     auto numItemsStr = Utils::Prepend_Zero_By_Digits(numItems[j], 2);
		     auto bagIDStr = Utils::Prepend_Zero_By_Digits(backpack.bags[j].Get_uID(), 3);
		     inventoryStr += numItemsStr += bagIDStr += bagStr[j];
	     }

	     updateItems.clear();
	     std::cout << "inventory update sent: " << inventoryStr << std::endl;
	     return inventoryStr;
     }


}; // namespace Inventory
