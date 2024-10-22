//
// Created by desktop on 10/13/24.
//

#include "inventory.h"
#include "string"
#include "array"
#include "iostream"
#include "items.h"
#include "utils.h"

namespace Inventory {


  void Drop_Item(Items::Inventory &inventory, Items::Ground &groundItems, uint8_t bag, uint8_t index) {
    auto itemID = inventory[bag][index];
    for (auto & groundItem : groundItems) {
      if (groundItem == 0) {
        groundItem = itemID;
        inventory[bag][index] = 0;
        return;
      }
    }
    std::cout << "item dropped: " << itemID << std::endl;
  }

  std::string Update_Inventory(const Items::Backpack &backpack, const Items::Max_Slots &maxSlots) {
    std::cout << "inventory updated" << std::endl;
    std::string inventoryStr;

    for (int j = 0; j < (int)Items::BagType::SIZE; ++j) {
      std::string bagStr;

      for (int i = 0; i < maxSlots[j]; ++i) {
        bagStr += Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(backpack.inventory[j][i], 3);
      }

      inventoryStr += Utils::Prepend_Zero_By_Digits(backpack.bags[j], 3) + bagStr;
      std::cout << "bag updated " << j << ": " <<  Utils::Prepend_Zero_By_Digits(backpack.bags[j], 3) + bagStr << std::endl;
    }
    return inventoryStr;
  }

  std::string Get_Inventory(Items::Inventory &inventory) {
    auto items = inventory[(int)Items::BagType::Items0];
    std::string itemsStr = Utils::Prepend_Zero_By_Digits(items.size(), 2);

    for (int i = 0; i < items.size(); ++i) {
      itemsStr +=  Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(items[i], 3);
    }

    std::cout << "inventories sent: " << itemsStr << std::endl;
    return itemsStr;
  }

};
