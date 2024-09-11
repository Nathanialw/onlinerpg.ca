//
// Created by nathanial on 3/29/24.
//
#include "string"

#include "map.h"

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

  std::string SendMapSegment(const int &x, const int &y, const int &visionRadius) {
    std::string mapSegment = "1";
    mapSegment += std::to_string(visionRadius * 2 + 1);

    for (int i = x - visionRadius; i <= x + visionRadius; i++) {
        for (int j = y - visionRadius; j <= y + visionRadius; j++) {
            mapSegment += map[i][j];
        }
    }

    return mapSegment;
  }

}