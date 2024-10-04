//
// Created by desktop on 9/14/24.
//
#include "attack.h"
#include "iostream"
#include "map.h"
#include "spawn.h"

namespace Attack {

void Check_Target_List(Game::State &game, const Units::Unit &unit, const Component::Position &moveTo,  Units::Objects &targets, char defaultChunk[Component::mapWidth][Component::mapWidth], char targetChunk[Component::mapWidth][Component::mapWidth]) {
    auto location = Component::Position{unit.location.x, unit.location.y};
    if (unit.position.x + moveTo.x < 0) {
      location = Component::Position{unit.location.x - 1, unit.location.y};
    }
    else if (unit.position.x + moveTo.x >= Component::mapWidth) {
      location = Component::Position{unit.location.x + 1, unit.location.y};
    }
    else if (unit.position.y + moveTo.y < 0) {
      location = Component::Position{unit.location.x, unit.location.y - 1};
    }
    else if (unit.position.y + moveTo.y >= Component::mapWidth) {
      location = Component::Position{unit.location.x, unit.location.y + 1};
    }

    targets = game.objects[unit.level][location];
    defaultChunk = game.map[unit.level][location].defaultChunk;
    targetChunk = game.map[unit.level][location].chunk;
}

  int Check_Target(Units::Objects &targets, int px, int py, int x, int y) {
    //if at the edge of the map
    int targetIndex;

    if (px+x < 0) {
      //get position of unit in the new chunk
      auto newPos = Component::Position{Component::mapWidth-1, py+y};
      targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos.x, newPos.y);
    }
    else if (px+x >= Component::mapWidth) {
      auto newPos = Component::Position{0, py+y};
      targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos.x, newPos.y);
    }
    else if (py+y < 0) {
      auto newPos = Component::Position{px+x, Component::mapWidth-1};
      targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos.x, newPos.y);
    }
    else if (py+y >= Component::mapWidth) {
      auto newPos = Component::Position{px+x, 0};
      targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos.x, newPos.y);
    }
    else {
      targetIndex = Units::Get_Unit_Index(targets.unitPositions, px + x, py + y);
    }
    return targetIndex;
  }

  //needs the correct objects list of the attacker
  //needs the correct objects list of the target
  //needs the correct chunk/defaultChunk of the target
  //then grab the index of the attacker
  //then grab the index of the target
    //which may be in a different chunk
  Damage Melee(Units::Unit &attacker, Units::Objects &targets, char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], int px, int py, int x, int y) {
    int targetIndex = Check_Target(targets, px, py, x, y);

    if (targetIndex == -1) {
      std::cout << "no target found" << std::endl;
      return {"", 0, false};
    }
    std::cout << "attacking: " << targetIndex << std::endl;
    auto &target = targets.units[targetIndex];

    target.health -= attacker.maxDamage;
    std::cout << Spawn::Get_Unit_Char(attacker.def.species) << " has attacked a: " << Spawn::Get_Unit_Char(target.def.species) << " for " << attacker.maxDamage << " damage" << std::endl;
    if (target.health <= 0) {
        std::cout << "target dead" << std::endl;
        Units::Remove_Unit(targets.unitPositions, targets.emptyUnitSlots, px+x, py+y);
        //need the grab the chunk the target is in
        Map::Reset_Tile(defaultChunk, chunk, px+x, py+y);
        return {std::to_string((int)target.def.species), attacker.maxDamage, true};
    }
    return {std::to_string((int)target.def.species), attacker.maxDamage, false};
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