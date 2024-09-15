//
// Created by desktop on 9/14/24.
//
#include "attack.h"
#include "iostream"
#include "map.h"

namespace Attack {


bool Melee(int px, int py, int x, int y) {
  std::cout << "checking for goblin" << std::endl;
  if (Map::Get_Adjacent_Tile(px+x, py+y) == "g") {
        std::cout << "goblin found" << std::endl;
        //get the goblin from th units vector
        //Units::Get_Units()->at(1);
        //Map::Reset_Tile(px+x, py+y);

        //when it dies remove it from both the map and the units vector
        //and remove it from the send string
    return true;
  }
  return false;
}


}