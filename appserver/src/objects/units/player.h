//
// Created by desktop on 9/30/24.
//

#ifndef BROWSERRPG_PLAYER_H
#define BROWSERRPG_PLAYER_H

#endif // BROWSERRPG_PLAYER_H

#include "string"
#include "game.h"

namespace Player {

  std::string Get_Stats(Game::Instance &game);
  void Spawn(Game::Instance &game, int level, Component::Position location, Component::Position position, const std::basic_string<char> &characterCreate);
}