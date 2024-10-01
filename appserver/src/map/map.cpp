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

  std::string Get_Map(Game::State &game) {
    std::string map;
    for (int j = 0; j < Component::mapWidth; j++) {
      for (int i = 0; i < Component::mapWidth; i++) {
        if (i < 0 || i > Component::mapWidth || j < 0 || j > Component::mapWidth)
          map += ' ';
        else
          map += game.map[game.level][game.location].chunk[j][i];
      }
    }
    return map;
  }

  void Set_Game_Map(Game::State &game) {
    std::cout << "Setting open map" << std::endl;
    for (int x = 0; x < Component::mapWidth; x++) {
      for (int y = 0; y < Component::mapWidth; y++) {
        game.map[game.level][game.location].chunk[x][y] = game.map[game.level][game.location].defaultChunk[x][y];
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

  void Create_Labyrinth(Game::State &game) {
    std::cout << "Creating labyrinth" << std::endl;
    Labyrinth::Generate_Map(game.seed);
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
            game.map[game.level][game.location].defaultChunk[x][y] = labyrinthStr[charIndex];
            charIndex++;
          }
        }
      }
    }
  }

  std::string Init(Game::State &game) {
//    Create_Open_Map();
    Create_Labyrinth(game);
    Chunk::Add_Rooms(game.map[game.level][game.location].defaultChunk, game.map[game.level][game.location].rooms);
    Set_Game_Map(game);
    std::cout << "map inited" << std::endl;
    return Get_Map(game);
  }

  void Set_Tile(Game::State &game, int x, int y, const char &tile) {
    game.map[game.level][game.location].chunk[y][x] = tile;
  }

  void Reset_Tile(Game::State &game, int x, int y) {
    game.map[game.level][game.location].chunk[y][x] = game.map[game.level][game.location].defaultChunk[y][x];
  }

  void Update(Game::State &game, int px, int py, int x, int y, const char &tile) {
    Reset_Tile(game, px, py);
    Set_Tile(game, px + x, py + y, tile);
  }

  // state 1 = initial map, 2 = update map
  std::string SendMapSegment(Game::State &game, const std::string& direction, int state) {
    std::string mapSegment = std::to_string(state);
    auto &player = game.Get_Player();
    mapSegment += std::to_string((player.vision * 2) + 1);
    mapSegment += direction;

    for (int j = player.position.y - player.vision; j <= player.position.y + player.vision; j++) {
        for (int i = player.position.x - player.vision; i <= player.position.x + player.vision; i++) {
            if (i < 0 || i >= Component::mapWidth || j < 0 || j >= Component::mapWidth)
              mapSegment += ' ';
            else
              mapSegment += game.map[game.level][game.location].chunk[j][i];
        }
    }
    std::cout << "map sent!" << std::endl;

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
}