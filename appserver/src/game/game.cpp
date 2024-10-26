//
// Created by desktop on 9/30/24.
//
#include "game.h"
#include "db.h"

namespace Game {


//all of these need to be saved into a database

  Units::Unit &Instance::Get_Player() {
    if (levels[level].objects[location].units.empty()) {
      std::cout << "Get_Player() no player found..." << std::endl;
    }
    return levels[level].objects[location].units[0];
  }

  //defaults to at player position
  Units::Objects &Instance::Get_Objects() {
    auto position = levels[level].objects[location].units[0].position;
    return levels[position.level].objects[position.location];
  }

  Units::Objects &Instance::Get_Objects(Units::Position position) {
    return levels[position.level].objects[position.location];
  }

  Units::Objects &Instance::Get_Objects(uint8_t mapLevel, Component::Position location) {
    return levels[mapLevel].objects[location];
  }

  Items::Ground &Instance::Get_Items() {
    auto position = levels[level].objects[location].units[0].position;
    return levels[position.level].items[position.location][position.position];
  }

  Items::Ground &Instance::Get_Items(Units::Position position) {
    return levels[position.level].items[position.location][position.position];
  }

  Items::Ground &Instance::Get_Items(Component::Position location, Component::Position position) {
    return levels[level].items[location][position];
  }


  void Instance::Set_Player_New_Chunk(Units::Position position) {
    levels[level].objects[location].units[0] = levels[position.level].objects[position.location].units[0];
  }

  Chunk::Map_Chunk &Instance::Get_Map() {
    return levels[level].map[location];
  }

  Chunk::Map_Chunk &Instance::Get_Map(Component::Position maplocation) {
    return levels[level].map[maplocation];
  }

  bool Instance::Exists() {
    return !levels[level].objects[location].units.empty();
  }

  Chunk::Map_Chunk &Instance::Get_Map(uint8_t currentLevel, Component::Position currentLocation) {
    return levels[currentLevel].map[currentLocation];
  }

//  constructor
  Instance::Instance(const std::string& sessionID) {
//    seed.seed = Proc_Gen::Create_Initial_Seed(Get_Player().name[0], Get_Player().name[3]);
    DB::Init();
    session_id = sessionID;
  }


};
