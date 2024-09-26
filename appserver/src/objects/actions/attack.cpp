//
// Created by desktop on 9/14/24.
//
#include "attack.h"
#include "iostream"
#include "map.h"
#include "units.h"
#include "spawn.h"

namespace Attack {

  Damage Melee(int px, int py, int x, int y) {
    auto i = Units::Get_Unit_Index(px, py);
    std::cout << "attacker: " << i << std::endl;
    auto &unit = Units::Get_Units()->at(i);

    i = Units::Get_Unit_Index(px+x, py+y);
    if (i == -1) {
      std::cout << "no target found" << std::endl;
      return {"", 0, false};
    }
    std::cout << "attacking: " << i << std::endl;
    auto &target = Units::Get_Units()->at(i);

    target.health -= unit.maxDamage;
    std::cout << Spawn::Get_Unit_Char(unit.def.species) << " has attacked a: " << Spawn::Get_Unit_Char(target.def.species) << " for " << unit.maxDamage << " damage" << std::endl;
    if (target.health <= 0) {
        std::cout << "target dead" << std::endl;
        Units::Remove_Unit(px+x,py+y);
        Map::Reset_Tile(px+x, py+y);
        return {std::to_string((int)target.def.species), unit.maxDamage, true};
    }
    return {std::to_string((int)target.def.species), unit.maxDamage, false};
  }


}