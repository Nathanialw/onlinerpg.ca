#pragma once

#include "string"
#include "game.h"

namespace Attack {
  struct Damage {
    std::string target = " ";
    int damageDone = 0;
    bool isDead = false;
  };

  Damage Melee(Game::State &game, int px, int py, int x, int y);

}