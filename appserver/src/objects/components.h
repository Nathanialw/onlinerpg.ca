#pragma once
//
// Created by desktop on 9/21/24.
//
#include <cstdint>
#include <functional>
#include <iostream>

#ifndef BROWSERRPG_COMPONENTS_H
#define BROWSERRPG_COMPONENTS_H

#endif // BROWSERRPG_COMPONENTS_H

namespace Component {
  typedef int8_t PosInt;
  static const uint8_t mapWidth = 99;

  struct Position {
    PosInt x;
    PosInt y;

    Position(PosInt X = 0, PosInt Y = 0) {
        x = X;
        y = Y;
    };

    bool operator==(const Position &other) const {
      return x == other.x && y == other.y;
    }

    Position Add(const Position &other) const {
      return {static_cast<PosInt>(x + other.x), static_cast<PosInt>(y + other.y)};
    }

    std::string As_String() const {
      return " x: " + std::to_string(x) + " y: " + std::to_string(y);
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