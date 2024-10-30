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

     void Remove_Unit(std::unordered_map<Component::Position, uint8_t> &unitPositions, std::vector<uint8_t> &emptyUnitSlots, Component::Position position) {
	     int index = unitPositions[position];
	     //can't dp this because it will invalidate map indexes
	     //    units.erase(units.begin() + index);
	     //instead, save the index to a vector of empty slots
	     if (index != 0) //ensure the 0 index is always open for the player
		     emptyUnitSlots.push_back(index);
	     unitPositions.erase(position);
     }

     void Add_Unit(std::vector<Unit::Unit> &units, std::unordered_map<Component::Position, uint8_t> &unitPositions, std::vector<uint8_t> &emptyUnitSlots, Unit::Unit &unit, Component::Position &position) {
	     if (!emptyUnitSlots.empty()) {
		     int index = emptyUnitSlots[emptyUnitSlots.size() - 1];
		     emptyUnitSlots.pop_back();
		     units[index] = unit;
		     unitPositions.emplace(position, index);
	     } else {
		     units.push_back(unit);
		     unitPositions.emplace(position, units.size() - 1);
	     }
     }

     Unit::Unit &Get_Unit_At_Position(std::vector<Unit::Unit> &units, std::unordered_map<Component::Position, uint8_t> &unitPositions, Component::Position &position) {
	     if (Get_Unit_Index(unitPositions, position) == -1) {
		     std::cout << "unit not found at: " << position.As_String() << std::endl;
		     return units[0];
	     }
	     return units[Units::Get_Unit_Index(unitPositions, position)];
     }

     int Get_Unit_Index(std::unordered_map<Component::Position, uint8_t> &unitPositions, Component::Position position) {
	     if (unitPositions.count(position) == 1) {
		     std::cout << "unit found at: " << position.As_String() << std::endl;
		     return unitPositions[position];
	     }
	     return -1;
     }

     void Update_Unit_Position(std::unordered_map<Component::Position, uint8_t> &unitPositions, const Component::Position &position, const Component::Position &newPosition) {
	     std::cout << "updating unit position from: " << position.As_String() << " to: " << newPosition.As_String() << std::endl;
	     int index = unitPositions[position];
	     unitPositions.erase(position);
	     unitPositions.emplace(newPosition, index);
     }


     void Update_UnitsString(std::string &unitsString, int x, int y) {
	     std::cout << "updating units string" << std::endl;
	     std::string xStr = Utils::Prepend_Zero(x);
	     std::string yStr = Utils::Prepend_Zero(y);
	     unitsString.replace(2, 4, xStr + yStr);
     }


}
