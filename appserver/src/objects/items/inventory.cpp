//
// Created by desktop on 10/13/24.
//

#include "inventory.h"
#include "array"
#include "iostream"
#include "items.h"
#include "string"
#include "utils.h"

namespace Inventory {

     void Drop_Item(Items::Inventory &inventory, Items::Ground &groundItems,
                    uint8_t bag, uint8_t index) {
	     auto item = inventory[bag][index];
	     for (auto &groundItem: groundItems) {
		     if (groundItem.Empty()) {
			     groundItem.Set(item);
			     inventory[bag][index].Set_Empty();
			     return;
		     }
	     }
	     item.Print();
     }

     //only send update when an inventory change function is called
     std::string Update_Inventory(const Items::Backpack &backpack, const Items::Max_Slots &maxSlots) {
	     std::string inventoryStr;

	     for (int j = 0; j < (int) Items::BagType::SIZE; ++j) {
		     std::string bagStr;
		     std::string newBagStr;
		     uint8_t  numItems = 0;

		     for (int i = 0; i < maxSlots[j]; ++i) {
			     if (backpack.inventory[j][i].Empty())
				     continue;
			     bagStr += Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(backpack.inventory[j][i].Get_uID(), 3);

			     auto slot = Utils::Prepend_Zero_By_Digits(i, 2);
			     auto item = backpack.inventory[j][i].As_Sendable_String();
			     newBagStr += slot + item;
			     numItems++;
		     }

		     auto bagID = Utils::Prepend_Zero_By_Digits(backpack.bags[j].Get_uID(), 3);
		     auto numItemsStr = Utils::Prepend_Zero_By_Digits(numItems, 2);
		     inventoryStr +=  numItemsStr  + bagID + newBagStr;

//		     inventoryStr += Utils::Prepend_Zero_By_Digits(backpack.bags[j].Get_uID(), 3) + bagStr;
		     std::cout << "bag updated " << j << ": " << backpack.Sendable_BagID(j) + bagStr << std::endl;
		     std::cout << "_item updated string: " << newBagStr << std::endl;
	     }
	     return inventoryStr;
     }


}; // namespace Inventory
