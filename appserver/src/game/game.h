//
// Created by desktop on 9/30/24.
//

#include "string"
#include "vector"
#include "unordered_map"
#include "components.h"
#include "units.h"
#include "pathing.h"

#ifndef BROWSERRPG_GAME_H
#define BROWSERRPG_GAME_H

#endif // BROWSERRPG_GAME_H


namespace Game {

  //all of these need to be saved into a database
  struct State {
    //player id
    //saved into the db to link the player to the game data

    //session
    std::string session_id;

    //units
    std::vector<Units::Unit> units;
    std::vector<int> emptyUnitSlots;
    std::unordered_map<Component::Position, int> unitPositions;
//    static std::string unitsString;

    //map
    static const int mapWidth = 99;
    std::string defaultMap[mapWidth][mapWidth];
    std::string gameMap[mapWidth][mapWidth];

    //pathing
    std::array<Pathing::sNode, mapWidth * mapWidth> nodes;

    //seed
    uint32_t seed;
  };

  State Init(const std::string& session_id);
  void Run();
}