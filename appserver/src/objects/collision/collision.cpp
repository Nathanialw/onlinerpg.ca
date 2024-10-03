

#include "collision.h"
#include "map.h"
#include "iostream"

namespace Collision {

  bool Wall_Collision(Game::State &game, int level, Component::Position location, int px, int py, int x, int y) {
    std::cout << "Checking Wall_Collision..." << std::endl;
    if (Map::Get_Adjacent_Tile(game, level, location, px + x, py + y) == "#") {
      return true;
    }
    return false;
  }
}