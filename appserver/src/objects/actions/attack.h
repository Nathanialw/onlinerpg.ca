
#pragma once
#include "string"


namespace Attack {
  struct Damage {
    std::string target = "";
    int damageDone = 0;
    bool isDead = false;
  };

  Damage Melee(int px, int py, int x, int y);

}