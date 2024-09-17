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

  enum class Species {
    alpaca,
    basilisk,
    centaur,
    dwarf,
    elf,
    fox,
    goblin,
    human,
    iguana,
    jackal,
    kobold,
    lamia,
    minotaur,
    nymph,
    orc,
    pixie,
    qat,
    rat,
    satyr,
    treant,
    unicorn,
    valkyrie,
    warg,
    xana,
    yale,
    zombie,
    ANGEL,
    BYAKHEE,
    CHIMERA,
    DRAGON,
    EBON,
    FAIRY,
    GOLEM,
    HARPY,
    IMP,
    JINN,
    KRAKEN,
    LICH,
    MADUSA,
    NAGA,
    OGRE,
    POLTERGEIST,
    QAFFIR,
    ROC,
    SIREN,
    TROLL,
    URIAS,
    VAMPIRE,
    WITCH,
    XANTHUS, //man-eating horse
    YETI,
    Ziburinis, //lithuanian glowing skeleton
    EMPTY,
    SIZE
  };

  enum class Gender {
    MALE,
    FEMALE,
    SIZE,
  };

  enum class Class {
    FIGHTER,
    MYSTIC,
    SIZE,
  };

  enum class Alignment {
    GOOD,
    NEUTRAL,
    EVIL,
    SIZE,
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
    std::string name = "Default";
    Species species = Species::goblin;
    Gender gender = Gender::MALE;
    Class unitClass = Class::FIGHTER;
    Alignment alignment = Alignment::NEUTRAL;

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
  void Init(std::basic_string<char> characterCreate);
  Unit Get_Player();
  std::vector<Unit>* Get_Units();
  int Get_Unit_Index(int x, int y);
  void Remove_Unit(int x, int y);
  std::string Get_Unit_Char(Species species);
  void Update_UnitsString(int x, int y);
}
