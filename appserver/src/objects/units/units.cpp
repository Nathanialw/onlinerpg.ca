//
// Created by nathanial on 3/29/24.
//
#include <cstdint>
#include "string"
#include "iostream"
#include "unordered_map"

#include "utils.h"

#include "attack.h"
#include "collision.h"
#include "map.h"
#include "units.h"

namespace Units {
  const int mapWidth = 99;

//  std::unordered_map<uint16_t, std::string> entities;

  struct Placement {
    int x;
    int y;
  };

  std::vector<Unit> units;
  //when adding new units, use the emptyUnitSlots vector to find the next empty slot before pushing back
  std::vector<int> emptyUnitSlots;
  std::unordered_map<UnitPosition, int> unitPositions;
  static std::string unitsString;

  std::vector<Unit> *Get_Units() { return &units; }

  void Remove_Unit(int x, int y) {
    Unit unit{};
    unit.def.species = Species::EMPTY;
    UnitPosition pos = {x, y};
    int index = unitPositions[pos];
//    emptyUnitSlots.push_back(index);
//    units[index] = unit;
    units.erase(units.begin() + index);
    unitPositions.erase(pos);

    //    std::string xStr = Utils::Prepend_Zero(x);
    //    std::string yStr = Utils::Prepend_Zero(y);
    //    //remove from the send string
    //    for (int i = 1; i < unitsString.size(); i + 5) {
    //      std::cout << "checking for unit at: " << unitsString.substr(i,4) << std::endl;
    //      if (unitsString.substr(i+1,2) == xStr && unitsString.substr(i+3,2) == yStr) {
    //        std::cout << "removing unit from string at: " << unitsString.substr(i,4) << std::endl;
    //        unitsString.erase(i, 4);
    //        break;
    //      }
    //    }
  }

  //is read only
  Unit Get_Player() {
    return units[0];
  }

  Placement Random_Placement() {
    Placement placement{};
    placement.x = rand() % mapWidth;
    placement.y = rand() % mapWidth;
    return placement;
  }

  int Get_Unit_Index(int x, int y) {
    UnitPosition pos = {x, y};
    return unitPositions[pos];
  }

  Unit Get_Unit_At_Position(int x, int y) {
    return units[Get_Unit_Index(x, y)];
  }

  void Update_Unit_Position(const int &x, const int &y, const int &newX, const int &newY) {
    UnitPosition pos = {x, y};
    int index = unitPositions[pos];
    UnitPosition newPos = {newX, newY};
    unitPositions.erase(pos);
    unitPositions.emplace(newPos, index);
  }

  std::string unitChars[(int)Species::SIZE] = {"a",    "b",    "c",
                                               "d",   "e",    "f",    "g",
                                               "h",   "i",    "j",    "k",
                                               "l",   "m",    "n",    "o",
                                               "p",   "q",    "r",    "s",
                                               "t",   "u",    "v",    "w",
                                               "x",   "y",    "z",    "A",
                                               "B",  "C",   "D",   "E",   "F",
                                               "G",   "H",   "I",   "J",   "K",
                                               "L",   "M",   "N",   "O",   "P",
                                               "Q",   "R",   "S",   "T",   "U",
                                               "V",   "W",   "X",   "Y",   "Z", " "};

  std::string Get_Unit_Char(Species species) {
    return unitChars[(int)species];
  }

  void Add_Unit(int x, int y, const std::string &name, Gender gender, Species species, Class unitClass, Alignment alignment) {
    Unit unit{};
    unit.name = name;
    unit.def.gender = gender;
    unit.def.species = species;
    unit.def.unitClass = unitClass;
    unit.def.alignment = alignment;
    unit.position.x = x;
    unit.position.y = y;

    if (emptyUnitSlots.empty()) {
      units.push_back(unit);
    } else {
      units[emptyUnitSlots.back()] = unit;
      emptyUnitSlots.pop_back();
    }

    UnitPosition pos = {x, y};
    unitPositions.emplace(pos, units.size() - 1);
  }

