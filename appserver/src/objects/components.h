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
  typedef int8_t PosInt;
  static const int mapWidth = 99;

  struct Position {
    PosInt x;
    PosInt y;

    bool operator==(const Position &other) const {
      return x == other.x && y == other.y;
    }

    Position Add(const Position &other) const {
      return {static_cast<PosInt>(x + other.x), static_cast<PosInt>(y + other.y)};
    }
  };

  struct sNode {
    float fGlobalGoal{};
    float fLocalGoal{};
    bool bObstacle = false;
    bool bVisited = false;
    // position
    PosInt x{};
    PosInt y{};
    std::vector<sNode *> vecNeighbours;
    sNode *parent{};
  };
}

namespace std {
  template <> struct hash<Component::Position> {
      std::size_t operator()(const Component::Position &pos) const {
        return std::hash<Component::PosInt>()(pos.x) ^ (std::hash<Component::PosInt>()(pos.y) << 1);
      }
  };
}