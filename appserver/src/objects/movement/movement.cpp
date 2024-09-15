#include "movement.h"
#include "units.h"

namespace Movement {

  void Move(int x, int y) {
    auto &player = Units::Get_Units()->at(0);
//    auto &player = Units::units[0];
    player.x += x;
    player.y += y;
  }


}