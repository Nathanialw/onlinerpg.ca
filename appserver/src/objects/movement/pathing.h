#pragma once
#include "components.h"
#include "string"

//
// Created by desktop on 9/21/24.
//

#ifndef BROWSERRPG_PATHING_H
#define BROWSERRPG_PATHING_H

#endif // BROWSERRPG_PATHING_H

namespace Pathing {
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

  Component::Position Move_To(std::array<Pathing::sNode, Component::mapWidth * Component::mapWidth> &nodes, Component::Position &position, const Component::Position &targetPosition);
  bool Init(std::array<Pathing::sNode, Component::mapWidth * Component::mapWidth> &nodes, const std::string &mapString);
  void Update(std::array<Pathing::sNode, Component::mapWidth * Component::mapWidth> &nodes, const std::string &mapString);
}