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

  void Add_Unit(Units::Objects &objects, int x, int y, const std::string &name, Units::Gender gender, Units::Species species, Units::Class unitClass, Units::Alignment alignment);
  char Get_Unit_Char(Units::Species species);
  void Init(char chunk[Component::mapWidth][Component::mapWidth], std::vector<Chunk::Room> &rooms, Units::Objects &objects);
}