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

  void Remove_Unit(std::unordered_map<Component::Position, int> &unitPositions, std::vector<int> &emptyUnitSlots, int x, int y) {
    Component::Position pos = {x, y};
    int index = unitPositions[pos];
    //can't dp this because it will invalidate map indexes
    //    units.erase(units.begin() + index);
    //instead, save the index to a vector of empty slots
    if (index != 0) //ensure the 0 index is always open for the player
      emptyUnitSlots.push_back(index);
    unitPositions.erase(pos);
  }

  Units::Unit& Get_Unit_At_Position(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, int> &unitPositions, int x, int y) {
    return units[Units::Get_Unit_Index(unitPositions, x, y)];
  }

  int Get_Unit_Index(std::unordered_map<Component::Position, int> &unitPositions, int x, int y) {
    Component::Position pos = {x, y};
    if (unitPositions.count(pos) == 1) {
      std::cout << "unit found at: " << x << " " << y << std::endl;
      return unitPositions[pos];
    }
    return -1;
  }

  void Update_Unit_Position(std::unordered_map<Component::Position, int> &unitPositions, const int &x, const int &y, const int &newX, const int &newY) {
    std::cout << "updating unit position from: " << x << " " << y << " to: " << newX << " " << newY << std::endl;
    Component::Position pos = {x, y};
    int index = unitPositions[pos];
    Component::Position newPos = {newX, newY};
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
