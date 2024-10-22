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

  uint8_t Equip_Bag(Items::Backpack &pack, int itemID, uint8_t invSlot, uint8_t bag, uint8_t bagSlot) {
    auto temp = pack.bags[bagSlot];
    pack.bags[bagSlot] = itemID;
    uint8_t tempMaxSlots = pack.maxSlots[bagSlot];
    pack.maxSlots[bagSlot] = stoi(DB::Query("slots", "Items", "uID", std::to_string(itemID)));
    pack.inventory[bag][invSlot] = temp;

    return tempMaxSlots;
  }

  void Use_Item(Items::Backpack &pack, Items::Ground &groundItems, Items::Equipped &equipment, uint8_t invSlot, uint8_t bag) {
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
      uint8_t tempMaxSlots;
      uint8_t bagSlot = 0;

      //determine which bag to equip
      if (pack.bags[bagSlot] == 0) {
        bagSlot = 0;
      }
      else if (pack.bags[bagSlot + 1] == 0) {
        bagSlot++;
      }

      //check how many slots the bag has
      auto newBagSlots = stoi(DB::Query("slots", "Items", "uID", std::to_string(itemID)));
      int numItemsInInventory = 0;
      for (const auto &bagItem : pack.inventory[bagSlot]) {
        if (bagItem != 0) {
            numItemsInInventory++;
        }
      }

      int numItemsToDrop = numItemsInInventory - newBagSlots;

      if (numItemsToDrop > 0) {
        std::cout << "old bag has more occupied slots than the new bag has total slots" << std::endl;

        // check how much space the ground cell has
        int occupiedGroundSpace = 0;
        for (const auto &groundItem : groundItems) {
            if (groundItem == 0) {
              break;
            }
            occupiedGroundSpace++;
        }
        int groundSpace = groundItems.size() - occupiedGroundSpace;

        std::cout << "numItemsToDrop: " << numItemsToDrop << " groundSpace: " << groundSpace << std::endl;
        if (numItemsToDrop < groundSpace)
            std::cout << "plenty of space, equipping the bag" << std::endl;
        else {
            std::cout << "not enough space on the ground to equip the bag" << std::endl;
            return;
        }
      }
      tempMaxSlots = Equip_Bag(pack, itemID, invSlot, bag, bagSlot);

      //throw away items if the bag is overfilled
      if (pack.maxSlots[bagSlot] < tempMaxSlots) {
        //drop the items if the bag is overfilled
        for (int i = pack.maxSlots[bagSlot]; i < tempMaxSlots; ++i) {
          auto itemIDdrop = pack.inventory[bagSlot][i];
          for (uint8_t &groundItem : groundItems) {
            if (groundItem == 0) {
              groundItem = itemIDdrop;
              std::cout << "item dropped: " << itemIDdrop << " now on the ground: " << groundItem << std::endl;
              pack.inventory[bagSlot][i] = 0;
              break;
            }
          }
          std::cout << "items dropped: " << itemIDdrop << std::endl;
        }
      }

      //equip the bag

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


//drops

//     10
//     015
//     025
//     012
//     022
//     023
//     010
//     023
//     013
//     004
//     039

//    bags
//    020001501027
//    06000430100002000030000400005000
//    020001601000
//    020001701017
//    03000000100002000


    //equipment
//    1600000010000200003000040000500006000070000800009000100001100012000130001400015000