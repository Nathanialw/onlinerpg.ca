//
// Created by desktop on 9/14/24.
//
#include "attack.h"
#include "iostream"
#include "map.h"
#include "units.h"
#include "spawn.h"

namespace Attack {

  //damage done
  //that goblin has died
Damage Melee(int px, int py, int x, int y) {
    //get the goblin from the units vector
    auto &unit = Units::Get_Units()->at(Units::Get_Unit_Index(px, py));
    auto &target = Units::Get_Units()->at(Units::Get_Unit_Index(px+x, py+y));
    //You have attacked a goblin for 5 damage
    target.health -= unit.maxDamage;
    std::cout << "You have attacked a: " << Spawn::Get_Unit_Char(target.def.species) << " for " << unit.maxDamage << " damage" << std::endl;
    if (target.health <= 0) {
        std::cout << "target dead" << std::endl;
        //remove the goblin from the unitPositions map
        Units::Remove_Unit(px+x,py+y);
        Map::Reset_Tile(px+x, py+y);
        return {std::to_string((int)target.def.species), unit.maxDamage, true}; //move
    }
    return {std::to_string((int)target.def.species), unit.maxDamage, false}; //don't move
  }


}