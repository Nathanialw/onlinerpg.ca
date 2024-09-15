//
// Created by desktop on 9/14/24.
//
#include "attack.h"
#include "iostream"
#include "map.h"
#include "units.h"

namespace Attack {


bool Melee(int px, int py, int x, int y) {
  std::cout << "checking for goblin" << std::endl;
  if (Map::Get_Adjacent_Tile(px+x, py+y) == "g") {
    std::cout << "goblin found" << std::endl;

    //get the goblin from the units vector
    auto &goblin = Units::Get_Units()->at(Units::Get_Unit_Index(px+x, py+y));
    auto &player = Units::Get_Units()->at(0);
    goblin.health -= player.damage;

    if (goblin.health <= 0) {
        std::cout << "goblin dead" << std::endl;

        //remove the goblin from the map
        Map::Reset_Tile(px+x, py+y);
        //remove the goblin from the unitPositions map
        Units::Remove_Unit(px+x,py+y);
        Map::Reset_Tile(px+x, py+y);
        return false;
    }
    return true;
  }
  return false;
}


}