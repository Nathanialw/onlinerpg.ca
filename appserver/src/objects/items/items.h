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
    Items,
    Items1,
    Potions,
    Scrolls,
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

  typedef std::array<uint8_t, (int)Items::BagType::SIZE> bagSlots;
  typedef std::array<std::array<int, 14>, (int)Items::BagType::SIZE> bags; //items

//  struct Bags {
//    bags bag{};
//    bagSlots maxSlots{};
//
//    Bags() {
//    }
//  };

  typedef std::array<uint8_t , 4> ground;
  typedef std::array<int, (int)Items::ItemSlot::SIZE> equipped;
}

#endif // BROWSERRPG_ITEMS_H
