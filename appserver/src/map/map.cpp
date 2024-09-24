//
// Created by nathanial on 3/29/24.
//
#include "string"

#include "map.h"
#include "labyrinth.h"

namespace Map {
  const int mapWidth = 98;
  std::string defaultMap[mapWidth][mapWidth];
  std::string gameMap[mapWidth][mapWidth];

  std::string Get_Map() {
    std::string map;
    for (int j = 0; j <= mapWidth; j++) {
      for (int i = 0; i <= mapWidth; i++) {
            if (i < 0 || i >= mapWidth || j < 0 || j >= mapWidth)
              map += ' ';
            else
              map += gameMap[j][i];
      }
    }
    return map;
  }

 void Create_Map() {
    Labyrinth::Generate_Map();
    std::string labyrinthStr;
//    for (int i = 0; i < mapWidth; i++) {
//      for (int j = 0; j < mapWidth; j++) {
//            if (i == 0 || i == mapWidth - 1 || j == 0 || j == mapWidth - 1) {
//              defaultMap[i][j] = '#';
//              gameMap[i][j] = defaultMap[i][j];
//            }
//            else {
//              defaultMap[i][j] = '.';
//              gameMap[i][j] = defaultMap[i][j];
//            }
//      }
//    }

    for (int i = 0; i < Labyrinth::labyrinthWidth; i++) {
      for (int j = 0; j < Labyrinth::labyrinthWidth; j++) {
        labyrinthStr = Labyrinth::Get_Map_Cells()[Labyrinth::Get_Labyrinth()[j * Labyrinth::labyrinthWidth + i]];
        int charIndex = 0;

        for (int k = 0; k <= 3; k++) {
          for (int l = 0; l <= 3; l++) {
            if (((i * 3) + k) > 96) {
              std::cout << "i: " << i << " k: " << k << " l: " << l << std::endl;
            }
            defaultMap[(i * 3) + k][(j * 3) + l] = labyrinthStr[charIndex];
            gameMap[(i * 3) + k][(j * 3) + l] = defaultMap[(i * 3) + k][(j * 3) + l];
            charIndex++;
          }
        }
      }
    }

  }

  std::string Init() {
    Create_Map();
    auto map = Get_Map();
    return map;
  }

  void Set_Tile(int x, int y, const std::string &tile) {
    gameMap[y][x] = tile;
  }

  void Reset_Tile(int x, int y) {
    gameMap[y][x] = defaultMap[y][x];
  }

  void Update(int px, int py, int x, int y, const std::string &tile) {
    Reset_Tile(px, py);
    Set_Tile(px + x, py + y, tile);
  }

  // state 1 = initial map, 2 = update map
  std::string SendMapSegment(const Units::Unit &player, const std::string& direction, int state) {
    std::string mapSegment = std::to_string(state);
    mapSegment += std::to_string((player.vision * 2) + 1);
    mapSegment += direction;

    for (int j = player.position.y - player.vision; j <= player.position.y + player.vision; j++) {
        for (int i = player.position.x - player.vision; i <= player.position.x + player.vision; i++) {
            if (i < 0 || i >= mapWidth || j < 0 || j >= mapWidth)
              mapSegment += ' ';
            else
              mapSegment += gameMap[j][i];
        }
    }

    return mapSegment;
  }

  std::string Get_Adjacent_Tile(int x, int y) {
    std::string tile;
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapWidth)
        tile = " ";
    else
        tile = gameMap[y][x];
    return tile;
  }
}