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
    EMPTY,
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
    LEVIATHAN,
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



  struct Stats {
    int srength = 10; // damage melee and ranged
    int intelligence = 10; // magic
    int dexterity = 10; // dual wielding
    int constitution = 10; // health
    int authority = 10; // leadership
    int charisma = 10; // social interactions
  };

  struct Unit {
    Stats stats;

    //unit data to send
    int x = 6;
    int y = 6;
    UnitType type = GOBLIN;

    int vision = 6;
    int speed = 1;
    int damage = 10;
    int AC = 10;
    int health = 30;
    int healthMax = 30;
  };

  struct UnitPosition {
    int x;
    int y;

    bool operator==(const UnitPosition &other) const {
      return x == other.x && y == other.y;
    }
  };


  std::string Send_Units();
  void Init();
  Unit Get_Player();
  std::vector<Unit>* Get_Units();
  int Get_Unit_Index(int x, int y);
  void Remove_Unit(int x, int y);
  std::string Get_Unit_Char(UnitType type);
  void Update_UnitsString(int x, int y);
}
