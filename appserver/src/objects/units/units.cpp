//
// Created by nathanial on 3/29/24.
//
#include <cstdint>
#include "string"
#include "unordered_map"


#include "units.h"
#include "warrior.h"

namespace Units {
  const int mapWidth = 99;
  static std::string map[mapWidth][mapWidth];

  std::string mapEntities;
  std::unordered_map<uint16_t , std::string> entities;

  struct Placement {
    int x;
    int y;
  };

  Placement Random_Placement() {
    Placement placement{};
    placement.x = rand() % mapWidth;
    placement.y = rand() % mapWidth;
    return placement;
  }

  bool Add_Object(std::string &group, int xStr, int yStr) {
    if (xStr > mapWidth - 1 || yStr > mapWidth - 1 || xStr < 1 || yStr < 1) {
      group.clear();
      return false;
    }
    else {
      std::string x;
      std::string y;
      if (xStr < 10)
        x = "0" + std::to_string(xStr);
      else
        x = std::to_string(xStr);
      if (yStr < 10)
        y = "0" + std::to_string(yStr);
      else
        y = std::to_string(yStr);
      group += x;
      group += y;
      return true;
    }
  }

  std::string Random_Entities(char entityType, int numEntities) {
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
    mapEntities = "2";
    //loop through the map x times and lok for 2x2 squares
    //set entities to be in the center of the square
    //I need to send the char and the offset in the map g0317
    mapEntities += "@0606";
//    mapEntities += Random_Entities('g', 3);
//    mapEntities += Random_Entities('g', 3);
//    mapEntities += Random_Entities('g', 3);
//    mapEntities += Random_Entities('g', 3);
//    mapEntities += Random_Entities('o', 1);
//    mapEntities += Random_Entities('o', 1);
//    mapEntities += Random_Entities('o', 1);
//    mapEntities += Random_Entities('o', 1);
//    mapEntities += Random_Entities('o', 1);
    return mapEntities;
  }


  //  static std::vector<std::string> unitsOnMap;
  static std::string unitsOnMap;

  void Init() {
    Unit player{};
    player.x = 6;
    player.y = 6;
    player.type = PLAYER;
    units.push_back(player);

    Unit enemy{};
    enemy.x = 5;
    enemy.y = 5;
    enemy.type = ENEMY;
    units.push_back(enemy);
    //unitsOnMap.push_back(Place_Entities_On_Map());
    unitsOnMap = Place_Entities_On_Map();
  }

std::string Send_Units() {
    return unitsOnMap;
}

  void Move(int x, int y) {
    for (auto & unit : units) {
      if (unit.type == PLAYER) {
        unit.x += x;
        unit.y += y;
      }
    }
  }

    void Die() {
      for (auto & unit : units) {
        if (unit.type == PLAYER) {
          units.erase(units.begin());
        }
      }
    }

  void Attack(int x, int y) {
    for (auto & unit : units) {
      if (unit.x == x && unit.y == y) {
        Die();
      }
    }
  }

  void Update(std::string &msg) {
    switch (msg[1]) {
        case 'w': Units::Move(0, 1); break;
        case 'a': Units::Move(0, -1); break;
        case 's': Units::Move(1, 0); break;
        case 'd': Units::Move(-1, 0); break;
    }

  }

}
