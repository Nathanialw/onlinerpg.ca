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

  std::string Update_Inventory(Items::bags &inventory, const Items::bagSlots &maxSlots);
  std::string Get_Inventory(Items::bags &inventory);
  void Drop_Item(Items::bags &inventory, Items::ground &groundItems, uint8_t index);
};

#endif // BROWSERRPG_INVENTORY_H
