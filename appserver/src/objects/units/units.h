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
    std::string potrait = "001";

    //unit data to send
    Component::Position position{};
    std::string name = "Default";
    uint8_t age = 0;
    Def def;

    int vision = 0;
    uint8_t speed = 0;
    uint8_t maxSpeed = 0;
    uint8_t minDamage = 0;
    uint8_t maxDamage = 0;
    uint8_t AC = 0;
    uint8_t health = 0;
    uint8_t healthMax = 0;
//    bool dead = false;

    uint8_t level;
    Component::Position location{};

    std::array<uint8_t, 15> equipment{};
    //items are just an ID that is in the db
      //db contains the damage, AC, icon path, description, etc
    std::array<uint8_t, 16> bag{};      //items
    std::array<uint8_t, 16> belt{};     //potions
    std::array<uint8_t, 16> tome{};     //scrolls
    std::array<uint8_t, 16> keyring{};  //keys

    uint8_t copper = 0;
    uint8_t silver = 0;
    uint8_t gold = 0;

    std::array<uint8_t, 8> spells{};

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
    std::unordered_map<Component::Position, uint8_t> unitPositions;
//    std::unordered_map<Map_Position, int> unitPositionss;
    std::vector<uint8_t> emptyUnitSlots;
    std::string unitsString;
  };

  int8_t Get_Unit_Index(std::unordered_map<Component::Position, uint8_t> &unitPositions, int8_t x, int8_t y);
  void Update_Unit_Position(std::unordered_map<Component::Position, uint8_t> &unitPositions, const int8_t &x, const int8_t &y, const int8_t &newX, const int8_t &newY);
  void Update_Unit_Position(std::unordered_map<Component::Position, uint8_t> &unitPositions, const Component::Position &pos, const Component::Position &newPos);
  void Remove_Unit(std::unordered_map<Component::Position, uint8_t> &unitPositions, std::vector<uint8_t> &emptyUnitSlots, int8_t x, int8_t y);
  Unit& Get_Unit_At_Position(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, uint8_t> &unitPositions, int8_t x, int8_t y);
  void Update_UnitsString(std::string &unitsString, int8_t x, int8_t y);

}

