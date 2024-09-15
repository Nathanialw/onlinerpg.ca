

#include "collision.h"
#include "../../map/map.h"
#include "iostream"

namespace Collision {

  bool Wall_Collision(int px, int py, int x, int y) {
    std::cout << "Checking Wall_Collision..." << std::endl;
    if (Map::Get_Adjacent_Tile(px + x, py + y) == "#") {
      return true;
    }
    return false;
  }
}