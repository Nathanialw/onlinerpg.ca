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

  void Set_Game_Map(char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth]) {
    std::cout << "Setting open map" << std::endl;
    for (int x = 0; x < Component::mapWidth; x++) {
      for (int y = 0; y < Component::mapWidth; y++) {
        chunk[x][y] = defaultChunk[x][y];
      }
    }
  }

  void Create_Open_Map(Game::State &game) {
    std::cout << "Creating open map" << std::endl;
    for (int i = 0; i < Component::mapWidth; i++) {
      for (int j = 0; j < Component::mapWidth; j++) {
        if (i == 0 || i == Component::mapWidth - 1 || j == 0 || j == Component::mapWidth - 1) {
          game.map[game.level][game.location].defaultChunk[i][j] = '#';
          game.map[game.level][game.location].chunk[i][j] = game.map[game.level][game.location].defaultChunk[i][j];
        } else {
          game.map[game.level][game.location].defaultChunk[i][j] = '.';
          game.map[game.level][game.location].chunk[i][j] = game.map[game.level][game.location].defaultChunk[i][j];
        }
      }
    }
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

  void Update(Game::State &game, int px, int py, int x, int y, const char &tile) {
    Reset_Tile(game.map[game.level][game.location].defaultChunk, game.map[game.level][game.location].chunk, px, py);
    Set_Tile(game.map[game.level][game.location].chunk, px + x, py + y, tile);
  }

  // state 1 = initial map, 2 = update map
  std::string SendMapSegment(Game::State &game, const std::string& direction, int state) {
    std::string mapSegment = std::to_string(state);
    auto &player = game.Get_Player();
    mapSegment += std::to_string((player.vision * 2) + 1);
    mapSegment += direction;
    std::string mapString;
    std::pair<int, int> directions[8] = {
        {-1, -1}, {1, 1}, {-1, 1}, {1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    for (int j = player.position.y - player.vision; j <= player.position.y + player.vision; j++) {
      for (int i = player.position.x - player.vision; i <= player.position.x + player.vision; i++) {
          if (i < 0 || i >= Component::mapWidth || j < 0 || j >= Component::mapWidth) {
            for (const auto &dir : directions) {
              int newX = i + dir.first * Component::mapWidth;
              int newY = j + dir.second * Component::mapWidth;

//              if (newX < 0 || newX >= Component::mapWidth || newY < 0 || newY >= Component::mapWidth) {
              auto location = game.location;
              location.x += dir.first;
              location.y += dir.second;

              char c = game.map[game.level][location].chunk[(newY + Component::mapWidth) % Component::mapWidth][(newX + Component::mapWidth) % Component::mapWidth];
              mapSegment += c;
//              }
            }
          }
          else
            mapSegment += game.map[game.level][game.location].chunk[j][i];
        }
    }
//    std::cout << "map sent!" << std::endl;
//    auto sentMap = mapSegment.substr(8);
//    for (int i = 0; i < player.vision * 2 + 1; i++) {
//      std::cout << sentMap.substr(i * (player.vision * 2 + 1), player.vision * 2 + 1) << std::endl;
//    }

    return mapSegment;
  }

  std::string Get_Adjacent_Tile(Game::State &game, int x, int y) {
    std::string tile;
    if (x < 0 || x >= Component::mapWidth || y < 0 || y >= Component::mapWidth)
        tile = " ";
    else
        tile = game.map[game.level][game.location].chunk[y][x];
    return tile;
  }

  void Add_Map_Chunk(Game::State &game, Component::Position location) {
    std::cout << "Add map chunk" << std::endl;
    std::cout << "location position: " << location.x << ", " << location.y << std::endl;

    std::cout << "Checking if location exists in map..." << std::endl;
    if (game.map[game.level].count(location) == 0) {
      // if player position is close to the edge of the chunk, create a new chunk add a new chunk
      std::cout << "Creating chunk" << std::endl;
      Proc_Gen::Seed seed;
      seed.seed = Proc_Gen::Create_Initial_Seed(location.x, location.y);

      Chunk::Create_Chunk(game.map[game.level][location].defaultChunk,
                          game.map[game.level][location].chunk,
                          game.map[game.level][location].rooms,
                          game.map[game.level][location].pathing,
                          seed, game.objects);
      std::cout << "chunk created" << std::endl;
      std::string mapString = Map::Get_Map(game.map[game.level][location].chunk);
      if (!mapString.empty()) {
          std::cout << "Map:" << std::endl;
          for (int i = 0; i < 99; i++) {
            std::cout << mapString.substr(i * 99, 99) << std::endl;
          }
      }
    }
    else {
      std::cout << "chunk already exists" << std::endl;
      std::string mapString = Map::Get_Map(game.map[game.level][location].chunk);
      if (!mapString.empty()) {
          std::cout << "Map:" << std::endl;
          for (int i = 0; i < 99; i++) {
            std::cout << mapString.substr(i * 99, 99) << std::endl;
          }
      }
    }
  }

  void Check_Map_Chunk(Game::State &game) {
    auto &player = game.Get_Player();
    std::pair<int, int> directions[8] = {
        {-1, -1}, {1, 1}, {-1, 1}, {1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    for (const auto &dir : directions) {
      if ((dir.first == -1 && player.position.x < player.vision) ||
          (dir.first == 1 && player.position.x >= Component::mapWidth - player.vision) ||
          (dir.second == -1 && player.position.y < player.vision) ||
          (dir.second == 1 && player.position.y >= Component::mapWidth - player.vision)) {

          Component::Position location = game.location;
          location.x += dir.first;
          location.y += dir.second;
          Add_Map_Chunk(game, location);
      }
    }
    std::cout << "Number of chunks: " <<  game.map[game.level].size() << std::endl;
    for (auto &chunk : game.map[game.level]) {
      std::cout << "Chunk: " << chunk.first.x << ", " << chunk.first.y << std::endl;
    }
  }

}