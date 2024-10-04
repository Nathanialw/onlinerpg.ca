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
    for (int j = 0; j < Component::mapWidth; j++) {
      for (int i = 0; i < Component::mapWidth; i++) {
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

  void Create_Open_Map(Game::State &game) {
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

  void Update(Game::State &game, int level, Component::Position location, int px, int py, int x, int y, const char &tile) {
    Reset_Tile(game.map[level][location].defaultChunk, game.map[level][location].chunk, px, py);
    Set_Tile(game.map[level][location].chunk, px + x, py + y, tile);
  }

  void Update(Game::State &game, int level, Component::Position formerPosition, Component::Position newPosition, Component::Position formerLocation, Component::Position newLocation, const char &tile) {
    Reset_Tile(game.map[level][formerLocation].defaultChunk, game.map[level][formerLocation].chunk, formerPosition.x, formerPosition.y);
    Set_Tile(game.map[level][newLocation].chunk, newPosition.x, newPosition.y, tile);
  }

  void Add_Map_Segment(Game::State &game, int i, int j, int offsetX, int offsetY, std::string &mapSegment) {
    auto location = game.Get_Player().location;
    location.x += offsetX;
    location.y += offsetY;
    auto c = game.map[game.Get_Player().level][location].chunk[j][i];
    mapSegment += c;
  }

  void Handle_Boundary(Game::State &game, int i, int j, std::string &mapSegment) {
    static const std::unordered_map<std::string, std::function<void()>> boundaryHandlers = {
        {"-1,-1", [&]() { Add_Map_Segment(game, Component::mapWidth + i, Component::mapWidth + j, -1, -1, mapSegment); }},
        {"1,1",   [&]() { Add_Map_Segment(game, i - Component::mapWidth, j - Component::mapWidth, 1, 1, mapSegment); }},
        {"-1,1",  [&]() { Add_Map_Segment(game, Component::mapWidth + i, j - Component::mapWidth, -1, 1, mapSegment); }},
        {"1,-1",  [&]() { Add_Map_Segment(game, i - Component::mapWidth, Component::mapWidth + j, 1, -1, mapSegment); }},
        {"-1,0",  [&]() { Add_Map_Segment(game, Component::mapWidth + i, j, -1, 0, mapSegment); }},
        {"1,0",   [&]() { Add_Map_Segment(game, i - Component::mapWidth, j, 1, 0, mapSegment); }},
        {"0,-1",  [&]() { Add_Map_Segment(game, i, Component::mapWidth + j, 0, -1, mapSegment); }},
        {"0,1",   [&]() { Add_Map_Segment(game, i, j - Component::mapWidth, 0, 1, mapSegment); }}
    };

    std::string key = std::to_string((i < 0) ? -1 : (i >= Component::mapWidth) ? 1 : 0) + "," +
                      std::to_string((j < 0) ? -1 : (j >= Component::mapWidth) ? 1 : 0);

    if (boundaryHandlers.find(key) != boundaryHandlers.end()) {
      boundaryHandlers.at(key)();
    } else {
      mapSegment += game.map[game.Get_Player().level][game.Get_Player().location].chunk[j][i];
    }
  }

  // state 1 = initial map, 2 = update map
  std::string SendMapSegment(Game::State &game, const std::string& direction, int state) {
    std::string mapSegment = std::to_string(state);

    mapSegment += std::to_string((game.Get_Player().vision * 2) + 1);
    mapSegment += direction;
    std::string mapString;

    for (int j = game.Get_Player().position.y - game.Get_Player().vision; j <= game.Get_Player().position.y + game.Get_Player().vision; j++) {
        for (int i = game.Get_Player().position.x - game.Get_Player().vision; i <= game.Get_Player().position.x + game.Get_Player().vision; i++) {
          Handle_Boundary(game, i, j, mapSegment);
      }
    }
//    std::cout << "map sent!" << std::endl;
//    auto sentMap = mapSegment.substr(8);
//    for (int i = 0; i < player.vision * 2 + 1; i++) {
//      std::cout << sentMap.substr(i * (player.vision * 2 + 1), player.vision * 2 + 1) << std::endl;
//    }
    return mapSegment;
  }

  std::string Get_Adjacent_Tile(Game::State &game, int level, Component::Position location, int x, int y) {
    std::string tile;
    if (x < 0 || x >= Component::mapWidth || y < 0 || y >= Component::mapWidth)
        tile = " ";
    else
        tile = game.map[level][location].chunk[y][x];
    return tile;
  }

  void Add_Map_Chunk(Game::State &game, int level, Component::Position location) {
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
    }
    else {
      std::cout << "chunk already exists" << std::endl;
    }
  }

  void Check_Map_Chunk(Game::State &game) {
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