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

//  std::string Get_Unit_Char(Units::Species species);
//  Placement Random_Placement();
//  void Add_Unit(int x, int y, const std::string &name, Units::

  void Add_Unit(Units::Objects &objects, int level, Component::Position location, Component::Position position, const uint16_t &name, Unit::Gender gender, Unit::Species species, Unit::Class unitClass, Unit::Alignment alignment, uint8_t picNum);
  char Get_Unit_Char(Unit::Species species);
  void Init(int level, Component::Position location, Chunk::Chunk chunk, std::vector<Chunk::Room> &rooms, Units::Objects &objects);
}