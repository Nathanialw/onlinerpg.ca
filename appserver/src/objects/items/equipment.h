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
  std::string Use_Item(std::array<std::array<int, 48>, 4> &inventory, std::array<int, (int)Items::ItemSlot::SIZE>  &equipment, uint8_t invSlot);
  std::string Get_Equipment(std::array<int, (int)Items::ItemSlot::SIZE> &equipment);
  void Unequip_Item(std::array<std::array<int, 48>, 4> &inventory, std::array<int, (int)Items::ItemSlot::SIZE>  &equipment, const std::string &slot);
  void Equip_Offhand(std::array<std::array<int, 48>, 4> &inventory, std::array<int, (int)Items::ItemSlot::SIZE>  &equipment, uint8_t index);
};

#endif // BROWSERRPG_EQUIPMENT_H
