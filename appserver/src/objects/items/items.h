#pragma once
//
// Created by desktop on 10/12/24.
//

#ifndef BROWSERRPG_ITEMS_H
#define BROWSERRPG_ITEMS_H

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

}

#endif // BROWSERRPG_ITEMS_H
