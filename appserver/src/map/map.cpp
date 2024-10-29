//
// Created by nathanial on 3/29/24.
//
#include "string"

#include "game.h"
#include "map.h"
#include "labyrinth.h"
#include "procgen.h"
#include "chunk.h"

namespace Map {

     std::string Get_Map(Chunk::Chunk chunk) {
	     std::string map;
	     for (auto j = 0; j < Component::mapWidth; j++) {
		     for (auto i = 0; i < Component::mapWidth; i++) {
			     if (i < 0 || i > Component::mapWidth || j < 0 || j > Component::mapWidth)
				     map += ' ';
			     else
				     map += chunk[j][i];
		     }
	     }
	     return map;
     }

     void Remove_Perimeter(Chunk::Chunk chunk) {
	     std::string map;
	     for (int j = 0; j < Component::mapWidth; j++) {
		     for (int i = 0; i < Component::mapWidth; i++) {
			     if (i == 0 || i == Component::mapWidth - 1 || j == 0 || j == Component::mapWidth - 1)
				     chunk[j][i] = '.';
		     }
	     }
     }

     void Set_Game_Map(Chunk::Chunk defaultChunk, Chunk::Chunk chunk) {
	     std::cout << "Setting open map" << std::endl;
	     for (int x = 0; x < Component::mapWidth; x++) {
		     for (int y = 0; y < Component::mapWidth; y++) {
			     chunk[x][y] = defaultChunk[x][y];
		     }
	     }
     }

     void Create_Open_Map(Game::Instance &game) {
//    std::cout << "Creating open map" << std::endl;
//    for (int i = 0; i < Component::mapWidth; i++) {
//      for (int j = 0; j < Component::mapWidth; j++) {
//        if (i == 0 || i == Component::mapWidth - 1 || j == 0 || j == Component::mapWidth - 1) {
//          game.map[game.level][game.location].defaultChunk[i][j] = '^';
//          game.map[game.level][game.location].chunk[i][j] = game.map[game.level][game.location].defaultChunk[i][j];
//        } else {
//          game.map[game.level][game.location].defaultChunk[i][j] = '.';
//          game.map[game.level][game.location].chunk[i][j] = game.map[game.level][game.location].defaultChunk[i][j];
//        }
//      }
//    }
     }

     void Create_Labyrinth(Chunk::Chunk defaultChunk, Proc_Gen::Seed &seed) {
	     std::cout << "Creating labyrinth" << std::endl;
	     Labyrinth::Generate_Map(seed);
	     std::string labyrinthStr;
	     const int cellSize = 3;

	     for (int i = 0; i < Labyrinth::labyrinthWidth; i++) {
		     for (int j = 0; j < Labyrinth::labyrinthWidth; j++) {
			     labyrinthStr = Labyrinth::Get_Map_Cells()[Labyrinth::Get_Labyrinth()[j * Labyrinth::labyrinthWidth + i]];
			     int charIndex = 0;
			     if (i < 1 || j < 1)
				     std::cout << "labyrinthStr: " << labyrinthStr << std::endl;

			     for (int k = 0; k < cellSize; k++) {
				     for (int l = 0; l < cellSize; l++) {
					     int x = (i * cellSize) + k;
					     int y = (j * cellSize) + l;
					     defaultChunk[x][y] = labyrinthStr[charIndex];
					     charIndex++;
				     }
			     }
		     }
	     }
     }

     std::string Init(Chunk::Chunk defaultChunk, Chunk::Chunk chunk, std::vector<Chunk::Room> &rooms, Proc_Gen::Seed &seed) {
//    Create_Open_Map();
	     std::cout << "Creating map" << std::endl;
	     Create_Labyrinth(defaultChunk, seed);
	     std::cout << "labyrinth created" << std::endl;
	     Remove_Perimeter(defaultChunk);
	     std::cout << "perimeter removed" << std::endl;
	     Chunk::Add_Rooms(defaultChunk, rooms);
	     std::cout << "rooms added" << std::endl;
	     Set_Game_Map(defaultChunk, chunk);
	     std::cout << "map inited" << std::endl;
	     return Get_Map(chunk);
     }

     void Reset_Tile(Chunk::Chunk defaultChunk, Chunk::Chunk chunk, int x, int y) {
	     chunk[y][x] = defaultChunk[y][x];
     }

     void Set_Tile(Chunk::Chunk chunk, int x, int y, const char &tile) {
	     chunk[y][x] = tile;
     }

     //only needs to check the first item
     bool Check_For_Item(Items::Ground &items) {
	     if (!items[0].Empty())
		     return true;
	     return false;
     }

