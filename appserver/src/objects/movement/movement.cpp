#include "movement.h"
#include "units.h"

namespace Movement {

  void Move(Game::State &game, int x, int y) {
    auto &player = game.Get_Player();;
    player.position.x += x;
    player.position.y += y;
  }


}