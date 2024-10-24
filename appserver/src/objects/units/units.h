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
#include "inventory.h"

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

  static std::string species[(uint8_t)Species::SIZE] = {
      "alpaca",
      "basilisk",
      "centaur",
      "dwarf",
      "elf",
      "fox",
      "goblin",
      "human",
      "iguana",
      "jackal",
      "kobold",
      "lamia",
      "minotaur",
      "nymph",
      "orc",
      "pixie",
      "qat",
      "rat",
      "skeleton",
      "treant",
      "unicorn",
      "valkyrie",
      "warg",
      "xana",
      "yale",
      "zombie",
      "angel",
      "byakhee",
      "chimera",
      "dragon",
      "ebon",
      "fairy",
      "golem",
      "harpy",
      "imp",
      "jinn",
      "kraken",
      "lich",
      "madusa",
      "naga",
      "ogre",
      "poltergeist",
      "qaffir",
      "roc",
      "satyr",
      "troll",
      "urias",
      "vampire",
      "witch",
      "xanthus",
      "yeti",
      "ziburinis"
  };

  enum class Race {

  };

  enum class Gender {
    MALE,
    FEMALE,
    SIZE,
  };

  static std::string gender[(uint8_t)Gender::SIZE] = {
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
    uint8_t srength = 10; // damage melee and ranged
    uint8_t intelligence = 10; // magic
    uint8_t dexterity = 10; // dual wielding
    uint8_t constitution = 10; // health
    uint8_t authority = 10; // leadership
    uint8_t charisma = 10; // social interactions
  };

  struct Def {
    Species species = Species::GOBLIN;
    Gender gender = Gender::MALE;
    Class unitClass = Class::FIGHTER;
    Alignment alignment = Alignment::NEUTRAL;
  };



  struct Unit {
    Stats stats;

    uint16_t name{};
    uint16_t firstName{};
    uint16_t surname{};
    uint16_t titlePrefix{};
    uint16_t titleSuffix{};
    //unit data to send
    Component::Position position{};

    Component::Position location{};
    Items::Equipped equipment{};
    Items::Backpack pack{};
    std::array<uint8_t, 8> spells{};


    uint16_t health = 0;
    uint16_t healthMax = 0;
    uint16_t copper = 0;
    uint16_t silver = 0;
    uint16_t gold = 0;

    Def def;
    uint8_t unitID = 0;
    uint8_t age = 0;

    uint8_t vision = 0;
    uint8_t speed = 0;
    uint8_t maxSpeed = 0;
    uint8_t minDamage = 0;
    uint8_t maxDamage = 0;
    uint8_t AC = 0;
    //    bool dead = false;
    uint8_t level;



  //items are just an ID that is in the db
  //db contains the damage, AC, icon path, description, etc
//    Items::Bags bags{}; //items
//    Items::Max_Slots maxSlots{}; //items



    //constructor
    Unit(uint8_t iLevel, Component::Position sLocation) {
      level = iLevel;
      location = sLocation;

      //starting bags
      pack.maxSlots[0] = 4;
      pack.bags[0] = 37;

      pack.maxSlots[1] = 4;
      pack.bags[1] = 37;

      pack.maxSlots[2] = 2;
      pack.bags[2] = 75;

      pack.maxSlots[3] = 2;
      pack.bags[3] = 32;

      pack.maxSlots[4] = 4;
      pack.bags[4] = 104;

    }
};





//  struct Map_Position {
//    Component::Position chunk;
//    Component::Position position;
//  };

  struct Objects {
    std::vector<Unit> units;
    std::unordered_map<Component::Position, uint8_t> unitPositions;
//    std::unordered_map<Map_Position, int> unitPositionss;
    std::vector<uint8_t> emptyUnitSlots;
//    std::string unitsString;
  };

  int Get_Unit_Index(std::unordered_map<Component::Position, uint8_t> &unitPositions, Component::Position position);
  void Update_Unit_Position(std::unordered_map<Component::Position, uint8_t> &unitPositions, const Component::Position &position, const Component::Position &newPosition);
  void Remove_Unit(std::unordered_map<Component::Position, uint8_t> &unitPositions, std::vector<uint8_t> &emptyUnitSlots, Component::Position position);
//  Unit& Get_Unit_At_Position(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, int> &unitPositions, Component::Position &newPosition);
  Unit& Get_Unit_At_Position(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, uint8_t> &unitPositions, Component::Position &position);

  void Update_UnitsString(std::string &unitsString, int x, int y);

}

