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
  void Use_Item(Items::Backpack &pack, Items::Ground &groundItems, Items::Equipped &equipment, uint8_t invSlot, uint8_t bag);
  std::string Get_Equipment(Items::Equipped &equipment);
  void Unequip_Item(Items::Inventory &inventory, Items::Equipped &equipment, const std::string &slotNum, const Items::Max_Slots &maxSlots);
  void Equip_Second_Item(Items::Backpack &pack, Items::Ground &groundItems, Items::Equipped &equipment, uint8_t index, uint8_t bag);
};

#endif // BROWSERRPG_EQUIPMENT_H