     //does not take into account traversing map chunks
     void Update(Game::Instance &game, int level, Component::Position location, Component::Position &position, Component::Position &move, const char &tile) {
	     //check item at location
	     if (Check_For_Item(game.Get_Items(location, position)))
		     game.Get_Map(location).chunk[position.y][position.x] = ',';
	     else
		     Reset_Tile(game.Get_Map(location).defaultChunk, game.Get_Map(location).chunk, position.x, position.y);
	     Set_Tile(game.Get_Map(location).chunk, position.x + move.x, position.y + move.y, tile);
     }

     void Update(Game::Instance &game, int level, Component::Position formerPosition, Component::Position newPosition, Component::Position formerLocation, Component::Position newLocation, const char &tile) {
	     if (Check_For_Item(game.Get_Items(formerLocation, formerPosition)))
		     game.Get_Map(formerLocation).chunk[formerPosition.y][formerPosition.x] = ',';
	     else
		     Reset_Tile(game.Get_Map(formerLocation).defaultChunk, game.Get_Map(formerLocation).chunk, formerPosition.x, formerPosition.y);
	     Set_Tile(game.Get_Map(newLocation).chunk, newPosition.x, newPosition.y, tile);
     }

     void Add_Map_Segment(Game::Instance &game, Component::Position cell, Component::Position offset, std::string &mapSegment) {
	     auto location = game.Get_Player().position.location;
	     mapSegment += game.Get_Map(location.Add(offset)).chunk[cell.y][cell.x];
     }

     void Handle_Boundary(Game::Instance &game, int8_t i, int8_t j, std::string &mapSegment) {
	     Component::Position chunk = {static_cast<int8_t>((i < 0) ? -1 : (i >= Component::mapWidth) ? 1 : 0), static_cast<int8_t>((j < 0) ? -1 : (j >= Component::mapWidth) ? 1 : 0)};
	     if (chunk.x == 0 && chunk.y == 0) {
		     mapSegment += game.Get_Map().chunk[j][i];
		     return;
	     }

	     Component::Position cell = {i, j};
	     if (chunk.x == -1) cell.x = Component::mapWidth + i;
	     else if (chunk.x == 1) cell.x = i - Component::mapWidth;

	     if (chunk.y == -1) cell.y = Component::mapWidth + j;
	     else if (chunk.y == 1) cell.y = j - Component::mapWidth;

	     Add_Map_Segment(game, cell, chunk, mapSegment);
     }

     void Print_Map(Game::Instance &game, const std::string &sentMap) {
	     auto vision = game.Get_Player().stats.vision;
	     for (int i = 0; i < vision * 2 + 1; i++) {
		     std::cout << sentMap.substr(i * (vision * 2 + 1), vision * 2 + 1) << std::endl;
	     }
     }

     // state 1 = initial map, 2 = update map
     std::string SendMapSegment(Game::Instance &game, const std::string &direction, int state) {
	     auto position = game.Get_Player().position.position;
	     auto vision = game.Get_Player().stats.vision;
	     std::string mapSegment = std::to_string(state);

	     mapSegment += std::to_string((vision * 2) + 1);
	     mapSegment += direction;
	     std::string mapString;

	     std::cout << position.As_String() << std::endl;
	     std::cout << "vision: " << (int) vision << std::endl;

	     for (auto j = position.y - vision; j <= position.y + vision; j++) {
		     for (auto i = position.x - vision; i <= position.x + vision; i++) {
			     Handle_Boundary(game, i, j, mapSegment);
		     }
	     }

	     std::cout << "mapSegment end: " << mapSegment << std::endl;

	     //print map
	     auto sentMap = mapSegment.substr(mapSegment.size() - (vision * 2 + 1) * (vision * 2 + 1));
	     Print_Map(game, sentMap);

	     std::cout << "map sent!" << std::endl;
	     return mapSegment;
     }

     std::string Get_Adjacent_Tile(Game::Instance &game, int level, Component::Position location, Component::Position newPosition) {
	     std::string tile;
	     if (newPosition.x < 0 || newPosition.x >= Component::mapWidth || newPosition.y < 0 || newPosition.y >= Component::mapWidth)
		     tile = " ";
	     else
		     tile = game.Get_Map(level, location).chunk[newPosition.y][newPosition.x];
	     return tile;
     }

