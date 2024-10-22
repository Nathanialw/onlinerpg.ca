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

  void Swap_Item(Items::Inventory &inventory, Items::Equipped &equipment, const int equipSlot, const int invSlot, uint8_t bag) {
    auto swapItemID = equipment[equipSlot];
    equipment[equipSlot] = inventory[bag][invSlot];
    std::cout << "equipment slot now contains itemID: " << equipment[equipSlot] << std::endl;
    inventory[bag][invSlot] = swapItemID;
  }

  //set equipment slot index to itemID
  //clear inventory slot index
  void Unequip_Item(Items::Inventory &inventory, Items::Equipped &equipment, const std::string &slotNum, const Items::Max_Slots &maxSlots) {
      //swap equipment slot itemID with inventory itemID
      auto swapItemID = equipment[stoi(slotNum)];

      for (int bag = 0; bag < (int)Items::BagType::Scrolls; ++bag) {
        for (int i = 0; i < maxSlots[bag]; ++i) {
          if (inventory[bag][i] == 0) {
            inventory[bag][i] = swapItemID;
            equipment[stoi(slotNum)] = 0;
            return;
          }
        }
      }
      std::cout << "no space in inventory" << std::endl;
  }

  int Dual_Equip(Items::Equipped &equipment, int slot0, int slot1) {
      if (equipment[slot0] == 0)
        return slot0;
      else if (equipment[slot1] == 0)
        return slot1;
      else
        return slot0;
  }

  void Equip_Item(Items::Inventory &inventory, Items::Equipped &equipment, uint8_t index, const std::string &equipSlot, uint8_t bag) {
    auto slotNum = stoi(DB::Query("slotNum", "equipSlots", "slotName", equipSlot)); //retrieve slotNum using slotName from the db

    std::cout << "equip slot num: " << slotNum << std::endl;

    //if slotNum == Items::ItemSlot::mainHand, then it can fit in Items::ItemSlot::mainHand or Items::ItemSlot::offHand
    if (slotNum == (int)Items::ItemSlot::mainHand)
      slotNum = Dual_Equip(equipment, (int)Items::ItemSlot::mainHand, (int)Items::ItemSlot::offHand);
    else if (slotNum == (int)Items::ItemSlot::ring0)
      slotNum = Dual_Equip(equipment, (int)Items::ItemSlot::ring0, (int)Items::ItemSlot::ring1);
    else if (slotNum == (int)Items::ItemSlot::trinket0)
      slotNum = Dual_Equip(equipment, (int)Items::ItemSlot::trinket0, (int)Items::ItemSlot::trinket1);

    std::cout << "equip slot num: " << slotNum << std::endl;

    Swap_Item(inventory, equipment, slotNum, index, bag);
  }

  void Equip_Second_Item(Items::Inventory &inventory, Items::Equipped &equipment, uint8_t index, uint8_t bag) {
    auto itemID = inventory[bag][index];
    auto slotStr = DB::Query("equipSlot", "Items", "uID", std::to_string(itemID)); //retrieve equipSlot using itemID from the db
    auto slotNum = stoi(DB::Query("slotNum", "equipSlots", "slotName", slotStr)); //retrieve slotNum using slotName from the db

    if (slotNum == (int)Items::ItemSlot::mainHand || slotNum == (int)Items::ItemSlot::offHand) {
      Swap_Item(inventory, equipment, (int)Items::ItemSlot::offHand, index, bag);
    }
    else if (slotNum == (int)Items::ItemSlot::ring0 || slotNum == (int)Items::ItemSlot::ring1) {
      Swap_Item(inventory, equipment, (int)Items::ItemSlot::ring0, index, bag);
    }
    else if (slotNum == (int)Items::ItemSlot::trinket0 || slotNum == (int)Items::ItemSlot::trinket1) {
      Swap_Item(inventory, equipment, (int)Items::ItemSlot::trinket0, index, bag);
    }
  }

  void Use_Item(Items::Pack &pack, Items::Ground &groundItems, Items::Equipped &equipment, uint8_t invSlot, uint8_t bag) {
    int itemID = pack.inventory[bag][invSlot];
    std::cout << "itemID: " << itemID << std::endl;

    auto slotStr = DB::Query("equipSlot", "Items", "uID", std::to_string(itemID)); //retrieve equipSlot using itemID from the db
    std::cout << "equip slot: " << slotStr << std::endl;

    if (slotStr == "notEquippable") {
      // query the effect of the item and apply it
//      auto slotNum = DB::Query("slotNum", "equipSlots", "slotName", slot); //retrieve slotNum using slotName from the db
      std::cout << "item not equippable" << std::endl;
      return;
    }

    if (slotStr == "bag") {
      //equip the bag
      uint8_t tempMaxSlots;
      if (pack.bags[0] == 0) {
        pack.bags[0] = itemID;
        tempMaxSlots = pack.maxSlots[0];
        pack.maxSlots[0] = stoi(DB::Query("slots", "Items", "uID", std::to_string(itemID)));

      }
      else if (pack.bags[1] == 0) {
        pack.bags[1] = itemID;
        tempMaxSlots = pack.maxSlots[1];
        pack.maxSlots[1] = stoi(DB::Query("slots", "Items", "uID", std::to_string(itemID)));

      }
      else {
        auto temp = pack.bags[0];
        pack.bags[0] = itemID;
        tempMaxSlots = pack.maxSlots[0];
        pack.maxSlots[0] = stoi(DB::Query("slots", "Items", "uID", std::to_string(itemID)));
        pack.inventory[bag][invSlot] = temp;
      }

      if (tempMaxSlots < pack.maxSlots[bag]) {
        //drop the items if the bag is overfilled
        auto itemIDdrop = pack.inventory[bag][invSlot];
        for (int i = pack.maxSlots[bag]; i < tempMaxSlots; ++i) {
            for (unsigned char &groundItem : groundItems) {
              if (groundItem == 0) {
                groundItem = itemIDdrop;
                pack.inventory[bag][invSlot] = 0;
              }
            }
        }
        std::cout << "items dropped: " << itemIDdrop << std::endl;
      }
      return;
    }

    Equip_Item(pack.inventory, equipment, invSlot, slotStr, bag);
  }

  std::string Get_Equipment(Items::Equipped &equipment) {
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
