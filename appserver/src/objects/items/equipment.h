#pragma once
//
// Created by desktop on 10/13/24.
//

#ifndef BROWSERRPG_EQUIPMENT_H
#define BROWSERRPG_EQUIPMENT_H
#include "array"
#include "string"
#include "items.h"

namespace Equipment {
  void Equip_Item(std::array<std::array<int, 16>, 4> &inventory, std::array<int, (int)Items::ItemSlot::SIZE>  &equipment, uint8_t index);
  std::string Get_Equipment(std::array<int, (int)Items::ItemSlot::SIZE> &equipment);
};

#endif // BROWSERRPG_EQUIPMENT_H