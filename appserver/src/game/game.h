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
#include "loot.h"

#ifndef BROWSERRPG_GAME_H
#define BROWSERRPG_GAME_H

#endif // BROWSERRPG_GAME_H


namespace Game {



  //all of these need to be saved into a database
  struct Instance {
    //player id
    //saved into the db to link the player to the game data

    //session
    std::string session_id;
//    int duration = 0;

    //units
//    Units::Objects objects;
    std::array<std::unordered_map<Component::Position, Units::Objects>, 26> objects;
    std::array<std::unordered_map<Component::Position, std::unordered_map<Component::Position, Items::Ground>>, 26> items{};

    //current turn
//    int time = 0;
//    int turn = 0;
    //start day jan 1 2024
    //attack/move = 1 min
    //1 day = 1440 min
    //get tired
    //sleep = 8 hours = 480 turns
    //active time = 960 turns/day
    //get hungry = 1/day
    //rest = 5min, unless interrupted


    //map
    int level = 0;
    Component::Position location = {0, 0};
    std::array<std::unordered_map<Component::Position, Chunk::Map_Chunk>, 26> map;

    //seed
    Proc_Gen::Seed seed;


    Units::Unit &Get_Player() {
      if (objects[level][location].units.empty()) {
        std::cout << "Get_Player() no player found..." << std::endl;
      }
//      std::cout << "level: " << level << " " << "game object location: " << location.x << ", " << location.y <<std::endl;
          return objects[level][location].units[0];
    }

    Chunk::Map_Chunk &Get_Map(int currentLevel, Component::Position currentLocation) {
      return map[currentLevel][currentLocation];
    }

    //constructor
//      Instance() {
//        seed.seed = Proc_Gen::Create_Initial_Seed(Get_Player().name[0], Get_Player().name[3]);
//      }


  };

  Instance Init(const std::string& session_id);
  void Run();
}