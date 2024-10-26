//
// Created by desktop on 9/30/24.
//
#include "game.h"
#include "db.h"

namespace Game {


//all of these need to be saved into a database

  Units::Unit &Instance::Get_Player() {
    if (objects[level][location].units.empty()) {
      std::cout << "Get_Player() no player found..." << std::endl;
    }
    return objects[level][location].units[0];
  }

  //defaults to at player position
  Units::Objects &Instance::Get_Objects() {
    auto position = objects[level][location].units[0].position;
    return objects[position.level][position.location];
  }

  Units::Objects &Instance::Get_Objects(Units::Position position) {
    return objects[position.level][position.location];
  }

  Items::Ground &Instance::Get_Items_At_player_Position() {
    auto position = objects[level][location].units[0].position;
    return items[position.level][position.location][position.position];
  }

  void Instance::Set_Player_New_Chunk(Units::Position position) {
    objects[level][location].units[0] = objects[position.level][position.location].units[0];
  }

  bool Instance::Exists() {
    return !objects[level][location].units.empty();
  }

  Chunk::Map_Chunk &Instance::Get_Map(uint8_t currentLevel, Component::Position currentLocation) {
    return map[currentLevel][currentLocation];
  }

//  constructor
  Instance::Instance(const std::string& sessionID) {
//    seed.seed = Proc_Gen::Create_Initial_Seed(Get_Player().name[0], Get_Player().name[3]);
    DB::Init();
    session_id = sessionID;
  }


};
