#include "movement.h"
#include "units.h"
#include "pathing.h"
#include "attack.h"

namespace Movement {

  void Move(Game::State &game, int x, int y) {
    std::cout << "moving from: " << game.Get_Player().position.x << " " << game.Get_Player().position.y << " by: " << x << " " << y << std::endl;
    game.Get_Player().position.x += x;
    game.Get_Player().position.y += y;
  }

  void asd(const Component::Position &position, const Component::Position &target) {
    Attack::Check_For_Target(position, target);
  }

}