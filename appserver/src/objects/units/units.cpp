//
// Created by nathanial on 3/29/24.
//
#include <cstdint>
#include "string"
#include "iostream"
#include "unordered_map"
#include <functional>

#include "utils.h"

#include "attack.h"
#include "collision.h"
#include "map.h"
#include "units.h"


namespace std {
  template <>
  struct hash<Units::UnitPosition> {
    std::size_t operator()(const Units::UnitPosition &pos) const {
      return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
    }
  };
}

namespace Units {
  const int mapWidth = 99;

//  std::unordered_map<uint16_t, std::string> entities;

  struct Placement {
    int x;
    int y;
  };

  std::vector<Unit> units;
  std::unordered_map<UnitPosition, int> unitPositions;
  static std::string unitsString;

  std::vector<Unit> *Get_Units() { return &units; }

  void Remove_Unit_At_Index(int i) {
    units.erase(units.begin() + i);
  };

  //key is position, the index of the unit in the units vector
  void Remove_Unit(int x, int y) {
    UnitPosition pos = {x, y};
    int index = unitPositions[pos];
    units.erase(units.begin() + index);
    unitPositions.erase(pos);
    Remove_Unit_At_Index(index);

    std::string xStr = Utils::Prepend_Zero(x);
    std::string yStr = Utils::Prepend_Zero(y);
    //remove from the send string
    for (int i = 1; i < unitsString.size(); i + 5) {
      std::cout << "checking for unit at: " << unitsString.substr(i,4) << std::endl;
      if (unitsString.substr(i+1,2) == xStr && unitsString.substr(i+3,2) == yStr) {
        std::cout << "removing unit from string at: " << unitsString.substr(i,4) << std::endl;
        unitsString.erase(i, 4);
        break;
      }
    }
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

  void Update_Unit_Position(int x, int y, int newX, int newY) {
    UnitPosition pos = {x, y};
    int index = unitPositions[pos];
    UnitPosition newPos = {newX, newY};
    unitPositions.erase(pos);
    unitPositions.emplace(newPos, index);
  }

  std::string unitChars[SIZE] = {"@",   "a",    "b",    "c",
                                 "d",   "e",    "f",    "g",
                                 "h",   "i",    "j",    "k",
                                 "l",   "m",    "n",    "o",
                                 "p",   "q",    "r",    "s",
                                 "t",   "u",    "v",    "w",
                                 "x",   "y",    "z"};

  std::string Get_Unit_Char(UnitType type) {
    return unitChars[type];
  }

  void Add_Unit(int x, int y, UnitType type) {
    Unit unit{};
    unit.x = x;
    unit.y = y;
    unit.type = type;
    units.push_back(unit);

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
      Add_Unit(x, y, GOBLIN);
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

  std::string Place_Entities_On_Map() {
    std::string mapEntities = "2";
    // loop through the map x times and lok for 2x2 squares
    // set entities to be in the center of the square
    // I need to send the char and the offset in the map g0317
    Add_Unit(6, 6, PLAYER);
    mapEntities += unitChars[PLAYER] + "0606";

    for (int i = 0; i < 5; ++i) {
      int numMonsters = rand() % 4;
      mapEntities += Random_Entities(unitChars[GOBLIN].c_str(), numMonsters);
    }
    return mapEntities;
  }


  void Update_UnitsString(int x, int y) {
    std::string xStr = Utils::Prepend_Zero(x);
    std::string yStr = Utils::Prepend_Zero(y);
    unitsString.replace(2, 4, xStr + yStr);
  }

  void Init() {
    unitsString = Place_Entities_On_Map();

    for (auto &unit : *Units::Get_Units()) {
      Map::Set_Tile(unit.x, unit.y, unitChars[unit.type]);
    }
  }

  std::string Send_Units() { return unitsString; }

}
