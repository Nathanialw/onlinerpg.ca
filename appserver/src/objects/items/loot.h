#pragma once
//
// Created by desktop on 10/12/24.
//

#ifndef BROWSERRPG_LOOT_H
#define BROWSERRPG_LOOT_H

#endif // BROWSERRPG_LOOT_H
#include "array"
#include "string"
#include "items.h"

namespace Loot {

  void Generate_Loot(Items::Ground &items);
  std::string Query_Loot(Items::Ground &items);
  std::string Pick_Up_Item(Items::Ground &loot, Items::Inventory &inventory, const Items::Max_Slots &maxSlots, uint8_t index);
}