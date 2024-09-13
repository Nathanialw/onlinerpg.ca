//
// Created by nathanial on 3/29/24.
//
#include "string"

#include "map.h"
#include "units.h"

namespace Map {
  const int mapWidth = 99;
  static std::string map[mapWidth][mapWidth];

  void Init() {
    for (int i = 0; i < mapWidth; i++) {
      for (int j = 0; j < mapWidth; j++) {
        if (i == 0 || i == mapWidth - 1 || j == 0 || j == mapWidth - 1)
          map[i][j] = '#';
        else
          map[i][j] = '.';
      }
    }
  }


  std::string Send() {
    std::string message = "1";
    message += std::to_string(mapWidth);

    for (auto & i : map) {
      for (const auto & j : i) {
        message += j;
      }
    }
    return message;
  }


  // state 1 = initial map, 2 = update map
  std::string SendMapSegment(const Units::Unit &player, int state) {
    std::string mapSegment = std::to_string(state);
    mapSegment += std::to_string((player.vision * 2) + 1);

    for (int j = player.y - player.vision; j <= player.y + player.vision; j++) {
        for (int i = player.x - player.vision; i <= player.x + player.vision; i++) {
            if (i < 0 || i >= mapWidth || j < 0 || j >= mapWidth)
              mapSegment += ' ';
            else
              mapSegment += map[j][i];
        }
    }

    return mapSegment;
  }

  std::string* Get_Map() {
    return *map;
  }

}