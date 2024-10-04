//
// Created by desktop on 9/14/24.
//
#include "attack.h"
#include "iostream"
#include "map.h"
#include "spawn.h"

namespace Attack {

  Damage Melee(Units::Objects &objects, char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], int px, int py, int x, int y) {
    auto i = Units::Get_Unit_Index(objects.unitPositions, px, py);
    std::cout << "attacker: " << i << std::endl;
    auto &unit = objects.units[i];

    //if at the edge of the map
    if (px+x < 0) {
      //get position of unit in the new chunk
      auto newPos = Component::Position{Component::mapWidth-1, py+y};
      i = Units::Get_Unit_Index(objects.unitPositions, newPos.x, newPos.y);
    }
    else if (px+x >= Component::mapWidth) {
      auto newPos = Component::Position{0, py+y};
      i = Units::Get_Unit_Index(objects.unitPositions, newPos.x, newPos.y);
    }
    else if (py+y < 0) {
      auto newPos = Component::Position{px+x, Component::mapWidth-1};
      i = Units::Get_Unit_Index(objects.unitPositions, newPos.x, newPos.y);
    }
    else if (py+y >= Component::mapWidth) {
      auto newPos = Component::Position{px+x, 0};
      i = Units::Get_Unit_Index(objects.unitPositions, newPos.x, newPos.y);
    }
    else {
      i = Units::Get_Unit_Index(objects.unitPositions, px + x, py + y);
    }

    if (i == -1) {
      std::cout << "no target found" << std::endl;
      return {"", 0, false};
    }
    std::cout << "attacking: " << i << std::endl;
    auto &target = objects.units[i];

    target.health -= unit.maxDamage;
    std::cout << Spawn::Get_Unit_Char(unit.def.species) << " has attacked a: " << Spawn::Get_Unit_Char(target.def.species) << " for " << unit.maxDamage << " damage" << std::endl;
    if (target.health <= 0) {
        std::cout << "target dead" << std::endl;
        Units::Remove_Unit(objects.unitPositions, objects.emptyUnitSlots, px+x, py+y);
        //need the grab the chunk the target is in
        Map::Reset_Tile(defaultChunk, chunk, px+x, py+y);
        return {std::to_string((int)target.def.species), unit.maxDamage, true};
    }
    return {std::to_string((int)target.def.species), unit.maxDamage, false};
  }

  bool Check_For_Target(const Component::Position &position, const Component::Position &target) {
    if (abs(position.x - target.x) < 6 && abs(position.y - target.y) < 6)
        return true;
    return false;
  }

  void Check_For_Target_On_Map_Chunk(const Component::Position &position, const Component::Position &target) {
    //only one of these can be true
    //need to create a temporary pathing map that merges the map chunks
    //corner cases merge 4 map chunks
    //edge cases merge 2 map chunks, unless close to the corner, then merge 4

    if (target.x < 0 && target.y < 0) {
        //target is on the top left map chunk
    }
    else if (target.x >= Component::mapWidth && target.y < 0) {
        //target is on the top right map chunk
    }
    else if (target.x < 0 && target.y >= Component::mapWidth) {
        //target is on the bottom left map chunk
    }
    else if (target.x >= Component::mapWidth && target.y >= Component::mapWidth) {
        //target is on the bottom right map chunk
    }
    else if (target.x < 0) {
        //target is on the left map chunk
    }
    else if (target.x >= Component::mapWidth) {
        //target is on the right map chunk
    }
    else if (target.y < 0) {
        //target is on the top map chunk
    }
    else if (target.y >= Component::mapWidth) {
        //target is on the bottom map chunk
    }
  }
}