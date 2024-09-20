//
// Created by desktop on 9/14/24.
//
#include "attack.h"
#include "iostream"
#include "map.h"
#include "units.h"

namespace Attack {

  //damage done
  //that goblin has died
Damage Melee(int px, int py, int x, int y) {
    std::cout << "checking for goblin" << std::endl;
    int damageDone = 0;
    int species;
    if (Map::Get_Adjacent_Tile(px+x, py+y) == "g") {
      std::cout << "goblin found" << std::endl;

      //get the goblin from the units vector
      auto &goblin = Units::Get_Units()->at(Units::Get_Unit_Index(px+x, py+y));
      species = (int)goblin.def.species;
      //You have attacked a goblin for 5 damage
      auto &player = Units::Get_Units()->at(0);
      goblin.health -= player.maxDamage;
      damageDone = player.maxDamage;
      if (goblin.health <= 0) {
          std::cout << "goblin dead" << std::endl;

          //remove the goblin from the unitPositions map
          Units::Remove_Unit(px+x,py+y);
          Map::Reset_Tile(px+x, py+y);
          return {std::to_string(species), damageDone, true}; //move
      }
      return {std::to_string(species), damageDone, false}; //don't move
    }
    return {std::to_string(species), damageDone, false}; // move
  }


}