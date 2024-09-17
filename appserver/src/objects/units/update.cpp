
#include "update.h"
#include "units.h"
#include "map.h"
#include "collision.h"
#include "attack.h"
#include "movement.h"
#include "iostream"

namespace Update {
  void Update_Player(const char *direction) {
    int x, y;
    switch (*direction) {
    case 'w':
      x = 0, y = -1;
      break;
    case 'a':
      x = -1, y = 0;
      break;
    case 's':
      x = 0, y = 1;
      break;
    case 'd':
      x = 1, y = 0;
      break;
    }
    auto &player = Units::Get_Units()->at(0);
    // collision
    if (Collision::Wall_Collision(player.x, player.y, x, y)) {
      std::cout << "wall collision" << std::endl;
      return;
    }
    // if the nearby cell is an enemy, attack
    if (Attack::Melee(player.x, player.y, x, y)) {
      std::cout << "attack goblin" << std::endl;
      return;
    }
    // if the unit survives, return, else move to the cell
    Map::Update(player.x, player.y, x, y, Units::Get_Unit_Char(player.def.species));
    Movement::Move(x, y);
    Units::Update_UnitsString(x, y);
  }


  void Update_Units() {
    // move enitities
    //        for (auto & unit : *Get_Units()) {
    //          if (unit.type == ENEMY) {
    //                std::string x = std::to_string(unit.x);
    //                std::string y = std::to_string(unit.y);
    //                if (unit.x < 10)
    //                  x = "0" + x;
    //                if (unit.y < 10)
    //                  y = "0" + y;
    //
    //                unitPositions["x+y"];
    //
    //
    //            std::string position = "2@" + x + y;
    //            unitsOnMap.replace(0, 6, position);
    //
    //          }
    //        }
  }

  void Update_Units(const char *direction) {
    Update_Player(direction);
  }

}
