#pragma once
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
    std::string unitsString;

    //map
//    static const int mapWidth = 99;
    std::string defaultMap[Component::mapWidth][Component::mapWidth];
    std::string gameMap[Component::mapWidth][Component::mapWidth];

    //pathing
    std::array<Pathing::sNode, Component::mapWidth * Component::mapWidth> nodes;

    //seed
    uint32_t seed;


    Units::Unit &Get_Player() {
      return units[0];
    }




  };

  State Init(const std::string& session_id);
  void Run();
}