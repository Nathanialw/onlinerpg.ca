#pragma once
#include "components.h"
#include "string"

//
// Created by desktop on 9/21/24.
//

#ifndef BROWSERRPG_PATHING_H
#define BROWSERRPG_PATHING_H

#endif // BROWSERRPG_PATHING_H
#include "components.h"

namespace Pathing {


  Component::Position Move_To(Component::sNode nodes[Component::mapWidth * Component::mapWidth], Component::Position &position, const Component::Position &targetPosition);
  bool Init(Component::sNode nodes[Component::mapWidth * Component::mapWidth], const std::string &mapString);
  void Update(Component::sNode nodes[Component::mapWidth * Component::mapWidth], const std::string &mapString);
}