     void Connect_Chunk_Pathing(Game::Instance &game, int8_t level, Component::Position location) {

	     //Connect Pathing
	     //check which adjacent chunks exist
	     //if they exist, add them to the pathing map

//    if (game.levels[level].map.count({location.x--, location.y}) > 0) {
//      std::cout << "connecting left chunk" << std::endl;
//      Pathing::Connect_Chunks(game.Get_Map(level, location).pathing, game.levels[level].map[{location.x--, location.y}].pathing, -1, 0);
//    }
	     Component::Position adjacentLocation(location.x + 1, location.y);
	     if (game.levels[level].map.count(adjacentLocation) > 0) {
		     std::cout << "connecting right chunk" << std::endl;
		     std::cout << "chunk: " << location.As_String() << std::endl;
		     std::cout << "toConnect: " << adjacentLocation.As_String() << std::endl;
		     Pathing::Connect_Chunks(game.Get_Map(level, location).pathing, game.Get_Map(level, adjacentLocation).pathing, 1, 0);
	     }
	     //        if (game.map[level].count({location.x, location.y--}) > 0) {
	     //          std::cout << "connecting top chunk" << std::endl;
	     //          Pathing::Connect_Chunks(game.map[level][location].pathing, game.map[level][{location.x, location.y--}].pathing, -1, 0);
	     //        }
	     //        if (game.map[level].count({location.x, location.y++}) > 0) {
	     //          std::cout << "connecting bottom chunk" << std::endl;
	     //          Pathing::Connect_Chunks(game.map[level][location].pathing, game.map[level][{location.x, location.y++}].pathing, 0, 1);
	     //        }

	     //Connect_Chunks(pathing, chunk);
     }

     void Add_Map_Chunk(Game::Instance &game, int8_t level, Component::Position location) {
	     std::cout << "Add map chunk" << std::endl;
	     std::cout << "location position to add: " << location.As_String() << std::endl;

	     std::cout << "Checking if location exists in map..." << std::endl;
	     if (game.levels[level].map.count(location) == 0) {
		     std::cout << "Not found adding chunk..." << std::endl;
		     // if player position is close to the edge of the chunk, create a new chunk add a new chunk
		     std::cout << "Creating chunk" << std::endl;
		     Proc_Gen::Seed seed;
		     seed.seed = Proc_Gen::Create_Initial_Seed(location.x, location.y);

		     Chunk::Create_Chunk(game.levels[level].map[location],
		                         level,
		                         location,
		                         game.Get_Map(level, location).rooms,
		                         seed, game.Get_Objects(level, location));
		     std::cout << "chunk created" << std::endl;

		     Connect_Chunk_Pathing(game, level, location);
	     } else {
		     std::cout << "chunk already exists" << std::endl;
	     }
     }

     void Check_Map_Chunk(Game::Instance &game) {
	     if (game.Get_Player().position.position.x < game.Get_Player().stats.vision && game.Get_Player().position.position.y < game.Get_Player().stats.vision) {
		     Component::Position location = game.Get_Player().position.location;
		     location.x--;
		     location.y--;
		     Add_Map_Chunk(game, game.Get_Player().position.level, location);
	     }
	     if (game.Get_Player().position.position.x >= Component::mapWidth - game.Get_Player().stats.vision && game.Get_Player().position.position.y >= Component::mapWidth - game.Get_Player().stats.vision) {
		     Component::Position location = game.Get_Player().position.location;
		     location.x++;
		     location.y++;
		     Add_Map_Chunk(game, game.Get_Player().position.level, location);
	     }
	     if (game.Get_Player().position.position.x < game.Get_Player().stats.vision && game.Get_Player().position.position.y >= Component::mapWidth - game.Get_Player().stats.vision) {
		     Component::Position location = game.Get_Player().position.location;
		     location.x--;
		     location.y++;
		     Add_Map_Chunk(game, game.Get_Player().position.level, location);
	     }
	     if (game.Get_Player().position.position.x >= Component::mapWidth - game.Get_Player().stats.vision && game.Get_Player().position.position.y < game.Get_Player().stats.vision) {
		     Component::Position location = game.Get_Player().position.location;
		     location.x++;
		     location.y--;
		     Add_Map_Chunk(game, game.Get_Player().position.level, location);
	     }
	     if (game.Get_Player().position.position.x < game.Get_Player().stats.vision) {
		     Component::Position location = game.Get_Player().position.location;
		     location.x--;
		     Add_Map_Chunk(game, game.Get_Player().position.level, location);
	     }
	     if (game.Get_Player().position.position.x >= Component::mapWidth - game.Get_Player().stats.vision) {
		     Component::Position location = game.Get_Player().position.location;
		     location.x++;
		     Add_Map_Chunk(game, game.Get_Player().position.level, location);
	     }
	     if (game.Get_Player().position.position.y < game.Get_Player().stats.vision) {
		     Component::Position location = game.Get_Player().position.location;
		     location.y--;
		     Add_Map_Chunk(game, game.Get_Player().position.level, location);
	     }
	     if (game.Get_Player().position.position.y >= Component::mapWidth - game.Get_Player().stats.vision) {
		     Component::Position location = game.Get_Player().position.location;
		     location.y++;
		     Add_Map_Chunk(game, game.Get_Player().position.level, location);
	     }

	     std::cout << "Number of chunks: " << game.levels[game.Get_Player().position.level].map.size() << std::endl;
	     for (auto &chunk: game.levels[game.Get_Player().position.level].map) {
		     std::cout << "Chunk: " << (int) chunk.first.x << ", " << (int) chunk.first.y << std::endl;
	     }
     }

}