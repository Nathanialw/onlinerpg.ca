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

  //set equipment slot index to itemID
  //clear inventory slot index

  void Equip_Item(std::array<std::array<int, 16>, 4> &inventory, std::array<int, (int)Items::ItemSlot::SIZE>  &equipment, uint8_t index) {
    int itemID = inventory[(int)Items::BagType::Items][index];
    std::cout << "itemID: " << itemID << std::endl;

    auto slot = DB::Query("equipSlot", "Items", "uID", std::to_string(itemID)); //retrieve slotName using itemID from the db
    std::cout << "equip slot: " << slot << std::endl;
    auto slotNum = DB::Query("slotNum", "equipSlots", "slotName", slot); //retrieve slotNum using slotName from the db
    std::cout << "equip slot num: " << slotNum << std::endl;

    //swap inventory itemID with equipment slot itemID
    auto swapItemID = equipment[stoi(slotNum)];
    equipment[stoi(slotNum)] = inventory[(int)Items::BagType::Items][index];
    std::cout << "equipment slot: " << equipment[stoi(slotNum)] << std::endl;
    inventory[(int)Items::BagType::Items][index] = swapItemID;
  }


  std::string Get_Equipment(std::array<int, (int)Items::ItemSlot::SIZE> &equipment) {
    std::string equipmentStr = Utils::Prepend_Zero_By_Digits(equipment.size(), 2);
    for (int i = 0; i < equipment.size(); ++i) {
      auto equipSlot = equipment[i];
      equipmentStr += Utils::Prepend_Zero_By_Digits(i , 2) + Utils::Prepend_Zero_By_Digits(equipSlot, 3);
    }
    //first 2 chars is equip size
    //each 5 of the next chars is equip slot and itemID
    return equipmentStr;
  }
};