#pragma once
//
// Created by desktop on 9/21/24.
//
#include <cstdint>
#include <functional>

#ifndef BROWSERRPG_COMPONENTS_H
#define BROWSERRPG_COMPONENTS_H

#endif // BROWSERRPG_COMPONENTS_H

namespace Component {
  static const int mapWidth = 99;

  struct Position {
    int8_t x;
    int8_t y;

    bool operator==(const Position &other) const {
      return x == other.x && y == other.y;
    }

    Position Add(const Position &other) const {
      return {static_cast<int8_t>(x + other.x), static_cast<int8_t>(y + other.y)};
    }
  };

  struct sNode {
    bool bObstacle = false;
    bool bVisited = false;
    float fGlobalGoal{};
    float fLocalGoal{};
    // position
    int x{};
    int y{};
    std::vector<sNode *> vecNeighbours;
    sNode *parent{};
  };
}

namespace std {
  template <> struct hash<Component::Position> {
      std::size_t operator()(const Component::Position &pos) const {
        return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
      }
  };
}