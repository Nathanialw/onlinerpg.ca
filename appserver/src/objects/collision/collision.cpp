

#include "collision.h"
#include "../../map/map.h"
#include "iostream"

namespace Collision {

  bool Wall_Collision(int x, int y, const char* direction) {
    std::cout << "Checking Wall_Collision..." << std::endl;


    switch (*direction) {
    case 'w':
      std::cout << Map::Get_Adjecent_Tile(x, y-1) << std::endl;
      if (Map::Get_Adjecent_Tile(x, y-1) == "#") {
        return true;
        }
        return false;
      case 'a':
        std::cout << Map::Get_Adjecent_Tile(x-1, y) << std::endl;
        if (Map::Get_Adjecent_Tile(x-1, y) == "#") {
          return true;
        }
        return false;
      case 's':
        std::cout << Map::Get_Adjecent_Tile(x, y+1) << std::endl;
        if (Map::Get_Adjecent_Tile(x, y+1) == "#") {
          return true;
        }
        return false;
      case 'd':
        std::cout << Map::Get_Adjecent_Tile(x+1, y) << std::endl;
        if (Map::Get_Adjecent_Tile(x+1, y) == "#") {
          return true;
        }
        return false;
    }
    return false;
  }

}