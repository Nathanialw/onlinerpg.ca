#pragma once
//
// Created by desktop on 10/12/24.
//

#ifndef BROWSERRPG_LOOT_H
#define BROWSERRPG_LOOT_H

#endif // BROWSERRPG_LOOT_H
#include "array"
#include "string"

namespace Loot {
  void Generate_Loot(std::array<uint8_t , 4> &items);
  std::string Query_Loot(std::array<uint8_t , 4> &items);
}