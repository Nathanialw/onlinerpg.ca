//
// Created by desktop on 9/30/24.
//
#include <iostream>

#include "player.h"
#include "utils.h"

#include "game.h"
#include "spawn.h"
#include "db.h"


namespace Player {

     void Set_Stats_Default(Unit::Def &def, Unit::Base_Stats &baseStats, Unit::Stats &stats) {
	     std::cout << "Set stats default: " << stats.health << " " << stats.healthMax << std::endl;
	     stats.minDamage = stoi(DB::Query("minDamage", "units", "uID", def.SpeciesIDStr()));
	     stats.maxDamage = stoi(DB::Query("maxDamage", "units", "uID", def.SpeciesIDStr()));
	     stats.healthMax = stoi(DB::Query("health", "units", "uID", def.SpeciesIDStr()));
	     stats.manaMax = stoi(DB::Query("mana", "units", "uID", def.SpeciesIDStr()));
	     stats.AC = stoi(DB::Query("AC", "units", "uID", def.SpeciesIDStr()));
	     stats.maxSpeed = stoi(DB::Query("speed", "units", "uID", def.SpeciesIDStr()));
	     stats.vision = stoi(DB::Query("vision", "units", "uID", def.SpeciesIDStr()));
	     std::cout << "Set stats default: " << stats.health << " " << stats.healthMax << std::endl;
     }

     template<typename T>
     void Cap_Stat(T &value1, int value2, int max) {
	     if ((value1 + value2) > max) {
		     value1 = max;
		     return;
	     }
	     value1 += static_cast<T>(value2);
     }

     template<typename T>
     void Cap_Stat(T &value1, T &value2, int max) {
	     if ((value1 + value2) > max) {
		     value1 = max;
		     return;
	     }
	     value1 += static_cast<T>(value2);
     }



     Unit::Stats Get_Stats_Gear(Items::Equipped &equipment) {
	     Unit::Stats itemStats;
	     for (const auto &slot: equipment) {
		     auto mods = slot.Get_Modifiers();
		     for (const auto &mod: mods) {
			     if (mod.uID == 0)
				     continue;

			     auto modType = DB::Query("name", "modifiers", "uID", mod.As_String());
			     int amount = stoi(DB::Query("effect", "modifiers", "uID", mod.As_String()));

			     std::cout << "modType: " << modType << " amount: " << amount << std::endl;

			     if (modType == "health") {
				     Cap_Stat(itemStats.health, amount, 999);
			     } else if (modType == "mana") {
				     Cap_Stat(itemStats.mana, amount, 999);
			     } else if (modType == "speed") {
				     Cap_Stat(itemStats.speed, amount, 99);
			     } else if (modType == "vision") {
				     Cap_Stat(itemStats.vision, amount, 9);
			     } else if (modType == "AC") {
				     Cap_Stat(itemStats.AC, amount, 99);
			     } else if (modType == "minDamage") {
				     Cap_Stat(itemStats.minDamage, amount, 99);
			     } else if (modType == "maxDamage") {
				     Cap_Stat(itemStats.maxDamage, amount, 99);
			     }
		     }
	     }
	     return itemStats;
     }

     void Apply_Stat_Bonuses(Unit::Stats &stats, Unit::Stats &itemStats) {
	     Cap_Stat(stats.healthMax, itemStats.health, 999);
	     Cap_Stat(stats.manaMax, itemStats.mana, 999);
	     Cap_Stat(stats.AC, itemStats.AC, 99);
	     Cap_Stat(stats.maxSpeed, itemStats.maxSpeed, 99);
	     Cap_Stat(stats.vision, itemStats.vision, 99);
	     Cap_Stat(stats.minDamage, itemStats.minDamage, 99);
	     Cap_Stat(stats.maxDamage, itemStats.maxDamage, 99);
     }

     void Update_Stats(Unit::Unit &player) {
	     std::cout << "updating stats full" << std::endl;
	     Set_Stats_Default(player.def, player.baseStats, player.stats);
	     auto itemStats = Get_Stats_Gear(player.equipment);
	     Apply_Stat_Bonuses(player.stats, itemStats);
	     std::cout << "updated stats full" << std::endl;
     }

     void Update_Stats(Unit::Unit &player, int8_t &update) {
	     if (update != -1) {
		     std::cout << "updating stats" << std::endl;
		     Set_Stats_Default(player.def, player.baseStats, player.stats);
		     auto itemStats = Get_Stats_Gear(player.equipment);
		     Apply_Stat_Bonuses(player.stats, itemStats);
		     std::cout << "updated stats" << std::endl;
	     }
     }

