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
    ENEMY
  };

  struct Unit {
    int x;
    int y;
    UnitType type;
  };

  static std::vector<Unit> units;


  std::string Send_Units();
  void Init();
  void Update(std::string &msg);

}
