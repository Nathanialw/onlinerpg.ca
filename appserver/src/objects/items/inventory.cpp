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

     std::string Update_Inventory(const Items::Backpack &backpack,
                                  const Items::Max_Slots &maxSlots) {
	     std::cout << "inventory updated" << std::endl;
	     std::string inventoryStr;

	     // each itme needs
	     //   the uID of the icon,  3
	     //   the rarity,           1
	     //   the durability,       3
	     //   the modifiers         num +  3*num

	     for (int j = 0; j < (int) Items::BagType::SIZE; ++j) {
		     std::string bagStr;
		     std::string newBagStr;

		     for (int i = 0; i < maxSlots[j]; ++i) {
			     bagStr += Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(backpack.inventory[j][i].Get_uID(), 3);
			     newBagStr += backpack.inventory[j][i].As_Sendable_String();
		     }

		     inventoryStr += Utils::Prepend_Zero_By_Digits(backpack.bags[j].Get_uID(), 3) + bagStr;
		     std::cout << "bag updated " << j << ": " << Utils::Prepend_Zero_By_Digits(backpack.bags[j].Get_uID(), 3) + bagStr << std::endl;
		     std::cout << "_item updated string: " << newBagStr << std::endl;
	     }
	     return inventoryStr;
     }


}; // namespace Inventory
