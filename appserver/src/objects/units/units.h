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
#include "iostream"

#include "components.h"

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
    SLAVE,
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
    std::string potrait = "001";

    //unit data to send
    Component::Position position = {6,6};
    std::string name = "Default";
    int age = 16;
    Def def;

    int vision = 6;
    int speed = 1;
    int maxSpeed = 1;
    int minDamage = 0;
    int maxDamage = 10;
    int AC = 10;
    int health = 30;
    int healthMax = 30;

//    int level = 0;
//    Component::Position location = {0, 0};
  };

//  struct Map_Position {
//    Component::Position chunk;
//    Component::Position position;
//  };

  struct Objects {
    std::vector<Unit> units;
    std::unordered_map<Component::Position, int> unitPositions;
//    std::unordered_map<Map_Position, int> unitPositionss;
    std::vector<int> emptyUnitSlots;
    std::string unitsString;
  };

  int Get_Unit_Index(std::unordered_map<Component::Position, int> &unitPositions, int x, int y);
  void Update_Unit_Position(std::unordered_map<Component::Position, int> &unitPositions, const int &x, const int &y, const int &newX, const int &newY);
  void Remove_Unit(std::unordered_map<Component::Position, int> &unitPositions, std::vector<int> &emptyUnitSlots, int x, int y);
  Unit& Get_Unit_At_Position(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, int> &unitPositions, int x, int y);
  void Update_UnitsString(std::string &unitsString, int x, int y);

}

