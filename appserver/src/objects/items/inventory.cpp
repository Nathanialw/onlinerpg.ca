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

  std::string Update_Inventory(std::array<std::array<int, 16>, 4> &inventory) {
    std::cout << "inventory updated" << std::endl;
    std::string inventoryStr;
    uint8_t numItems = 0;
    auto items = inventory[Items::BagType::Items];
    for (int i = 0; i < items.size(); ++i) {
      if (items[i] == 0)
        break;
      numItems++;
      inventoryStr += Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(items[i], 3);
    }

    std::cout << "inventory updated: " << Utils::Prepend_Zero_By_Digits(numItems, 2) + inventoryStr << std::endl;
    return Utils::Prepend_Zero_By_Digits(numItems, 2) + inventoryStr;
  }

};
