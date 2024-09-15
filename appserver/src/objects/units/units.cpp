//
// Created by nathanial on 3/29/24.
//
#include <cstdint>
#include "string"
#include "iostream"
#include "unordered_map"

#include "../utils/utils.h"

#include "units.h"
#include "../collision/collision.h"
#include "../map/map.h"


namespace Units {
  const int mapWidth = 99;

  std::unordered_map<uint16_t, std::string> entities;

  struct Placement {
    int x;
    int y;
  };

  std::vector<Unit> units;
  std::vector<Unit> *Get_Units() { return &units; }

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

  bool Add_Object(std::string &group, int xStr, int yStr) {
    if (xStr > mapWidth - 1 || yStr > mapWidth - 1 || xStr < 1 || yStr < 1) {
      group.clear();
      return false;
    } else {
      group += Utils::Prepend_Zero(xStr);
      group += Utils::Prepend_Zero(yStr);
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
    std::string mapEntities = "2";
    // loop through the map x times and lok for 2x2 squares
    // set entities to be in the center of the square
    // I need to send the char and the offset in the map g0317
    mapEntities += unitChars[PLAYER] + "0606";
    mapEntities += unitChars[GOBLIN] + "0909";
    //    mapEntities += Random_Entities('g', 3);
    return mapEntities;
  }

  static std::string unitsOnMap;

  void Init() {
    Unit player{};
    player.x = 6;
    player.y = 6;
    player.vision = 6;
    player.type = PLAYER;
    units.push_back(player);
    std::cout << "Init() player added: " << units.size() << std::endl;

    Unit enemy{};
    enemy.x = 9;
    enemy.y = 9;
    enemy.type = GOBLIN;
    units.push_back(enemy);

    unitsOnMap = Place_Entities_On_Map();

    for (auto &unit : *Units::Get_Units()) {
      if (unit.type == Units::PLAYER) {
        Map::Set_Tile(unit.x, unit.y, unitChars[PLAYER]);
      } else if (unit.type == Units::GOBLIN) {
        Map::Set_Tile(unit.x, unit.y, unitChars[GOBLIN]);
      }
    }
  }

  std::string Send_Units() { return unitsOnMap; }

  void Move(int x, int y) {
    auto &player = units[0];
    player.x += x;
    player.y += y;
  }

  bool Attack(int px, int py, int x, int y) {
    std::cout << "checking for goblin" << std::endl;
    if (Map::Get_Adjacent_Tile(px+x, py+y) == "g") {
      return true;
    }
    return false;
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
    if (Attack(player.x, player.y, x, y)) {
      std::cout << "attack goblin" << std::endl;
      return;
    }
    // if the unit survives, return, else move to the cell
    Map::Update(player.x, player.y, x, y, unitChars[PLAYER]);
    std::cout << "moved from: " << player.x << ", " << player.y << " to: " << player.x+x << ", " << player.y+y << std::endl;
    Move(x, y);

    std::string position = Utils::Prepend_Zero(player.x) + Utils::Prepend_Zero(player.y);
    unitsOnMap.replace(2, 6, position);
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
