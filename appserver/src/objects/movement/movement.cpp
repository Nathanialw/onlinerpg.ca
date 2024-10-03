#include "movement.h"
#include "units.h"

namespace Movement {

  void Move(Game::State &game, int x, int y) {
    auto &player = game.Get_Player();;
    std::cout << "moving:: " << player.position.x << " " << player.position.y << " by: " << x << " " << y << std::endl;
    player.position.x += x;
    player.position.y += y;
  }


}