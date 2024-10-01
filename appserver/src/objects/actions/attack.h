#pragma once

#include "string"
#include "game.h"

namespace Attack {
  struct Damage {
    std::string target = " ";
    int damageDone = 0;
    bool isDead = false;
  };

  Damage Melee(Units::Objects &objects, char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], int px, int py, int x, int y);

}