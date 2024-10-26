#pragma once
#include "components.h"
#include "string"

//
// Created by desktop on 9/21/24.
//

#ifndef BROWSERRPG_PATHING_H
#define BROWSERRPG_PATHING_H


namespace Pathing {
  typedef Component::sNode Map[Component::mapWidth * Component::mapWidth];

  void Connect_Chunks(Map chunk, Map newChunk, int x, int y);
  Component::Position Move_To(Map nodes, Component::Position &position, const Component::Position &targetPosition);
  bool Init(Map nodes, const std::string &mapString);
  void Update(Map nodes, const std::string &mapString);
}

#endif // BROWSERRPG_PATHING_H
