#pragma once

#include "string"
#include "game.h"

namespace Attack {
  struct Damage {
    std::string target = " ";
    uint8_t damageDone = 0;
    bool isDead = false;
  };

  Damage Melee(Units::Unit &attacker, Units::Objects &targets, char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], int8_t px, int8_t py, int8_t x, int8_t y);;
  Component::Position Check_Target_Location(const Units::Unit &unit, const Component::Position &moveTo);
  bool Check_For_Target(const Component::Position &position, const Component::Position &target);
}