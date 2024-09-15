//
// Created by nathanial on 3/29/24.
//
#include <cstdint>
#include "string"
#include "iostream"
#include "unordered_map"
#include <functional>

#include "../utils/utils.h"

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

  std::unordered_map<uint16_t, std::string> entities;

  struct Placement {
    int x;
    int y;
  };

  std::vector<Unit> units;
  std::vector<Unit> *Get_Units() { return &units; }

  //key is position, the index of the unit in the units vector



  std::unordered_map<UnitPosition, int> unitPositions;

  std::string unitChars[SIZE] = {"@",   "a",    "b",    "c",
                                 "d",   "e",    "f",    "g",
                                 "h",   "i",    "j",    "k",
                                 "l",   "m",    "n",    "o",
                                 "p",   "q",    "r",    "s",
                                 "t",   "u",    "v",    "w",
                                 "x",   "y",    "z"};

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

void Add_Unit(int x, int y, UnitType type) {
  Unit unit{};
  unit.x = x;
  unit.y = y;
  unit.type = type;
  units.push_back(unit);
  std::cout << "attempting to add unit to hashmap" << std::endl;
  UnitPosition pos = {x, y};
  unitPositions.emplace(pos, units.size() - 1);
//  unitPositions[pos] = units.size() - 1;
  std::cout << "unit added at index: " << unitPositions[pos] << std::endl;
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

  static std::string unitsOnMap;

  void Init() {
    unitsOnMap = Place_Entities_On_Map();

    for (auto &unit : *Units::Get_Units()) {
      Map::Set_Tile(unit.x, unit.y, unitChars[unit.type]);
    }
  }

  std::string Send_Units() { return unitsOnMap; }

  void Move(int x, int y) {
    auto &player = units[0];
    player.x += x;
    player.y += y;
  }

  void Update_Player(const char *direction) {
    int x, y;
    switch (*direction) {
    case 'w':
      x = 0, y = -1;
      break;
    case 'a':
      x = -1, y = 0;
      break;
    case 's':
      x = 0, y = 1;
      break;
    case 'd':
      x = 1, y = 0;
      break;
    }
    auto &player = units[0];
    // collision
    if (Collision::Wall_Collision(player.x, player.y, x, y)) {
      std::cout << "wall collision" << std::endl;
      return;
    }
    // if the nearby cell is an enemy, attack
    if (Attack::Melee(player.x, player.y, x, y)) {
      std::cout << "attack goblin" << std::endl;
      return;
    }
    // if the unit survives, return, else move to the cell
    Map::Update(player.x, player.y, x, y, unitChars[PLAYER]);
    Move(x, y);

    std::string position = Utils::Prepend_Zero(player.x) + Utils::Prepend_Zero(player.y);
    unitsOnMap.replace(2, 4, position);
  }


  void Update_Units() {
    // move enitities
    //        for (auto & unit : *Get_Units()) {
    //          if (unit.type == ENEMY) {
    //                std::string x = std::to_string(unit.x);
    //                std::string y = std::to_string(unit.y);
    //                if (unit.x < 10)
    //                  x = "0" + x;
    //                if (unit.y < 10)
    //                  y = "0" + y;
    //
    //                unitPositions["x+y"];
    //
    //
    //            std::string position = "2@" + x + y;
    //            unitsOnMap.replace(0, 6, position);
    //
    //          }
    //        }
  }

  void Update(const char *direction) {
    Update_Player(direction);
  }
}
