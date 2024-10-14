#pragma once
//
// Created by desktop on 10/12/24.
//

#ifndef BROWSERRPG_ITEMS_H
#define BROWSERRPG_ITEMS_H

namespace Items {
  enum class BagType {
    Items,
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
    bracers,
    gloves,
    belt,
    leggings,
    boots,
    ring,
    trinket,
    weaponMain,
    weaponOffhand,
    ranged,
    ammo,
    SIZE,
  };

}

#endif // BROWSERRPG_ITEMS_H
