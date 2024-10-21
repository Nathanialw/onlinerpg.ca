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
  typedef std::array<std::array<int, 14>, (int)Items::BagType::SIZE> bags; //items

  std::string Update_Inventory(bags &inventory, const std::array<uint8_t, (int)Items::BagType::SIZE> &maxSlots);
  std::string Get_Inventory(bags &inventory);
  void Drop_Item(bags &inventory, std::array<uint8_t , 4> &groundItems, uint8_t index);
};

#endif // BROWSERRPG_INVENTORY_H
