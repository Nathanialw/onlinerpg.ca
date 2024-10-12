//
// Created by nathanial on 3/29/24.
//
#include <cstdint>
#include "string"
#include "iostream"
#include "unordered_map"

#include "utils.h"
#include "units.h"

namespace Units {

  void Remove_Unit(std::unordered_map<Component::Position, uint8_t> &unitPositions, std::vector<uint8_t> &emptyUnitSlots, int8_t x, int8_t y) {
    Component::Position pos = {x, y};
    uint8_t index = unitPositions[pos];
    //can't dp this because it will invalidate map indexes
    //    units.erase(units.begin() + index);
    //instead, save the index to a vector of empty slots
    if (index != 0) //ensure the 0 index is always open for the player
      emptyUnitSlots.push_back(index);
    unitPositions.erase(pos);
  }

  void Add_Unit(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, uint8_t> &unitPositions, std::vector<uint8_t> &emptyUnitSlots, Units::Unit &unit, int8_t x, int8_t y) {
    if (!emptyUnitSlots.empty()) {
      int index = emptyUnitSlots[emptyUnitSlots.size() - 1];
      emptyUnitSlots.pop_back();
      units[index] = unit;
      Component::Position pos = {x, y};
      unitPositions.emplace(pos, index);
    }
    else {
      units.push_back(unit);
      Component::Position pos = {x, y};
      unitPositions.emplace(pos, units.size() - 1);
    }
  }

  Units::Unit& Get_Unit_At_Position(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, uint8_t> &unitPositions, int8_t x, int8_t y) {
    if (Get_Unit_Index(unitPositions, x, y) == -1) {
      std::cout << "unit not found at: " << x << " " << y << std::endl;
      return units[0];
    }
    return units[Units::Get_Unit_Index(unitPositions, x, y)];
  }

  int8_t Get_Unit_Index(std::unordered_map<Component::Position, uint8_t> &unitPositions, int8_t x, int8_t y) {
    Component::Position pos = {x, y};
    if (unitPositions.count(pos) == 1) {
      std::cout << "unit found at: " << x << " " << y << std::endl;
      return unitPositions[pos];
    }
    return -1;
  }

  void Update_Unit_Position(std::unordered_map<Component::Position, uint8_t> &unitPositions, const int8_t &x, const int8_t &y, const int8_t &newX, const int8_t &newY) {
    std::cout << "updating unit position from: " << x << " " << y << " to: " << newX << " " << newY << std::endl;
    Component::Position pos = {x, y};
    int index = unitPositions[pos];
    Component::Position newPos = {newX, newY};
    unitPositions.erase(pos);
    unitPositions.emplace(newPos, index);
  }

  void Update_Unit_Position(std::unordered_map<Component::Position, uint8_t> &unitPositions, const Component::Position &pos, const Component::Position &newPos) {
    std::cout << "updating unit position from: " << pos.x << " " << pos.y << " to: " << newPos.x << " " << newPos.y << std::endl;
    int index = unitPositions[pos];
    unitPositions.erase(pos);
    unitPositions.emplace(newPos, index);
  }

  void Update_UnitsString(std::string &unitsString, int x, int y) {
    std::cout << "updating units string" << std::endl;
    std::string xStr = Utils::Prepend_Zero(x);
    std::string yStr = Utils::Prepend_Zero(y);
    unitsString.replace(2, 4, xStr + yStr);
  }


}
