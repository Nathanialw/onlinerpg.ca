

#include "collision.h"
#include "map.h"
#include "iostream"

namespace Collision {

  bool Wall_Collision(Game::Instance &game, int level, Component::Position location, Component::Position newPosition) {
    auto tile = Map::Get_Adjacent_Tile(game, level, location, newPosition);
    std::cout << "Checking Wall_Collision, tile is: " << tile << std::endl;
    if (tile == "^") {
      return true;
    }
    return false;
  }
}