//
// Created by desktop on 10/22/24.
//
#include "backpack.h"
#include "items.h"
#include "db.h"
#include <iostream>

namespace Backpack {

  uint8_t Equip_Bag(Items::Backpack &pack, Items::ItemID itemID, uint8_t invSlot, uint8_t bag, uint8_t bagSlot) {
    auto temp = pack.bags[bagSlot];
    pack.bags[bagSlot] = itemID;
    uint8_t tempMaxSlots = pack.maxSlots[bagSlot];
    pack.maxSlots[bagSlot] = stoi(DB::Query("slots", "Items", "uID", std::to_string(itemID)));
    pack.inventory[bag][invSlot] = temp;

    return tempMaxSlots;
  }

  void Unequip_Bag(Items::Backpack &pack, uint8_t bagSlot) {
    auto temp = pack.bags[bagSlot];
    pack.bags[bagSlot] = 0;

    for (int j = 0; j < (int)Items::BagType::Scrolls; ++j) {
      for (int i = 0; i < pack.maxSlots[j]; ++i) {
        if (pack.inventory[j][i] == 0) {
          pack.inventory[j][i] = temp;
          break;
        }
      }
    }
  }

  bool Check_Space_Item_Drop(Items::Backpack &pack, Items::Ground &groundItems, uint8_t bagSlot, Items::ItemID itemID) {
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
        auto itemIDdrop = pack.inventory[bagSlot][i];
        if (itemIDdrop != 0) {
          for (auto &groundItem : groundItems) {
            if (groundItem == 0) {
              groundItem = itemIDdrop;
              std::cout << "item dropped: " << itemIDdrop
                        << " now on the ground: " << groundItem << std::endl;
              pack.inventory[bagSlot][i] = 0;
              break;
            }
          }
        }
        std::cout << "items dropped: " << itemIDdrop << std::endl;
      }
    }
  }

  void Equip_Bag(Items::Backpack &pack, Items::Ground &groundItems, uint8_t invSlot, uint8_t bag, Items::BagType bagSlot) {
    auto itemID = pack.inventory[bag][invSlot];

    if (bagSlot == Items::BagType::Items0) {
      //determine which bag to equip
      if (pack.bags[(int)Items::BagType::Items0] == 0) {
        bagSlot = Items::BagType::Items0;
      } else if (pack.bags[(int)Items::BagType::Items1] == 0) {
        bagSlot = Items::BagType::Items1;
      }
    }
    auto iBagSlot = (int)bagSlot;

    if (!Check_Space_Item_Drop(pack, groundItems, iBagSlot, itemID))
      return;
    auto tempMaxSlots = Equip_Bag(pack, itemID, invSlot, bag, iBagSlot);
    Drop_Items(pack, groundItems, iBagSlot, tempMaxSlots);
  }
}
