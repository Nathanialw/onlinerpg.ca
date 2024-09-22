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


std::string Init();
std::string SendMapSegment(const Units::Unit &player, std::string direction, int state = 1);
std::string Get_Adjacent_Tile(int x, int y);
std::string* Update(int px, int py, int x, int y, std::string tile);
void Set_Tile(int x, int y, std::string tile);
void Reset_Tile(int x, int y);
}