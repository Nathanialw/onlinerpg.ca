#pragma once
//
// Created by desktop on 9/30/24.
//

#include "string"
#include "vector"
#include "unordered_map"

#include "components.h"
#include "units.h"
#include "pathing.h"
#include "procgen.h"
#include "chunk.h"

#ifndef BROWSERRPG_GAME_H
#define BROWSERRPG_GAME_H


namespace Game {


     struct Level {
	std::unordered_map<Component::Position, Units::Objects> objects;
	std::unordered_map<Component::Position, std::unordered_map<Component::Position, Items::Ground>> items{};
	std::unordered_map<Component::Position, Chunk::Map_Chunk> map;

	Level() {
		std::cout << "Level created" << std::endl;
	};
     };

     //all of these need to be saved into a database
     struct Instance {
	//player id
	//saved into the db to link the player to the game data

	//session
	std::string session_id;
	//    int duration = 0;
	//all of these need to be saved into a database

	std::vector<Level> levels;


	//current turn
	//    int time = 0;
	//    int turn = 0;
	//start day jan 1 2024
	//attack/move = 1 min
	//1 day = 1440 min
	//get tired
	//sleep = 8 hours = 480 turns
	//active time = 960 turns/day
	//get hungry = 1/day

	//rest = 5min, unless interrupted

	//player
	uint16_t player_id = 0;
	std::vector<std::string> player_names;
          std::unordered_map<ItemID, ItemEffectUID> knownUsables;

	std::vector<std::pair<uint8_t, uint8_t>> updateInventory{};
	int8_t updateEquipment  = -1;
	int8_t updateBag  = -1;

	int8_t level = 0;
	Component::Position location = {0, 0};

	explicit Instance(const std::string &sessionID);

	//seed
	Proc_Gen::Seed seed;

	Unit::Unit &Get_Player();

	Units::Objects &Get_Objects();

	Units::Objects &Get_Objects(Unit::Position position);

	Units::Objects &Get_Objects(uint8_t mapLevel, Component::Position location);

	Items::Ground &Get_Items();

	Items::Ground &Get_Items(Unit::Position position);

	Items::Ground &Get_Items(Component::Position location, Component::Position position);

	Chunk::Map_Chunk &Get_Map();

	Chunk::Map_Chunk &Get_Map(Component::Position mapLocation);

	Chunk::Map_Chunk &Get_Map(uint8_t currentLevel, Component::Position currentLocation);

	void Set_Player_New_Chunk(Unit::Position position);

	bool Exists();
     };

}


#endif // BROWSERRPG_GAME_H










