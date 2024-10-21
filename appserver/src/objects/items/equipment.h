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
  std::string Use_Item(Items::bags &inventory, Items::equipped &equipment, uint8_t invSlot);
  std::string Get_Equipment(Items::equipped &equipment);
  void Unequip_Item(Items::bags &inventory, Items::equipped &equipment, const std::string &slot);
  void Equip_Second_Item(Items::bags &inventory, Items::equipped &equipment, uint8_t index);
};

#endif // BROWSERRPG_EQUIPMENT_H
