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

  struct Mod {
    uint8_t uID = 0;

    bool Empty() const {
      if (uID == 0)
        return true;
      return false;
    }

    void Set_Empty() {
      uID = 0;
    }

    bool operator==(const Mod &rhs) const {
      return uID == rhs.uID;
    }
  };

  struct Item {
    ItemID uID = 0; //is this not jsut the icon basically?

    //it needs to know which modifiers it has
    std::array<Mod, 8> modifiers{}; //keys to the static modifiers in the db

    //which icon it has

    uint8_t rarity{}; //0-5
    uint8_t durability{}; //0-100

    //requirements

    Item(uint8_t powerLevel = 0) {
      //passin the power level of item to create
      //get a random uID from the db of that level
      //roll for rarity
      //roll for modifers based on rarity

      //set the icon
      uID = 0; //0-255 name of the icon png in the directory referenced in the db
      //set the durability
      durability = 100; //probably will be random later
      //set the rarity
      rarity = 0; //0-5
      //set the modifiers
      for (auto &modifier : modifiers) {
        modifier.Set_Empty();
      }
    }

    bool Empty() const {
      return !uID;
//      if (uID == 0)
//        return true;
//      return false;
    }

    void Set_Empty() {
      uID = 0; //0-255 name of the icon png in the directory referenced in the db
      rarity = 0; //0-5
      durability = 0; //0-100
      for (auto &modifier : modifiers) {
        modifier.Set_Empty();
      }
    }

    bool operator==(const Item &rhs) const {
      return uID == rhs.uID &&
             modifiers == rhs.modifiers &&
             rarity == rhs.rarity &&
             durability == rhs.durability;
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



















































































