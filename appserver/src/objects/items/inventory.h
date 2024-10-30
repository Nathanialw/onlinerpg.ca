#pragma once
//
// Created by desktop on 10/13/24.
//

#ifndef BROWSERRPG_INVENTORY_H
#define BROWSERRPG_INVENTORY_H

#include "items.h"
#include "string"
#include "array"
#include "vector"

namespace Inventory {

     std::string Get_Inventory(const Items::Backpack &backpack, const Items::Max_Slots &maxSlots);

     std::string Get_Inventory(const Items::Backpack &backpack, std::vector<std::pair<uint8_t, uint8_t>> updateItems);

     void Drop_Item(Items::Inventory &inventory, Items::Ground &groundItems, uint8_t bag, uint8_t index);
};

#endif // BROWSERRPG_INVENTORY_H






































