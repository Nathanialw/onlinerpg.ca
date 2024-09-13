

#include "collision.h"
#include "../../map/map.h"
#include "iostream"

namespace Collision {

  bool Wall_Collision(int x, int y, const char* direction) {
    std::cout << "Map::Get_Map()[0][6]: " << Map::Get_Map()[0][6] << std::endl;

    switch (*direction) {
    case 'w':
      if (Map::Get_Map()[x][y-1] == '#') {
        return true;
        }
        return false;
      case 'a':
        if (Map::Get_Map()[x-1][y] == '#') {
          return true;
        }
        return false;
      case 's':
        if (Map::Get_Map()[x][y+1] == '#') {
          return true;
        }
        return false;
      case 'd':
        if (Map::Get_Map()[x+1][y] == '#') {
          return true;
        }
        return false;
    }
    return false;
  }

}