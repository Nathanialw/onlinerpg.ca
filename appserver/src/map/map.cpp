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

  std::string SendMapSegment(const Units::Unit &player) {
    std::string mapSegment = "1";
    mapSegment += std::to_string((player.vision * 2) + 1);

    for (int j = player.x - player.vision; j <= player.x + player.vision; j++) {
        for (int i = player.y - player.vision; i <= player.y + player.vision; i++) {
            if (i < 0 || i >= mapWidth || j < 0 || j >= mapWidth)
              mapSegment += ' ';
            else
              mapSegment += map[i][j];
        }
    }

    return mapSegment;
  }

}