

#include "collision.h"
#include "../../map/map.h"
#include "iostream"

namespace Collision {

  bool Wall_Collision(int x, int y, const char* direction) {
    std::cout << "basic: " << Map::Get_Map()[0][0] << std::endl;
    std::cout << "ref: " << &Map::Get_Map()[0][0] << std::endl;

    std::cout << "x: " << x << " y: " << y << std::endl;
    std::cout << "direction: " << *direction << std::endl;
    std::cout << "player position Map::Get_Map()[x][y] basic: " << Map::Get_Map()[x][y] << std::endl;
    std::cout << "player position Map::Get_Map()[x][y] ref: " << &Map::Get_Map()[x][y] << std::endl;

    switch (*direction) {
    case 'w':
      std::cout << "Map::Get_Map()[x][y-1]: " << Map::Get_Map()[x][y-1] << std::endl;
      if (Map::Get_Map()[x][y-1] == '#') {
        std::cout << "wall collision" << std::endl;
        return true;
        }
        return false;
      case 'a':
        std::cout << "Map::Get_Map()[x-1][y]: " << Map::Get_Map()[x-1][y] << std::endl;
        if (Map::Get_Map()[x-1][y] == '#') {
          std::cout << "wall collision" << std::endl;
          return true;
        }
        return false;
      case 's':
        std::cout << "Map::Get_Map()[x][y+1]: " << Map::Get_Map()[x][y+1] << std::endl;
        if (Map::Get_Map()[x][y+1] == '#') {
          std::cout << "wall collision" << std::endl;
          return true;
        }
        return false;
      case 'd':
        std::cout << "Map::Get_Map()[x+1][y]: " << Map::Get_Map()[x+1][y] << std::endl;
        if (Map::Get_Map()[x+1][y] == '#') {
          std::cout << "wall collision" << std::endl;
          return true;
        }
        return false;
    }
    return false;
  }

}