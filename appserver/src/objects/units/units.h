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
  ANGEL,
  BASILISK,
  CENTAUR,
  DWARF,
  ELF,
  FAIRY,
  GOBLIN,
  HUMAN,
  IMP,
  JINN,
  KOBOLD,
  LIZARD,
  MINOTAUR,
  NAGA,
  ORC,
  POLTERGEIST,
  QAFFIR,
  RAT,
  SNAKE,
  TROLL,
  UNICORN,
  VAMPIRE,
  WITCH,
  XENOMORPH,
  YETI,
  ZOMBIE,
  SIZE
};

struct Unit {
  int x = 6;
  int y = 6;
  UnitType type = GOBLIN;
  int srength = 10; // damage melee and ranged
  int intelligence = 10; // magic
  int dexterity = 10; // dual wielding
  int constitution = 10; // health
  int authority = 10; // leadership
  int charisma = 10; // social interactions

  int vision = 6;
  int movement = 1;
  int damage = 10;
  int AC = 10;
  int health = 100;
  int healthMax = 100;
};


  std::string Send_Units();
  void Init();
  void Update(const char* direction);
  Unit Get_Player();
  std::vector<Unit>* Get_Units();
}
