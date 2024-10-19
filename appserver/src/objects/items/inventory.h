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

  std::string Update_Inventory(std::array<std::array<int, 48>, 4> &inventory);
  std::string Get_Inventory(std::array<std::array<int, 48>, 4> &inventory);
  void Drop_Item(std::array<std::array<int, 48>, 4> &inventory, std::array<uint8_t , 4> &groundItems, uint8_t index);
};

#endif // BROWSERRPG_INVENTORY_H
