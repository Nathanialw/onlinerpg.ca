

#include "collision.h"
#include "../../map/map.h"
#include "iostream"

namespace Collision {

  bool Wall_Collision(int x, int y, const char* direction) {
    std::cout << "Checking Wall_Collision..." << std::endl;

    switch (*direction) {
    case 'w':
      std::cout << Map::map[x][y-1].c_str() << std::endl;
      if (Map::map[x][y-1] == "#") {
        return true;
        }
        return false;
      case 'a':
        std::cout << Map::map[x-1][y].c_str() << std::endl;
        if (Map::map[x-1][y] == "w") {
          return true;
        }
        return false;
      case 's':
        std::cout << Map::map[x][y+1].c_str() << std::endl;
        if (Map::map[x][y+1] == "#") {
          return true;
        }
        return false;
      case 'd':
        std::cout << Map::map[x+1][y].c_str() << std::endl;
        if (Map::map[x+1][y] == "#") {
          return true;
        }
        return false;
    }
    std::cout << "... false" << std::endl;
    return false;
  }

}