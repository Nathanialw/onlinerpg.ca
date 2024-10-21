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

  void Drop_Item(Items::bags &inventory, Items::ground &groundItems, uint8_t index) {
    auto itemID = inventory[(int)Items::BagType::Items][index];
    for (unsigned char & groundItem : groundItems) {
      if (groundItem == 0) {
        groundItem = itemID;
        inventory[(int)Items::BagType::Items][index] = 0;
        return;
      }
    }
    std::cout << "item dropped: " << itemID << std::endl;
  }

  std::string Update_Inventory(Items::bags &inventory, const Items::bagSlots &maxSlots) {
    std::cout << "inventory updated" << std::endl;
    std::string inventoryStr;

//    auto items = inventory[(int)Items::BagType::Items];
    for (int j = 0; j < (int)Items::BagType::SIZE; ++j) {
      std::string bagStr;
      uint8_t numItems = 0;

      for (int i = 0; i < maxSlots[j]; ++i) {
        bagStr += Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(inventory[j][i], 3);
        numItems++;
      }

      inventoryStr += Utils::Prepend_Zero_By_Digits(numItems, 2) + bagStr;
      std::cout << "bag updated " << j << ": " <<  Utils::Prepend_Zero_By_Digits(numItems, 2) + bagStr << std::endl;
    }
    return inventoryStr;
  }

  std::string Get_Inventory(Items::bags &inventory) {
    auto items = inventory[(int)Items::BagType::Items];
    std::string itemsStr = Utils::Prepend_Zero_By_Digits(items.size(), 2);

    for (int i = 0; i < items.size(); ++i) {
      itemsStr +=  Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(items[i], 3);
    }

    std::cout << "inventories sent: " << itemsStr << std::endl;
    return itemsStr;
  }

};
