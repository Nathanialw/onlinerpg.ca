//
// Created by desktop on 9/19/24.
//
#include "string"
#include "goblin.h"
#include "units.h"
#include "utils.h"
#include "iostream"
#include "game.h"

// name
// gender
// pic
// health/maxhealth
// damage range
// AC
// speed
// vision
// alignment

//type? (fire/ice/etc maybe not sure if will use)

namespace Species {
     std::string Get_Unit_Data_As_string(Game::Instance &game, const std::string &msg) {
	     int8_t mapPositionX = game.Get_Player().position.position.x - game.Get_Player().stats.vision + std::stoi(msg.substr(0, 2));
	     int8_t mapPositionY = game.Get_Player().position.position.y - game.Get_Player().stats.vision + std::stoi(msg.substr(2, 2));
	     Component::Position position = {mapPositionX, mapPositionY};

	     //will need to use mouse coords to determine level/location, but for now you can only get from the same map chunk/level as the player
	     auto unit = Units::Get_Unit_At_Position(game.Get_Objects().units, game.Get_Objects().unitPositions, position);

	     //unit ID for the DB
	     std::cout << "unitID  int8: " << unit.stats.unitID << std::endl;
	     auto unitID = Utils::Prepend_Zero_By_Digits(unit.stats.unitID, 3);
	     std::cout << "unitID str: " << unitID << std::endl;
	     //name uID from "names" table, save in unit class
	     //vision from DB
	     //speed from DB
	     //alignment from DB
	     //bio from DB
	     //pic from DB

	     //append to the message
	     //age random generate
	     //health random generate + level + items
	     //gender random generate
	     //damage random generate + items
	     //AC random generate + items

	     std::cout << "unit name int16: " << unit.name.firstName << std::endl;
	     auto name = Utils::Prepend_Zero_By_Digits(unit.name.firstName, 4);
	     std::cout << "unit name str: " << name << std::endl;

	     auto age = Utils::Prepend_Zero_By_Digits(unit.stats.age, 3);
	     std::string gender = std::to_string((int) unit.def.gender);

	     auto health = Utils::Prepend_Zero_3Digit(unit.stats.health) + Utils::Prepend_Zero_3Digit(unit.stats.healthMax);
	     auto damage = Utils::Prepend_Zero(unit.stats.minDamage) + Utils::Prepend_Zero(unit.stats.maxDamage);
	     auto AC = Utils::Prepend_Zero(unit.stats.AC);
	     auto pic = Utils::Prepend_Zero_By_Digits(unit.stats.picNum, 2);


	     return unitID + name + age + gender + health + damage + AC + pic + unit.traits.As_Sendable_String();
     }
}