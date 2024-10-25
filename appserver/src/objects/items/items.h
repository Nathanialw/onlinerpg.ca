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



  typedef std::array<Items::ItemID, (uint8_t)Items::BagType::SIZE> Bags;
  typedef std::array<uint8_t, (uint8_t)Items::BagType::SIZE> Max_Slots;
  typedef std::array<std::array<Items::ItemID, 14>, (uint8_t)Items::BagType::SIZE> Inventory;

  struct Item {
    Items::ItemID uID;

    //it needs to know which modifiers it has
    std::array<uint8_t, 5> modifiers; //keys to the static modifiers in the db

    //which icon it has
    uint8_t icon; //name of the icon png in the directory referenced in the db

    uint8_t rarity; //0-5
    uint8_t durability; //0-100


    //requirements
  };

  struct Backpack {
      Inventory inventory;
      Bags bags;
      Max_Slots maxSlots;
  };


  typedef std::array<Items::ItemID , 14> Ground;
  typedef std::array<Items::ItemID, (uint8_t)Items::ItemSlot::SIZE> Equipped;
}

#endif // BROWSERRPG_ITEMS_H



















































































