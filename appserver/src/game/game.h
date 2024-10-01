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
#include "procgen.h"
#include "chunk.h"

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
    std::unordered_map<Component::Position, int> unitPositions;
    std::vector<int> emptyUnitSlots;
    std::string unitsString;

    //map
    Component::Position location = {0, 0};
    int level = 0;
    std::array<std::unordered_map<Component::Position, Chunk::Map_Chunk>, 26> map;

    //seed
    Proc_Gen::Seed seed;


    Units::Unit &Get_Player() {
      return units[0];
    }

    //constructor
//      State() {
//        seed.seed = Proc_Gen::Create_Initial_Seed(Get_Player().name[0], Get_Player().name[3]);
//      }


  };

  State Init(const std::string& session_id);
  void Run();
}