//
// Created by nathanial on 3/29/24.
//
#include <cstdint>
#include "string"
#include "iostream"
#include "unordered_map"

#include "utils.h"

#include "attack.h"
#include "collision.h"
#include "map.h"
#include "units.h"

namespace Units {

//  std::unordered_map<uint16_t, std::string> entities;
  std::vector<Unit> units;
  //when adding new units, use the emptyUnitSlots vector to find the next empty slot before pushing back
  std::unordered_map<UnitPosition, int> unitPositions;
  static std::string unitsString;

  std::string Get_Units_String() {
    return unitsString;
  }

  std::unordered_map<UnitPosition, int>* Get_Unit_Positions() {
    return &unitPositions;
  }

  void Set_Units_String(const std::string &newUnitsString) {
    unitsString = newUnitsString;
  }

  std::vector<Unit> *Get_Units() { return &units; }

  void Remove_Unit(int x, int y) {
    UnitPosition pos = {x, y};
    int index = unitPositions[pos];
    //can't dp this because it will invalidate map indexes
    //    units.erase(units.begin() + index);
    unitPositions.erase(pos);
  }

  //is read only
  Unit Get_Player() {
    return units[0];
  }

  int Get_Unit_Index(int x, int y) {
    UnitPosition pos = {x, y};
    if (unitPositions.count(pos) == 1) {
      std::cout << "unit found at: " << x << " " << y << std::endl;
      return unitPositions[pos];
    }
    return -1;
  }

  Unit Get_Unit_At_Position(int x, int y) {
    return units[Get_Unit_Index(x, y)];
  }

  void Update_Unit_Position(const int &x, const int &y, const int &newX, const int &newY) {
    UnitPosition pos = {x, y};
    int index = unitPositions[pos];
    UnitPosition newPos = {newX, newY};
    unitPositions.erase(pos);
    unitPositions.emplace(newPos, index);
  }

//  void Add_Unit(int x, int y, const std::string &name, Gender gender, Species species, Class unitClass, Alignment alignment) {

  void Update_UnitsString(int x, int y) {
    std::string xStr = Utils::Prepend_Zero(x);
    std::string yStr = Utils::Prepend_Zero(y);
    unitsString.replace(2, 4, xStr + yStr);
  }

  std::string GetCharStats() {
    //only append with what is being updated
    //when the stat IS updated on then add it to the string

    //prepend with 0000 to tell which stats are being sent
    //name + gender + species + class + alignment

    auto player = Get_Player();

    auto health = Utils::Prepend_Zero_3Digit(player.health) + Utils::Prepend_Zero_3Digit(player.healthMax);
    auto speed = std::to_string(player.speed) + std::to_string(player.maxSpeed);
    auto damage = Utils::Prepend_Zero(player.minDamage) + Utils::Prepend_Zero(player.maxDamage);
    auto variableStats = player.potrait + Utils::Prepend_Zero(player.AC) + Utils::Prepend_Zero_3Digit(player.age) + health + speed + damage;

//    2 + 3 + 3 + 3 + 1 + 1 + 2 + 2

    std::string stats = "1111" + player.name + variableStats + std::to_string((int)player.def.gender) + std::to_string((int)player.def.species) + std::to_string((int)player.def.unitClass) + std::to_string((int)player.def.alignment);
    std::cout << "3" + stats << std::endl;
    return "3" + stats;
  }
//  1 2 4 8 16
}
