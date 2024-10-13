//
// Created by desktop on 10/13/24.
//

#include "equipment.h"
#include "string"
#include "array"
#include "iostream"
#include "items.h"
#include "utils.h"
#include "db.h"

namespace Equipment {


  int Get_Equip_Slot() {

    return 1;
  };


  //set equipment slot index to itemID
  //clear inventory slot index

  std::string Equip_Item(std::array<std::array<int, 16>, 4> &inventory, std::array<int, (int)Items::ItemSlot::SIZE>  &equipment, uint8_t index) {
    int itemID = inventory[(int)Items::BagType::Items][index];
//    int inventoryIndex;
//    //search for first empty slot in inventory
//
//
//    for (int i = 0; i < inventory[(int)Items::BagType::Items].size(); ++i) {
//      if (inventory[(int)Items::BagType::Items][i] == 0) {
//        inventoryIndex = i;
//        std::cout << "picked up item: " << itemID << " inserted at index: " << inventoryIndex << std::endl;
//        break;
//      }
//
//      if (i == inventory[(int)Items::BagType::Items].size() - 1) {
//        std::cout << "inventory full" << std::endl;
//        return " ";
//      }
//    }
    std::cout << "itemID: " << itemID << std::endl;

    auto slot = DB::Query("equipSlot", "Items", "uID", "1");; //retrieve slot using itemID from the db
    std::cout << "equip slot: " << slot << std::endl;
//    equipment[slot] = inventory[(int)Items::BagType::Items][index];


    // add item to inventory array
//    inventory[Items::BagType::Items][inventoryIndex] = itemID;
    //remove from loot array and resize
//    for (int i = index; i < loot.size() - 1; ++i) {
//      loot[i] = loot[i + 1];
//    }
//    loot[loot.size() - 1] = 0; // Set the last element to 0

    // return the index of the inventory to update and the index of the item in the db
//    std::string inventoryStr = Utils::Prepend_Zero_By_Digits(inventoryIndex, 2) + Utils::Prepend_Zero_By_Digits(itemID, 3);
    return "sdas";
  }
};
