//
// Created by desktop on 10/12/24.
//
#include "loot.h"
#include "components.h"
#include "iostream"
#include "utils.h"
#include "items.h"
#include "db.h"

namespace Loot {

  void Generate_Loot(Items::Ground &items) {
    uint8_t numItems = Utils::Random(1, 4);
    for (int i = 0; i < numItems; ++i) {
      uint8_t itemID = Utils::Random(1 , DB::Get_Num_Items());
      std::cout << "item dropped: " << itemID << std::endl;
      items[i] = itemID;
    }
  }

  std::string Query_Loot(Items::Ground &items) {
    std::string itemsStr;
    int size = 0;
    for (auto item : items) {
      if (item == 0)
        break;
      itemsStr += Utils::Prepend_Zero_By_Digits(item, 3);
      size++;
    }
    if (size == 0)
      return "0";
    itemsStr = Utils::Prepend_Zero_By_Digits(size, 2) + itemsStr;
    std::cout << "items found and prepended with number of: " << itemsStr << std::endl;
    return itemsStr;
  }

  std::string Pick_Up_Item(Items::Ground &loot, Items::Inventory &inventory, const Items::Max_Slots &maxSlots, uint8_t index) {
    int itemID = loot[index];
    int inventoryIndex = 999;

    std::cout << "picked up item: " << itemID << std::endl;
    auto type = DB::Query("type", "items", "uID", std::to_string(itemID));
    std::cout << "item type: " << type << std::endl;
    auto bagIndex = stoi(DB::Query("slotNum", "equipSlots", "type", type));
    std::cout << "bag index: " << bagIndex << std::endl;

    //get the type of item items/scroll/potion
      //put it in the preferred bag
      //if bag is full, put it in the items bag
      //if items bag is full, return "inventory full"

    //search for first empty slot in inventory
    for (int i = 0; i < maxSlots[bagIndex]; ++i) {
      if (inventory[bagIndex][i] == 0) {
        inventoryIndex = i;
        std::cout << "picked up item: " << itemID << " inserted at index: " << inventoryIndex << std::endl;
        break;
      }
    }

    if (bagIndex == 0 && 999 == inventoryIndex) {
      bagIndex++;
      for (int i = 0; i < maxSlots[bagIndex]; ++i) {
        if (inventory[bagIndex][i] == 0) {
          inventoryIndex = i;
          std::cout << "picked up item: " << itemID << " inserted at index: " << inventoryIndex << std::endl;
          break;
        }
      }
    }

    if (999 == inventoryIndex) {
      std::cout << "inventory full" << std::endl;
      return " ";
    }

    // add item to inventory array
    inventory[bagIndex][inventoryIndex] = itemID;
    //remove from loot array and resize
    for (int i = index; i < loot.size() - 1; ++i) {
      loot[i] = loot[i + 1];
    }
    loot[loot.size() - 1] = 0; // Set the last element to 0

    // return the index of the inventory slot to update and the index of the item in the db
    std::string inventoryStr = Utils::Prepend_Zero_By_Digits(inventoryIndex, 2) + Utils::Prepend_Zero_By_Digits(itemID, 3);
    return inventoryStr;
  }
}