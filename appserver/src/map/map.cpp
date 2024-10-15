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

  std::string Get_Map(char chunk[Component::mapWidth][Component::mapWidth]) {
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

  void Remove_Perimeter(char chunk[Component::mapWidth][Component::mapWidth]) {
    std::string map;
    for (int j = 0; j < Component::mapWidth; j++) {
      for (int i = 0; i < Component::mapWidth; i++) {
        if (i == 0 || i == Component::mapWidth - 1 || j == 0 || j == Component::mapWidth - 1)
          chunk[j][i] = '.';
      }
    }
  }

  void Set_Game_Map(char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth]) {
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
//          game.map[game.level][game.location].defaultChunk[i][j] = '#';
//          game.map[game.level][game.location].chunk[i][j] = game.map[game.level][game.location].defaultChunk[i][j];
//        } else {
//          game.map[game.level][game.location].defaultChunk[i][j] = '.';
//          game.map[game.level][game.location].chunk[i][j] = game.map[game.level][game.location].defaultChunk[i][j];
//        }
//      }
//    }
  }

  void Create_Labyrinth(char defaultChunk[Component::mapWidth][Component::mapWidth], Proc_Gen::Seed &seed) {
    std::cout << "Creating labyrinth" << std::endl;
    Labyrinth::Generate_Map(seed);
    std::string labyrinthStr;
    const int cellSize = 3;

    for (int i = 0; i < Labyrinth::labyrinthWidth; i++) {
      for (int j = 0; j < Labyrinth::labyrinthWidth; j++) {
        labyrinthStr = Labyrinth::Get_Map_Cells() [Labyrinth::Get_Labyrinth()[j * Labyrinth::labyrinthWidth + i]];
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

  std::string Init(char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], std::vector<Chunk::Room> &rooms, Proc_Gen::Seed &seed) {
//    Create_Open_Map();
    Create_Labyrinth(defaultChunk, seed);
    Remove_Perimeter(defaultChunk);
    Chunk::Add_Rooms(defaultChunk, rooms);
    Set_Game_Map(defaultChunk, chunk);
    std::cout << "map inited" << std::endl;
    return Get_Map(chunk);
  }

  void Set_Tile(char chunk[Component::mapWidth][Component::mapWidth], int x, int y, const char &tile) {
    chunk[y][x] = tile;
  }

  void Reset_Tile(char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], int x, int y) {
    chunk[y][x] = defaultChunk[y][x];
  }

  void Update(Game::Instance &game, int level, Component::Position location, int px, int py, int x, int y, const char &tile) {
    Reset_Tile(game.map[level][location].defaultChunk, game.map[level][location].chunk, px, py);
    Set_Tile(game.map[level][location].chunk, px + x, py + y, tile);
  }

  void Update(Game::Instance &game, int level, Component::Position formerPosition, Component::Position newPosition, Component::Position formerLocation, Component::Position newLocation, const char &tile) {
    Reset_Tile(game.map[level][formerLocation].defaultChunk, game.map[level][formerLocation].chunk, formerPosition.x, formerPosition.y);
    Set_Tile(game.map[level][newLocation].chunk, newPosition.x, newPosition.y, tile);
  }

  void Add_Map_Segment(Game::Instance &game, int i, int j, Component::Position offset, std::string &mapSegment) {
    auto location = game.Get_Player().location;
    location.x += offset.x;
    location.y += offset.y;
    mapSegment += game.map[game.Get_Player().level][location].chunk[j][i];
  }


  void Handle_Boundary(Game::Instance &game, int i, int j, std::string &mapSegment) {
    std::string key = std::to_string((i < 0) ? -1 : (i >= Component::mapWidth) ? 1 : 0) + "," + std::to_string((j < 0) ? -1 : (j >= Component::mapWidth) ? 1 : 0);
    Component::Position chunk = {(i < 0) ? -1 : (i >= Component::mapWidth) ? 1 : 0,  (j < 0) ? -1 : (j >= Component::mapWidth) ? 1 : 0};
    Component::Position direction[] = { {0, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}, {1, -1}, {-1, -1}, {1, 1}, {-1, 1} };

    std::cout << chunk.x << ", " << chunk.y << std::endl;

    if      (chunk == direction[0]) mapSegment += game.map[game.Get_Player().level][game.Get_Player().location].chunk[j][i];
    else if (chunk == direction[5]) Add_Map_Segment(game, i - Component::mapWidth, Component::mapWidth + j, chunk, mapSegment);
    else if (chunk == direction[6]) Add_Map_Segment(game, Component::mapWidth + i, j - Component::mapWidth, chunk, mapSegment);
    else if (chunk == direction[7]) Add_Map_Segment(game, i - Component::mapWidth, j - Component::mapWidth, chunk, mapSegment);
    else if (chunk == direction[8]) Add_Map_Segment(game, Component::mapWidth + i, Component::mapWidth + j, chunk, mapSegment);
    else if (chunk == direction[1]) Add_Map_Segment(game, i, Component::mapWidth + j, chunk, mapSegment);
    else if (chunk == direction[2]) Add_Map_Segment(game, i - Component::mapWidth, j, chunk, mapSegment);
    else if (chunk == direction[3]) Add_Map_Segment(game, i, j - Component::mapWidth, chunk, mapSegment);
    else if (chunk == direction[4]) Add_Map_Segment(game, Component::mapWidth + i, j, chunk, mapSegment);
  }

  void Print_Map(Game::Instance &game, const std::string &sentMap) {
    for (int i = 0; i < game.Get_Player().vision * 2 + 1; i++) {
      std::cout << sentMap.substr(i * (game.Get_Player().vision * 2 + 1), game.Get_Player().vision * 2 + 1) << std::endl;
    }
  }

  // state 1 = initial map, 2 = update map
  std::string SendMapSegment(Game::Instance &game, const std::string& direction, int state) {
    std::string mapSegment = std::to_string(state);

    mapSegment += std::to_string((game.Get_Player().vision * 2) + 1);
    mapSegment += direction;
    std::string mapString;

    std::cout << "x: " << game.Get_Player().position.x << " y: " << game.Get_Player().position.y << std::endl;
    std::cout << "vision: " << game.Get_Player().vision << std::endl;

    for (int j = game.Get_Player().position.y - game.Get_Player().vision; j <= game.Get_Player().position.y + game.Get_Player().vision; j++) {
        for (int i = game.Get_Player().position.x - game.Get_Player().vision; i <= game.Get_Player().position.x + game.Get_Player().vision; i++) {
          Handle_Boundary(game, i, j, mapSegment);
      }
    }

    std::cout << "mapSegment end: " << mapSegment << std::endl;

    //print map
    auto sentMap = mapSegment.substr(mapSegment.size() - (game.Get_Player().vision * 2 + 1) * (game.Get_Player().vision * 2 + 1));
    Print_Map(game, sentMap);
    //append items
//    std::string items;
//    for (int j = game.Get_Player().position.y - game.Get_Player().vision; j <= game.Get_Player().position.y + game.Get_Player().vision; j++) {
//      for (int i = game.Get_Player().position.x - game.Get_Player().vision; i <= game.Get_Player().position.x + game.Get_Player().vision; i++) {
//          Handle_Boundary(game, i, j, items);
//      }
//    }

//    game.items[game.Get_Player().level][game.Get_Player().location][game.Get_Player().position];

    std::cout << "map sent!" << std::endl;
    return mapSegment;
  }

  std::string Get_Adjacent_Tile(Game::Instance &game, int level, Component::Position location, int x, int y) {
    std::string tile;
    if (x < 0 || x >= Component::mapWidth || y < 0 || y >= Component::mapWidth)
        tile = " ";
    else
        tile = game.map[level][location].chunk[y][x];
    return tile;
  }

  void Add_Map_Chunk(Game::Instance &game, int level, Component::Position location) {
    std::cout << "Add map chunk" << std::endl;
    std::cout << "location position to add: " << location.x << ", " << location.y << std::endl;

    std::cout << "Checking if location exists in map..." << std::endl;
    if (game.map[level].count(location) == 0) {
      std::cout << "Not found adding chunk..." << std::endl;
      // if player position is close to the edge of the chunk, create a new chunk add a new chunk
      std::cout << "Creating chunk" << std::endl;
      Proc_Gen::Seed seed;
      seed.seed = Proc_Gen::Create_Initial_Seed(location.x, location.y);

      Chunk::Create_Chunk(level,
                          location,
                          game.map[level][location].defaultChunk,
                          game.map[level][location].chunk,
                          game.map[level][location].rooms,
                          game.map[level][location].pathing,
                          seed, game.objects[level][location]);
      std::cout << "chunk created" << std::endl;

      //Connect Pathing
        //check which adjacent chunks exist
        //if they exist, add them to the pathing map

//        if (game.map[level].count({location.x--, location.y}) > 0) {
//          std::cout << "connecting left chunk" << std::endl;
//          Pathing::Connect_Chunks(game.map[level][location].pathing, game.map[level][{location.x--, location.y}].pathing, -1, 0);
//        }
//        if (game.map[level].count({location.x++, location.y}) > 0) {
//          std::cout << "connecting right chunk" << std::endl;
//          Pathing::Connect_Chunks(game.map[level][location].pathing, game.map[level][{location.x++, location.y}].pathing, 1, 0);
//        }
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
    else {
      std::cout << "chunk already exists" << std::endl;
    }
  }

  void Check_Map_Chunk(Game::Instance &game) {
    if (game.Get_Player().position.x < game.Get_Player().vision && game.Get_Player().position.y < game.Get_Player().vision) {
      Component::Position location = game.Get_Player().location;
      location.x--;
      location.y--;
      Add_Map_Chunk(game, game.Get_Player().level, location);
    }
    if (game.Get_Player().position.x >= Component::mapWidth - game.Get_Player().vision && game.Get_Player().position.y >= Component::mapWidth - game.Get_Player().vision) {
      Component::Position location = game.Get_Player().location;
      location.x++;
      location.y++;
      Add_Map_Chunk(game, game.Get_Player().level, location);
    }
    if (game.Get_Player().position.x < game.Get_Player().vision && game.Get_Player().position.y >= Component::mapWidth - game.Get_Player().vision) {
      Component::Position location = game.Get_Player().location;
      location.x--;
      location.y++;
      Add_Map_Chunk(game, game.Get_Player().level, location);
    }
    if (game.Get_Player().position.x >= Component::mapWidth - game.Get_Player().vision && game.Get_Player().position.y < game.Get_Player().vision) {
      Component::Position location = game.Get_Player().location;
      location.x++;
      location.y--;
      Add_Map_Chunk(game, game.Get_Player().level, location);
    }
    if (game.Get_Player().position.x < game.Get_Player().vision) {
      Component::Position location = game.Get_Player().location;
      location.x--;
      Add_Map_Chunk(game, game.Get_Player().level, location);
    }
    if (game.Get_Player().position.x >= Component::mapWidth - game.Get_Player().vision) {
      Component::Position location = game.Get_Player().location;
      location.x++;
      Add_Map_Chunk(game, game.Get_Player().level, location);
    }
    if (game.Get_Player().position.y < game.Get_Player().vision) {
      Component::Position location = game.Get_Player().location;
      location.y--;
      Add_Map_Chunk(game, game.Get_Player().level, location);
    }
    if (game.Get_Player().position.y >= Component::mapWidth - game.Get_Player().vision) {
      Component::Position location = game.Get_Player().location;
      location.y++;
      Add_Map_Chunk(game, game.Get_Player().level, location);
    }

    std::cout << "Number of chunks: " <<  game.map[game.Get_Player().level].size() << std::endl;
    for (auto &chunk : game.map[game.Get_Player().level]) {
      std::cout << "Chunk: " << chunk.first.x << ", " << chunk.first.y << std::endl;
    }
  }

}