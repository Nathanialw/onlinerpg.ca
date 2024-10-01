#pragma once
//
// Created by desktop on 9/25/24.
//

#include "string"
#include "units.h"
#include "game.h"

#ifndef BROWSERRPG_SPAWN_H
#define BROWSERRPG_SPAWN_H

#endif // BROWSERRPG_SPAWN_H

namespace Spawn {
  struct Placement {
    int x;
    int y;
  };

//  std::string Get_Unit_Char(Units::Species species);
//  Placement Random_Placement();
//  void Add_Unit(int x, int y, const std::string &name, Units::

  void Init(Game::State &game, const std::basic_string<char> &characterCreate);
  std::string Get_Unit_Char(Units::Species species);
}