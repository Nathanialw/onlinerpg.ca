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
     void Add_Room(Chunk defaultChunk, Component::PosInt x, Component::PosInt y, Component::PosInt w, Component::PosInt h, bool columns = false) {
	     std::cout << "Adding room at: " << x << ", " << y << std::endl;
	     for (Component::PosInt k = 0; k < w; k++) {
		     for (Component::PosInt l = 0; l < h; l++) {
			     auto j = x + l;
			     auto i = y + k;
			     defaultChunk[i][j] = '.';
		     }
	     }
     }

     void Add_Small_Rooms(Chunk defaultChunk) {
	     Proc_Gen::Seed seed;
	     for (Component::PosInt x = 1; x < Component::mapWidth - 7; x += 7) {
		     for (Component::PosInt y = 1; y < Component::mapWidth - 7; y += 7) {
			     seed.seed = Proc_Gen::Create_Initial_Seed(x, y);
			     auto w = Proc_Gen::Random_Int(3, 6, seed);
			     seed.seed = Proc_Gen::Create_Initial_Seed(y, x);
			     auto h = Proc_Gen::Random_Int(3, 6, seed);
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

     void Add_Large_Rooms(Chunk defaultChunk, std::vector<Room> &rooms) {
	     Proc_Gen::Seed seed;
	     for (Component::PosInt x = 1; x < (Component::mapWidth - 20); x += 21) {
		     for (Component::PosInt y = 1; y < Component::mapWidth - 20; y += 21) {
			     seed.seed = Proc_Gen::Create_Initial_Seed(x, y);
			     Component::PosInt w = Proc_Gen::Random_Int(9, 19, seed);
			     seed.seed = Proc_Gen::Create_Initial_Seed(y, x);
			     Component::PosInt h = Proc_Gen::Random_Int(9, 19, seed);
			     Add_Room(defaultChunk, x, y, w, h);
			     rooms.push_back({x, y, w, h});
		     }
	     }
     }

     void Add_Rooms(Chunk defaultChunk, std::vector<Room> &rooms) {
	     std::cout << "Adding rooms" << std::endl;
	     Add_Small_Rooms(defaultChunk);
	     Add_Large_Rooms(defaultChunk, rooms);
     }


     void Create_Chunk(Map_Chunk &mapChunk, int8_t level, Component::Position location, std::vector<Room> &rooms, Proc_Gen::Seed &seed, Units::Objects &objects) {
	     // chunk position
	     // seed based on that position

	     std::string map = Map::Init(mapChunk.defaultChunk, mapChunk.chunk, rooms, seed);
	     Pathing::Init(mapChunk.pathing, map);
	     Spawn::Init(level, location, mapChunk.chunk, rooms, objects); // msg->get_payload()
     }


}