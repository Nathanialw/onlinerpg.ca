#pragma once

#include "string"
#include "game.h"

namespace Update {

     Component::Position Move_Direction(Game::Instance &game, const char *direction);

     std::string Update_Units(Game::Instance &game, const char *direction);
}