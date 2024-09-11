#pragma once
//
// Created by nathanial on 3/29/24.
//

#ifndef BROWSERRPG_MAP_H
#define BROWSERRPG_MAP_H

#endif //BROWSERRPG_MAP_H

#include "string"

namespace Map {


  void Init();
  std::string SendMapSegment(const int &x, const int &y, const int &visionRadius);
  std::string Send();
}