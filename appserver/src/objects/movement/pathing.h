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

  void Move_To(Component::Position &position, const Component::Position &targetPosition);
  bool Init(const std::string &mapString);
  void Update(const std::string &mapString);
}