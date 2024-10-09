#pragma once
#include "game.h"

namespace Collision {

  bool Wall_Collision(Game::Instance &game, int level, Component::Position location, int px, int py, int x, int y);

}