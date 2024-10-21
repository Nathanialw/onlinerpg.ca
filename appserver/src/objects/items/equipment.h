#pragma once
//
// Created by desktop on 10/13/24.
//

#ifndef BROWSERRPG_EQUIPMENT_H
#define BROWSERRPG_EQUIPMENT_H
#include "array"
#include "string"
#include "items.h"
#include "inventory.h"

namespace Equipment {
  std::string Use_Item(Inventory::bags &inventory, std::array<int, (int)Items::ItemSlot::SIZE>  &equipment, uint8_t invSlot);
  std::string Get_Equipment(std::array<int, (int)Items::ItemSlot::SIZE> &equipment);
  void Unequip_Item(Inventory::bags &inventory, std::array<int, (int)Items::ItemSlot::SIZE>  &equipment, const std::string &slot);
  void Equip_Second_Item(Inventory::bags &inventory, std::array<int, (int)Items::ItemSlot::SIZE>  &equipment, uint8_t index);
};

#endif // BROWSERRPG_EQUIPMENT_H
