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
#include "items.h"

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
    SKELETON,
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
    SATYR,
    TROLL,
    URIAS,
    VAMPIRE,
    WITCH,
    XANTHUS, //man-eating horse
    YETI,
    Ziburinis, //lithuanian glowing skeleton

//    EMPTY,

    SIZE
  };

  static std::string species[(int)Species::SIZE] = {
      "Alpaca",
      "Basilisk",
      "Centaur",
      "Dwarf",
      "Elf",
      "Fox",
      "Goblin",
      "Human",
      "Iguana",
      "Jackal",
      "Kobold",
      "Lamia",
      "Minotaur",
      "Nymph",
      "Orc",
      "Pixie",
      "Qat",
      "Rat",
      "Skeleton",
      "Treant",
      "Unicorn",
      "Valkyrie",
      "Warg",
      "Xana",
      "Yale",
      "Zombie",
      "Angel",
      "Byakhee",
      "Chimera",
      "Dragon",
      "Ebon",
      "Fairy",
      "Golem",
      "Harpy",
      "Imp",
      "Jinn",
      "Kraken",
      "Lich",
      "Madusa",
      "Naga",
      "Ogre",
      "Poltergeist",
      "Qaffir",
      "Roc",
      "Satyr",
      "Troll",
      "Urias",
      "Vampire",
      "Witch",
      "Xanthus",
      "Yeti",
      "Ziburinis"
  };

  enum class Race {

  };

  enum class Gender {
    MALE,
    FEMALE,
    SIZE,
  };

  static std::string gender[(int)Gender::SIZE] = {
      "male",
      "female"
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
    std::string portrait = "001";

    //unit data to send
    Component::Position position{};
    std::string name = "Default";
    std::string firstName;
    std::string surname;
    std::string titlePrefix;
    std::string titleSuffix;

    int age = 0;
    Def def;

    int vision = 0;
    int speed = 0;
    int maxSpeed = 0;
    int minDamage = 0;
    int maxDamage = 0;
    int AC = 0;
    int health = 0;
    int healthMax = 0;
//    bool dead = false;

    int level;
    Component::Position location{};

    std::array<int, (int)Items::ItemSlot::SIZE> equipment{};
    //items are just an ID that is in the db
      //db contains the damage, AC, icon path, description, etc
    std::array<std::array<int, 48>, (int)Items::BagType::SIZE> inventory{}; //items

    int copper = 0;
    int silver = 0;
    int gold = 0;

    std::array<int, 8> spells{};

    //constructor
    Unit(int iLevel, Component::Position sLocation) {
      level = iLevel;
      location = sLocation;
    }
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
  void Update_Unit_Position(std::unordered_map<Component::Position, int> &unitPositions, const Component::Position &pos, const Component::Position &newPos);
  void Remove_Unit(std::unordered_map<Component::Position, int> &unitPositions, std::vector<int> &emptyUnitSlots, int x, int y);
  Unit& Get_Unit_At_Position(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, int> &unitPositions, int x, int y);
  void Update_UnitsString(std::string &unitsString, int x, int y);

}

