#pragma once
//
// Created by desktop on 10/12/24.
//

#ifndef BROWSERRPG_ITEMS_H
#define BROWSERRPG_ITEMS_H

#include "array"
#include "string"


namespace Items {
  enum class BagType {
    Items0,
    Items1,
    Scrolls,
    Potions,
    Keys,
    SIZE,
  };

  enum class ItemSlot {
    Helmet,
    amulet,
    cloak,
    chest,
    belt,
    gloves,
    leggings,
    boots,
    ring0,
    ring1,
    trinket0,
    trinket1,
    mainHand,
    offHand,
    twoHanded,
    ammo,
    SIZE,
  };

  typedef uint16_t ItemID;

  struct Item {
    ItemID uID = 0;

    //it needs to know which modifiers it has
    std::array<uint8_t, 7> modifiers{}; //keys to the static modifiers in the db

    //which icon it has
    uint8_t icon{}; //0-255 name of the icon png in the directory referenced in the db

    uint8_t rarity{}; //0-5
    uint8_t durability{}; //0-100

    //requirements

    Item() {
      //figure out what level of item to create
      //get the power level of the item
      //get a random uID from the db
      //roll for modifers
      //roll for rarity

      //set the icon
      //set the durability
      durability = 100; //probably will be random later
    }

    bool Empty() const {
      if (uID == 0)
        return true;
      return false;
    }

    void Set_Empty() {
      uID = 0;
      icon = 0; //0-255 name of the icon png in the directory referenced in the db
      rarity = 0; //0-5
      durability = 0; //0-100
      for (auto &modifier : modifiers) {
        modifier = 0;
      }
    }
  };

  typedef std::array<Item, (uint8_t)BagType::SIZE> Bags;
  typedef std::array<uint8_t, (uint8_t)BagType::SIZE> Max_Slots;
  typedef std::array<std::array<Item, 14>, (uint8_t)BagType::SIZE> Inventory;



  struct Backpack {
    Inventory inventory{};
    Bags bags{};
    Max_Slots maxSlots{};

    uint16_t copper = 0;
    uint16_t silver = 0;
    uint16_t gold = 0;
  };

  typedef std::array<Item, 14> Ground;
  typedef std::array<Item, (uint8_t)ItemSlot::SIZE> Equipped;
}

#endif // BROWSERRPG_ITEMS_H



















































































