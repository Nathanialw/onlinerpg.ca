//
// Created by nathanial on 3/29/24.
//
#include "string"

#include "map.h"

namespace Map {
  const int mapWidth = 99;
  std::string defaultMap[mapWidth][mapWidth];
  std::string gameMap[mapWidth][mapWidth];

  void Init() {
    for (int i = 0; i < mapWidth; i++) {
      for (int j = 0; j < mapWidth; j++) {
        if (i == 0 || i == mapWidth - 1 || j == 0 || j == mapWidth - 1) {
          defaultMap[i][j] = '#';
          gameMap[i][j] = defaultMap[i][j];
        }
        else {
          defaultMap[i][j] = '.';
          gameMap[i][j] = defaultMap[i][j];
        }
      }
    }
  }

  void Set_Tile(int x, int y, std::string tile) {
    gameMap[y][x] = tile;
  }

  void Reset_Tile(int x, int y) {
    gameMap[y][x] = defaultMap[y][x];
  }

  void Update(int px, int py, int x, int y, std::string tile) {
    Set_Tile(px, py, defaultMap[px][py]);
//    if (tile == " ")
//      Reset_Tile(px + x, py + y);
//    else
    Set_Tile(px + x, py + y, tile);
  }

  // state 1 = initial map, 2 = update map
  std::string SendMapSegment(const Units::Unit &player, std::string direction, int state) {
    std::string mapSegment = std::to_string(state);
    mapSegment += direction;
    mapSegment += std::to_string((player.vision * 2) + 1);

    for (int j = player.y - player.vision; j <= player.y + player.vision; j++) {
        for (int i = player.x - player.vision; i <= player.x + player.vision; i++) {
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