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
    std::cout << "checking for target" << std::endl;
    int damageDone = 0;
    int species;
    if (Map::Get_Adjacent_Tile(px+x, py+y) == "g") {
      std::cout << "target found" << std::endl;

      //get the goblin from the units vector
      auto &unit = Units::Get_Units()->at(Units::Get_Unit_Index(px, py));
      auto &target = Units::Get_Units()->at(Units::Get_Unit_Index(px+x, py+y));
      species = (int)target.def.species;
      //You have attacked a goblin for 5 damage

      target.health -= unit.maxDamage;
      damageDone = unit.maxDamage;
      if (target.health <= 0) {
          std::cout << "target dead" << std::endl;

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