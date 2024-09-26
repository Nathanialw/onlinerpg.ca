#pragma once
//
// Created by desktop on 9/21/24.
//
#include <functional>

#ifndef BROWSERRPG_COMPONENTS_H
#define BROWSERRPG_COMPONENTS_H

#endif // BROWSERRPG_COMPONENTS_H

namespace Component {

  struct Position {
    int x;
    int y;

    bool operator==(const Position &other) const {
      return x == other.x && y == other.y;
    }
  };
}

namespace std {
template <> struct hash<Component::Position> {
    std::size_t operator()(const Component::Position &pos) const {
      return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
    }
};
}