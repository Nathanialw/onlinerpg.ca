#pragma once

#include "string"
#include <vector>
//
// Created by nathanial on 3/29/24.
//

#ifndef BROWSERRPG_UNITS_H
#define BROWSERRPG_UNITS_H

#endif //BROWSERRPG_UNITS_H

#include "vector"
#include <functional>
#include "iostream"

#include "components.h"
#include "items.h"
#include "inventory.h"
#include "unit.h"

namespace Units {



     static std::string species[(uint8_t) Unit::Species::SIZE] = {
	"Alp",
	"Basilisk",
	"Centaur",
	"Dwarf",
	"Elf",
	"Fox",
	"Goblin",
	"Human",
	"Iguana",
	"Jackal",
	"Kobold",
	"Lamia",
	"Minotaur",
	"Nymph",
	"Orc",
	"Pixie",
	"Qat",
	"Rat",
	"Skeleton",
	"Treant",
	"Unicorn",
	"Valkyrie",
	"Warg",
	"Xana",
	"Yale",
	"Zombie",
	"Angel",
	"Byakhee",
	"Chimera",
	"Dragon",
	"Ebon",
	"Fairy",
	"Golem",
	"Harpy",
	"Imp",
	"Jinn",
	"Krampus",
	"Lich",
	"Medusa",
	"Naga",
	"Ogre",
	"Poltergeist",
	"Quinotaur",
	"Roc",
	"Satyr",
	"Troll",
	"Urias",
	"Vampire",
	"Witch",
	"Xanthus",
	"Yeti",
	"Ziburinis"
     };

     enum class Race {

     };



     static std::string gender[(uint8_t) Unit::Gender::SIZE] = {
	"male",
	"female"
     };












//  struct Map_Position {
//    Component::Position chunk;
//    Component::Position position;
//  };

     struct Objects {
	std::vector<Unit::Unit> units;
	std::unordered_map<Component::Position, uint8_t> unitPositions;
	std::vector<uint8_t> emptyUnitSlots;
     };

     int Get_Unit_Index(std::unordered_map<Component::Position, uint8_t> &unitPositions, Component::Position position);

     void Update_Unit_Position(std::unordered_map<Component::Position, uint8_t> &unitPositions, const Component::Position &position, const Component::Position &newPosition);

     void Remove_Unit(std::unordered_map<Component::Position, uint8_t> &unitPositions, std::vector<uint8_t> &emptyUnitSlots, Component::Position position);

//  Unit& Get_Unit_At_Position(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, int> &unitPositions, Component::Position &newPosition);
     Unit::Unit &Get_Unit_At_Position(std::vector<Unit::Unit> &units, std::unordered_map<Component::Position, uint8_t> &unitPositions, Component::Position &position);

     void Update_UnitsString(std::string &unitsString, int x, int y);

}

