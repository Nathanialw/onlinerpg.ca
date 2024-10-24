//
// Created by desktop on 10/1/24.
//
#include "chunk.h"
#include "map.h"
#include "spawn.h"
//#include "procgen.h"

namespace Chunk {

  //3x3 rooms = quarters
  //9x9 rooms = barracks
  //9x15 rooms = halls
  void Add_Room(char defaultChunk[Component::mapWidth][Component::mapWidth], int x, int y, int w, int h, bool columns = false) {
    std::cout << "Adding room at: " << x << ", " << y << std::endl;
    for (int k = 0; k < w; k++) {
      for (int l = 0; l < h; l++) {
        int j = x + l;
        int i = y + k;
        defaultChunk[i][j] = '.';
      }
    }
  }

  void Add_Small_Rooms(char defaultChunk[Component::mapWidth][Component::mapWidth]) {
    Proc_Gen::Seed seed;
    for (int x = 1; x < Component::mapWidth - 7; x += 7) {
      for (int y = 1; y < Component::mapWidth - 7; y += 7) {
        seed.seed = Proc_Gen::Create_Initial_Seed(x, y);
        auto w = Proc_Gen::Random_Int(3, 6, seed);
        seed.seed = Proc_Gen::Create_Initial_Seed(y, x);
        int h = Proc_Gen::Random_Int(3, 6, seed);
        Add_Room(defaultChunk, x, y, w, h);
      }
    }
    //    Add_Room(2, 40, 9, 9);
    //    Add_Room(12, 40, 9, 16);
    //    Add_Room(30, 40, 5, 5);
  }

  //
  //  std::vector<Room> Get_Large_Rooms() {
  //    return largeRooms;
  //  }

  void Add_Large_Rooms(char defaultChunk[Component::mapWidth][Component::mapWidth], std::vector<Room> &rooms) {
    Proc_Gen::Seed seed;
    for (uint8_t x = 1; x < (Component::mapWidth - 20); x+=21) {
      for (uint8_t y = 1; y < Component::mapWidth - 20; y+=21) {
        seed.seed = Proc_Gen::Create_Initial_Seed(x, y);
        uint8_t w = Proc_Gen::Random_Int(9, 19, seed);
        seed.seed = Proc_Gen::Create_Initial_Seed(y, x);
        uint8_t h = Proc_Gen::Random_Int(9, 19, seed);
        Add_Room(defaultChunk, x, y, w, h);
        rooms.push_back({x, y, w, h});
      }
    }
  }

  void Add_Rooms(char defaultChunk[Component::mapWidth][Component::mapWidth], std::vector<Room> &rooms) {
    std::cout << "Adding rooms" << std::endl;
    Add_Small_Rooms(defaultChunk);
    Add_Large_Rooms(defaultChunk, rooms);
  }


  void Create_Chunk(int8_t level, Component::Position location, char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], std::vector<Room> &rooms, Component::sNode pathing[Component::mapWidth * Component::mapWidth], Proc_Gen::Seed &seed, Units::Objects &objects) {
    // chunk position
    // seed based on that position

    std::string map = Map::Init(defaultChunk, chunk, rooms, seed);
    Pathing::Init(pathing, map);
    Spawn::Init(level, location, chunk, rooms, objects); // msg->get_payload()
  }



}