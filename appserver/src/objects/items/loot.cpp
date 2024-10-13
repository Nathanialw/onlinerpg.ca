//
// Created by desktop on 10/12/24.
//
#include "loot.h"
#include "components.h"
#include "iostream"
#include "utils.h"
#include "items.h"

namespace Loot {

  void Generate_Loot(std::array<uint8_t , 4> &items) {
    uint8_t numItems = rand() % 4 + 1;
    for (int i = 0; i < numItems; ++i) {
      //random between 1 and 2 as there are only 2 items currently
      uint8_t itemID = rand() % 2 + 1;
      items[i] = itemID;
    }
    std::cout << "items dropped" << std::endl;
  }

  std::string Query_Loot(std::array<uint8_t , 4> &items) {
    std::string itemsStr;
    int size = 0;
    for (auto item : items) {
      if (item == 0)
        break;
      itemsStr += Utils::Prepend_Zero_3Digit(item);
      size++;
    }
    if (size == 0)
      return "0";
    itemsStr = std::to_string(size) + itemsStr;
    std::cout << "items found and prepended with number of: " << itemsStr << std::endl;
    return itemsStr;
  }

  std::string Pick_Up_Item(std::array<uint8_t , 4> &loot, std::array<std::array<int, 16>, 4> &inventory, uint8_t index) {
    int itemID = loot[index];
    int inventoryIndex;
    //search for first empty slot in inventory
    for (int i = 0; i < inventory[Items::BagType::Items].size(); ++i) {
      if (inventory[Items::BagType::Items][i] == 0) {
            inventoryIndex = i;
            break;
      }
      if (i == inventory[Items::BagType::Items].size() - 1) {
        std::cout << "inventory full" << std::endl;
        return " ";
      }
    }

    // add item to inventory array
    inventory[Items::BagType::Items][inventoryIndex] = itemID;
    //remove from loot array and resize
    for (int i = index; i < loot.size() - 1; ++i) {
      loot[i] = loot[i + 1];
    }
    loot[loot.size() - 1] = 0; // Set the last element to 0

    // return the index of the inventory to update and the index of the item in the db
    std::string inventoryStr = Utils::Prepend_Zero_By_Digits(inventoryIndex, 2) + Utils::Prepend_Zero_By_Digits(itemID, 3);
    return inventoryStr;
  }
}