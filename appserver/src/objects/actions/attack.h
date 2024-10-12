#pragma once

#include "string"
#include "game.h"

namespace Attack {
  struct Damage {
    std::string target = " ";
    int damageDone = 0;
    bool isDead = false;
  };

  Damage Melee(Units::Unit &attacker, Units::Objects &targets, char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], int px, int py, int x, int y);;
  Component::Position Check_Target_Location(const Units::Unit &unit, const Component::Position &moveTo);
  bool Check_For_Target(const Component::Position &position, const Component::Position &target);
}