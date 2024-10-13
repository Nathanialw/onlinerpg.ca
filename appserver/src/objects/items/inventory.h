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

  std::string Update_Inventory(std::array<std::array<int, 16>, 4> &inventory);
  std::string Get_Inventory(std::array<std::array<int, 16>, 4> &inventory);
};

#endif // BROWSERRPG_INVENTORY_H
