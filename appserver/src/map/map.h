#pragma once
//
// Created by nathanial on 3/29/24.
//

#ifndef BROWSERRPG_MAP_H
#define BROWSERRPG_MAP_H

#endif //BROWSERRPG_MAP_H

#include "string"
#include "units.h"

namespace Map {
const int mapWidth = 99;
static std::string map[mapWidth][mapWidth];

void Init();
std::string SendMapSegment(const Units::Unit &player, int state = 3);
std::string Send();
}