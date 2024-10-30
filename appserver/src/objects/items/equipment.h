#pragma once
//
// Created by desktop on 10/13/24.
//

#ifndef BROWSERRPG_EQUIPMENT_H
#define BROWSERRPG_EQUIPMENT_H

#include "array"
#include "string"
#include "items.h"
#include "vector"

namespace Equipment {
     void Use_Item(Items::Backpack &pack, Items::Ground &groundItems, Items::Equipped &equipment, uint8_t invSlot, uint8_t bag, std::vector<std::pair<uint8_t, uint8_t>> &updateItems, int8_t &updateEquipment, int8_t &updateBag);

     std::string Get_Equipment(Items::Equipped &equipment);

     std::string Get_Equipment(Items::Equipped &equipment, int8_t &slot);

     void Unequip_Item(Items::Inventory &inventory, Items::Equipped &equipment, const std::string &slotNum, const Items::Max_Slots &maxSlots, std::vector<std::pair<uint8_t, uint8_t>> &updateItems, int8_t &updateEquipment);

     void Equip_Second_Item(Items::Backpack &pack, Items::Ground &groundItems, Items::Equipped &equipment, uint8_t index, uint8_t bag, std::vector<std::pair<uint8_t, uint8_t>> &updateItems, int8_t &updateEquipment, int8_t &updateBag);
};

#endif // BROWSERRPG_EQUIPMENT_H