     std::string Get_Stats(Game::Instance &game) {
	     std::cout << "sending char stats back  to client" << std::endl;

	     auto stats = game.Get_Player().stats;
	     auto name = game.Get_Player().name.firstName;
	     auto def = game.Get_Player().def;

	     auto health = Utils::Prepend_Zero_3Digit(stats.health) + Utils::Prepend_Zero_3Digit(stats.healthMax);
	     auto speed = std::to_string(stats.speed) + std::to_string(stats.maxSpeed);
	     auto damage = Utils::Prepend_Zero(stats.minDamage) + Utils::Prepend_Zero(stats.maxDamage);
	     auto variableStats = "001" + Utils::Prepend_Zero(stats.AC) + Utils::Prepend_Zero_3Digit(stats.age) + health + speed + damage;

	     std::string statsStr = "1111" + game.player_names[name] + variableStats + std::to_string((int) def.gender) + std::to_string((int) def.species) + std::to_string((int) def.unitClass) + std::to_string((int) def.alignment);
	     std::cout << "3" + statsStr << " Char stats sent!" << std::endl;
	     return "3" + statsStr;
     }

// a string of only the stats that have been updated
     std::string Update_Stats(Game::Instance &game) {
	     std::cout << "sending char stats back  to client" << std::endl;

	     auto stats = game.Get_Player().stats;
	     auto name = game.Get_Player().name.firstName;
	     auto def = game.Get_Player().def;

	     auto health = Utils::Prepend_Zero_3Digit(stats.health) + Utils::Prepend_Zero_3Digit(stats.healthMax);
	     auto speed = std::to_string(stats.speed) + std::to_string(stats.maxSpeed);
	     auto damage = Utils::Prepend_Zero(stats.minDamage) + Utils::Prepend_Zero(stats.maxDamage);
	     auto pic = "001";
	     auto variableStats = pic + Utils::Prepend_Zero(stats.AC) + Utils::Prepend_Zero_3Digit(stats.age) + health + speed + damage;

	     std::string statsStr = "1111" + game.player_names[name] + variableStats + std::to_string((int) def.gender) + std::to_string((int) def.species) + std::to_string((int) def.unitClass) + std::to_string((int) def.alignment);
	     std::cout << "3" + statsStr << " Char stats sent!" << std::endl;
	     return "3" + statsStr;
     }

     void Spawn(Game::Instance &game, int level, Component::Position location, Component::Position position, const std::basic_string<char> &characterCreate) {
	     auto length = characterCreate.size();

	     std::cout << "Character create: " << characterCreate << std::endl;
	     std::string name = characterCreate.substr(1, length - 5);
	     std::cout << "Name: " << name << std::endl;
	     std::string genderStr = characterCreate.substr(length - 4, 1);
	     std::cout << "Gender: " << genderStr << std::endl;
	     std::string speciesStr = characterCreate.substr(length - 3, 1);
	     std::cout << "Species: " << speciesStr << std::endl;
	     std::string classStr = characterCreate.substr(length - 2, 1);
	     std::cout << "Class: " << classStr << std::endl;
	     std::string alignmentStr = characterCreate.substr(length - 1, 1);
	     std::cout << "Alignment: " << alignmentStr << std::endl;

	     auto gender = (Unit::Gender) std::stoi(genderStr);
	     auto species = (Unit::Species) std::stoi(speciesStr);
	     auto unitClass = (Unit::Class) std::stoi(classStr);
	     auto alignment = (Unit::Alignment) std::stoi(alignmentStr);
	     auto picNum = 0;

	     std::cout << "Spawn player" << std::endl;
	     Spawn::Add_Unit(game.Get_Objects(), level, location, position, game.player_id, gender, species, unitClass, alignment, picNum);
	     std::cout << "Player spawned" << std::endl;
	     game.player_names.push_back(name);
	     std::cout << "name: " << game.player_names[game.player_id] << std::endl;
	     game.player_id++;
	     std::cout << "size: " << game.Get_Objects().units.size() << std::endl;

	     game.Get_Player().stats.minDamage = stoi(DB::Query("minDamage", "units", "uID", game.Get_Player().def.SpeciesIDStr()));
	     game.Get_Player().stats.maxDamage = stoi(DB::Query("maxDamage", "units", "uID", game.Get_Player().def.SpeciesIDStr()));
	     game.Get_Player().stats.healthMax = stoi(DB::Query("health", "units", "uID", game.Get_Player().def.SpeciesIDStr()));
	     game.Get_Player().stats.manaMax = stoi(DB::Query("mana", "units", "uID", game.Get_Player().def.SpeciesIDStr()));
	     game.Get_Player().stats.AC = stoi(DB::Query("AC", "units", "uID", game.Get_Player().def.SpeciesIDStr()));
	     game.Get_Player().stats.maxSpeed = stoi(DB::Query("speed", "units", "uID", game.Get_Player().def.SpeciesIDStr()));
	     game.Get_Player().stats.vision = stoi(DB::Query("vision", "units", "uID", game.Get_Player().def.SpeciesIDStr()));

	     std::cout << "health: " << game.Get_Player().stats.health << std::endl;
     }

}