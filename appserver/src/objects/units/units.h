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
#include <functional>



namespace Units {

  enum class Species {
    ALPACA,
    BASILISK,
    CENTAUR,
    DWARF,
    ELF,
    FOX,
    GOBLIN,
    HUMAN,
    IGUANA,
    JACKAL,
    KOBOLD,
    LAMIA,
    MINOTAUR,
    NYMPH,
    ORC,
    PIXIE,
    QAT,
    RAT,
    SATYR,
    TREANT,
    UNICORN,
    VALKYRIE,
    WARG,
    XANA,
    YALE,
    ZOMBIE,
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

  enum class Race {

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

  struct Def {
    Species species = Species::GOBLIN;
    Gender gender = Gender::MALE;
    Class unitClass = Class::FIGHTER;
    Alignment alignment = Alignment::NEUTRAL;
  };

  struct Unit {
    Stats stats;

    //unit data to send
    int x = 6;
    int y = 6;
    std::string name = "Default";
    int age = 16;
    Def def;

    int vision = 6;
    int speed = 1;
    int minDamage = 0;
    int maxDamage = 10;
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
  Unit Get_Unit_At_Position(int x, int y);
  void Update_UnitsString(int x, int y);
  std::string GetCharStats();
}

namespace std {
  template <> struct hash<Units::UnitPosition> {
      std::size_t operator()(const Units::UnitPosition &pos) const {
        return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
      }
  };
}