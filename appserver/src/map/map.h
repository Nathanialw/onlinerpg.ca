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


void Init();
std::string SendMapSegment(const Units::Unit &player, int state = 3);
std::string* Get_Map();
std::string Send();
}