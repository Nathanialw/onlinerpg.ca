#pragma once

#include "game.h"

namespace Collision {

     bool Wall_Collision(Game::Instance &game, int level, Component::Position location, Component::Position newPosition);

}