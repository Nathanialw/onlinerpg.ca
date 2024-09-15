#pragma once
#include "string"
#include <vector>
//
// Created by nathanial on 3/29/24.
//

#ifndef BROWSERRPG_UNITS_H
#define BROWSERRPG_UNITS_H

#endif //BROWSERRPG_UNITS_H

#include "vector"

namespace Units {

enum UnitType {
  PLAYER,
  GOBLIN,
};

struct Unit {
  int x = 6;
  int y = 6;
  UnitType type = GOBLIN;
  int vision = 6;
};


  std::string Send_Units();
  void Init();
  void Update(const char* direction);
  Unit Get_Player();
  std::vector<Unit>* Get_Units();
}
