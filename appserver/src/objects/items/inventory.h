#pragma once
//
// Created by desktop on 10/13/24.
//

#ifndef BROWSERRPG_INVENTORY_H
#define BROWSERRPG_INVENTORY_H
#include "items.h"
#include "string"
#include "array"

namespace Inventory {

  std::string Update_Inventory(const Items::Backpack &backpack, const Items::Max_Slots &maxSlots);
  std::string Get_Inventory(Items::Inventory &inventory);
  void Drop_Item(Items::Inventory &inventory, Items::Ground &groundItems, uint8_t bag, uint8_t index);
};

#endif // BROWSERRPG_INVENTORY_H






