  bool Add_Object(std::string &group, int x, int y) {
    if (x > mapWidth - 1 || y > mapWidth - 1 || x < 1 || y < 1) {
      group.clear();
      return false;
    } else {
      group += Utils::Prepend_Zero(x);
      group += Utils::Prepend_Zero(y);
      Add_Unit(x, y, "Blargh", Gender::MALE, Species::GOBLIN, Class::FIGHTER, Alignment::EVIL);
      return true;
    }
  }

  std::string Random_Entities(const char* entityType, int numEntities) {
    std::string group;
  reRoll:
    Placement placement = Random_Placement();
    for (int i = 0; i < numEntities; ++i) {
      group += entityType;
      if (!Add_Object(group, placement.x + i, placement.y + i))
        goto reRoll;
    }
    return group;
  }


//  void Add_Unit(int x, int y, const std::string &name, Gender gender, Species species, Class unitClass, Alignment alignment) {

  std::string Place_Entities_On_Map(std::basic_string<char> characterCreate) {
    std::string mapEntities = "2";
    // loop through the map x times and lok for 2x2 squares
    // set entities to be in the center of the square
    // I need to send the char and the offset in the map g0317
    auto length = characterCreate.size();

    std::cout << "Crearacter create: " << characterCreate << std::endl;
    std::string name = characterCreate.substr(1, length - 5);
    std::cout << "Name: " << name << std::endl;
    std::string genderStr = characterCreate.substr(length - 4, 1);
    std::cout << "Gender: " << genderStr << std::endl;
    std::string speciesStr = characterCreate.substr(length - 3, 1);
    std::cout << "Species: " << speciesStr << std::endl;
    std::string classStr = characterCreate.substr(length - 2, 1);
    std::cout << "Class: " << classStr << std::endl;
    std::string alignmentStr = characterCreate.substr(length - 1, 1);
    std::cout << "Alignment: " << alignmentStr << std::endl;


    auto gender = (Gender)std::stoi(genderStr);
    auto species = (Species)std::stoi(speciesStr);
    auto unitClass = (Class)std::stoi(classStr);
    auto alignment = (Alignment)std::stoi(alignmentStr);

    Add_Unit(6, 6, name, gender, species, unitClass, alignment);

    mapEntities += unitChars[(int)unitClass] + "0606";

    for (int i = 0; i < 5; ++i) {
      int numMonsters = rand() % 4;
      mapEntities += Random_Entities(unitChars[(int)Species::GOBLIN].c_str(), numMonsters);
    }
    std::cout << "init num entities: " << units.size() << std::endl;
    return mapEntities;
  }


  void Update_UnitsString(int x, int y) {
    std::string xStr = Utils::Prepend_Zero(x);
    std::string yStr = Utils::Prepend_Zero(y);
    unitsString.replace(2, 4, xStr + yStr);
  }

  void Init(const std::basic_string<char> &characterCreate) {
    unitsString = Place_Entities_On_Map(characterCreate);

    for (auto &unit : *Units::Get_Units()) {
      Map::Set_Tile(unit.position.x, unit.position.y, unitChars[(int)unit.def.species]);
    }
  }

  std::string GetCharStats() {
    //only append with what is being updated
    //when the stat IS updated on then add it to the string

    //prepend with 0000 to tell which stats are being sent
    //name + gender + species + class + alignment

    auto player = Get_Player();

    auto health = Utils::Prepend_Zero_3Digit(player.health) + Utils::Prepend_Zero_3Digit(player.healthMax);
    auto speed = std::to_string(player.speed) + std::to_string(player.maxSpeed);
    auto damage = Utils::Prepend_Zero(player.minDamage) + Utils::Prepend_Zero(player.maxDamage);
    auto variableStats = player.potrait + Utils::Prepend_Zero(player.AC) + Utils::Prepend_Zero_3Digit(player.age) + health + speed + damage;

//    2 + 3 + 3 + 3 + 1 + 1 + 2 + 2

    std::string stats = "1111" + player.name + variableStats + std::to_string((int)player.def.gender) + std::to_string((int)player.def.species) + std::to_string((int)player.def.unitClass) + std::to_string((int)player.def.alignment);
    return "3" + stats;
  }
//  1 2 4 8 16
}
