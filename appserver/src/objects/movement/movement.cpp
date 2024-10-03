#include "movement.h"
#include "units.h"

namespace Movement {

  void Move(Game::State &game, int x, int y) {
    std::cout << "moving from: " << game.Get_Player().position.x << " " << game.Get_Player().position.y << " by: " << x << " " << y << std::endl;
    game.Get_Player().position.x += x;
    game.Get_Player().position.y += y;
  }


}