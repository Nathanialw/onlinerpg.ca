//
// Created by desktop on 10/22/24.
//
#include "backpack.h"
#include "items.h"
#include "db.h"
#include <iostream>

namespace Backpack {

  uint8_t Equip_Bag(Items::Backpack &pack, Items::Item item, uint8_t invSlot, uint8_t bag, uint8_t bagSlot) {
    auto temp = pack.bags[bagSlot];
    pack.bags[bagSlot] = item;
    uint8_t tempMaxSlots = pack.maxSlots[bagSlot];
    pack.maxSlots[bagSlot] = stoi(DB::Query("slots", "Items", "uID", std::to_string(item.uID)));
    pack.inventory[bag][invSlot] = temp;

    return tempMaxSlots;
  }

  void Unequip_Bag(Items::Backpack &pack, uint8_t bagSlot) {
    std::cout << "unequipping bag" << std::endl;
    auto temp = pack.bags[bagSlot];
    pack.bags[bagSlot].Set_Empty();

    for (int j = 0; j < (int)Items::BagType::Scrolls; ++j) {
      for (int i = 0; i < pack.maxSlots[j]; ++i) {
        if (pack.inventory[j][i].Empty()) {
          pack.inventory[j][i] = temp;
          std::cout << "bag unequipped at slot: " << bagSlot << std::endl;
          break;
        }
      }
    }
    std::cout << "no space in inventory to unequip bag" << std::endl;
  }

  bool Check_Space_Item_Drop(Items::Backpack &pack, Items::Ground &groundItems, uint8_t bagSlot, Items::ItemID itemID) {
    //check how many slots the bag has
    auto newBagSlots = stoi(DB::Query("slots", "Items", "uID", std::to_string(itemID)));
    int numItemsInInventory = 0;
    for (const auto &bagItem : pack.inventory[bagSlot]) {
      if (!bagItem.Empty()) {
        numItemsInInventory++;
      }
    }

    int numItemsToDrop = numItemsInInventory - newBagSlots;

    if (numItemsToDrop > 0) {
      std::cout << "old bag has more occupied slots than the new bag has total slots" << std::endl;

      // check how much space the ground cell has
      int occupiedGroundSpace = 0;
      for (const auto &groundItem : groundItems) {
        if (groundItem.Empty()) {
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
        return false;
      }
    }

    //equip the bag
    return true;
  }

  void Drop_Items(Items::Backpack &pack, Items::Ground &groundItems, uint8_t bagSlot, uint8_t tempMaxSlots) {
    //throw away items if the bag is overfilled
    if (pack.maxSlots[bagSlot] < tempMaxSlots) {
      //drop the items if the bag is overfilled
      for (int i = pack.maxSlots[bagSlot]; i < tempMaxSlots; ++i) {
        auto itemDrop = pack.inventory[bagSlot][i];
        if (!itemDrop.Empty()) {
          for (auto &groundItem : groundItems) {
            if (groundItem.Empty()) {
              groundItem = itemDrop;
              std::cout << "item dropped: " << itemDrop.uID << " now on the ground: " << groundItem.uID << std::endl;
              pack.inventory[bagSlot][i].Set_Empty();
              break;
            }
          }
        }
        std::cout << "items dropped: " << itemDrop.uID << std::endl;
      }
    }
  }

  void Equip_Bag(Items::Backpack &pack, Items::Ground &groundItems, uint8_t invSlot, uint8_t bag, Items::BagType bagSlot) {
    auto item = pack.inventory[bag][invSlot];

    if (bagSlot == Items::BagType::Items0) {
      //determine which bag to equip
      if (pack.bags[(int)Items::BagType::Items0].Empty()) {
        bagSlot = Items::BagType::Items0;
      } else if (pack.bags[(int)Items::BagType::Items1].Empty()) {
        bagSlot = Items::BagType::Items1;
      }
    }
    auto iBagSlot = (int)bagSlot;

    if (!Check_Space_Item_Drop(pack, groundItems, iBagSlot, item.uID))
      return;
    auto tempMaxSlots = Equip_Bag(pack, item, invSlot, bag, iBagSlot);
    Drop_Items(pack, groundItems, iBagSlot, tempMaxSlots);
  }
}
