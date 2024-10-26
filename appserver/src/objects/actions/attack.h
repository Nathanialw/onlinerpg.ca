#pragma once

#include "string"
#include "game.h"

namespace Attack {
  struct Damage {
    std::string target = " ";
    int damageDone = 0;
    bool isDead = false;
  };

  Damage Melee(Units::Unit &attacker, Units::Objects &targets, Chunk::Chunk defaultChunk, Chunk::Chunk chunk, Component::Position &position, Component::Position &moveTo);
  Component::Position Check_Target_Location(const Units::Unit &unit, const Component::Position &moveTo);
  bool Check_For_Target(const Component::Position &position, const Component::Position &target, uint8_t visionRange);
}