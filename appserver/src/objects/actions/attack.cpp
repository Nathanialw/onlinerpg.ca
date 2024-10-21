//
// Created by desktop on 9/14/24.
//
#include "attack.h"
#include "iostream"
#include "map.h"
#include "spawn.h"
#include "utils.h"

namespace Attack {

  Component::Position Check_Target_Location(const Units::Unit &unit, const Component::Position &moveTo) {
    auto location = unit.location;
    if (unit.position.x + moveTo.x < 0) {
      location.x--;
    }
    else if (unit.position.x + moveTo.x >= Component::mapWidth) {
      location.x++;
    }
    else if (unit.position.y + moveTo.y < 0) {
      location.y--;
    }
    else if (unit.position.y + moveTo.y >= Component::mapWidth) {
      location.y++;
    }
    return location;
  }

  int Check_Target(Units::Objects &targets, int px, int py, int x, int y) {
    //if at the edge of the map
    int targetIndex;

    if (px+x < 0) {
      Component::Position newPos = {Component::mapWidth-1, Utils::Add(py, y)};
      targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos.x, newPos.y);
    }
    else if (px+x >= Component::mapWidth) {
      Component::Position newPos = {0, Utils::Add(py, y)};
      targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos.x, newPos.y);
    }
    else if (py+y < 0) {
      Component::Position newPos = {Utils::Add(px, x), Component::mapWidth-1};
      targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos.x, newPos.y);
    }
    else if (py+y >= Component::mapWidth) {
      Component::Position newPos = {Utils::Add(px, x), 0};
      targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos.x, newPos.y);
    }
    else {
      targetIndex = Units::Get_Unit_Index(targets.unitPositions, Utils::Add(px, x), Utils::Add(py, y));
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
    auto targetIndex = Check_Target(targets, px, py, x, y);

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
        Units::Remove_Unit(targets.unitPositions, targets.emptyUnitSlots, Utils::Add(px, x), Utils::Add(py, y));
        //need the grab the chunk the target is in
        //if items drop
          //send the uIDs of the items to the client when he moves over them
        //else
        chunk[py+y][px+x] = ',';
        return {Utils::Prepend_Zero_By_Digits((int)target.def.species, 2), attacker.maxDamage, true};
    }
    return {Utils::Prepend_Zero_By_Digits((int)target.def.species, 2), attacker.maxDamage, false};
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