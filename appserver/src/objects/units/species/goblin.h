#pragma once
//
// Created by desktop on 9/19/24.
//

#ifndef BROWSERRPG_GOBLIN_H
#define BROWSERRPG_GOBLIN_H

#endif // BROWSERRPG_GOBLIN_H

#include "units.h"
#include "game.h"

namespace Species {
     std::string Get_Unit_Data_As_string(Game::Instance &game, const std::string &msg);

     std::string Get_Unit_Data_As_string(Game::Instance &game, Component::Position &position);
}