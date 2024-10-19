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

  void Drop_Item(std::array<std::array<int, 48>, 4> &inventory, std::array<uint8_t , 4> &groundItems, uint8_t index) {
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

  std::string Update_Inventory(std::array<std::array<int, 48>, 4> &inventory) {
    std::cout << "inventory updated" << std::endl;
    std::string inventoryStr;
    uint8_t numItems = 0;
    auto items = inventory[(int)Items::BagType::Items];
    for (int i = 0; i < items.size(); ++i) {
      inventoryStr += Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(items[i], 3);
      numItems++;
    }

    std::cout << "inventory updated: " << Utils::Prepend_Zero_By_Digits(numItems, 2) + inventoryStr << std::endl;
    return Utils::Prepend_Zero_By_Digits(numItems, 2) + inventoryStr;
  }

  std::string Get_Inventory(std::array<std::array<int, 48>, 4> &inventory) {
    auto items = inventory[(int)Items::BagType::Items];
    std::string itemsStr = Utils::Prepend_Zero_By_Digits(items.size(), 2);

    for (int i = 0; i < items.size(); ++i) {
      itemsStr +=  Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(items[i], 3);
    }

    std::cout << "inventories sent: " << itemsStr << std::endl;
    return itemsStr;
  }

};
