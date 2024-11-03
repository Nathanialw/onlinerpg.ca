//
// Created by desktop on 9/25/24.
//
#include "spawn.h"
#include "map.h"
#include "units.h"
#include "utils.h"
#include "procgen.h"
#include "chunk.h"
#include "db.h"
#include "files.h"

namespace Spawn {

     const std::string pathToSpeciesImgs = "../public/assets/graphics/imgs/";

     char unitChars[(int) Unit::Species::SIZE] = {'a', 'b', 'c',
                                                  'd', 'e', 'f', 'g',
                                                  'h', 'i', 'j', 'k',
                                                  'l', 'm', 'n', 'o',
                                                  'p', 'q', 'r', 's',
                                                  't', 'u', 'v', 'w',
                                                  'x', 'y', 'z', 'A',
                                                  'B', 'C', 'D', 'E', 'F',
                                                  'G', 'H', 'I', 'J', 'K',
                                                  'L', 'M', 'N', 'O', 'P',
                                                  'Q', 'R', 'S', 'T', 'U',
                                                  'V', 'W', 'X', 'Y', 'Z'};

     char Get_Unit_Char(Unit::Species species) {
	     return unitChars[(int) species];
     }

     void Add_Unit(Units::Objects &objects, int level, Component::Position location, Component::Position position, const uint16_t &name, Unit::Gender gender, Unit::Species species, Unit::Class unitClass, Unit::Alignment alignment, uint8_t picNum) {
	     Unit::Unit unit(level, location);

	     //defined by where it is spawned
	     unit.def.species = species;
	     unit.stats.unitID = (uint8_t) species + 1;
	     unit.position.position = position;

	     //randomize, weighted
	     unit.def.gender = gender; //unless it is a gendered species
	     unit.def.unitClass = unitClass;

	     //query db for all of this
	     unit.def.alignment = alignment;
	     unit.name.firstName = name;
	     unit.stats.age = 16;

	     unit.stats.minDamage = stoi(DB::Query("minDamage", "units", "uID", unit.def.SpeciesIDStr()));
	     unit.stats.maxDamage = stoi(DB::Query("maxDamage", "units", "uID", unit.def.SpeciesIDStr()));
	     unit.stats.healthMax = stoi(DB::Query("health", "units", "uID", unit.def.SpeciesIDStr()));
	     unit.stats.manaMax = stoi(DB::Query("mana", "units", "uID", unit.def.SpeciesIDStr()));
	     unit.stats.AC = stoi(DB::Query("AC", "units", "uID", unit.def.SpeciesIDStr()));
	     unit.stats.maxSpeed = stoi(DB::Query("speed", "units", "uID", unit.def.SpeciesIDStr()));
	     unit.stats.vision = stoi(DB::Query("vision", "units", "uID", unit.def.SpeciesIDStr()));

	     unit.stats.speed = unit.stats.speed;
	     unit.stats.health = unit.stats.healthMax;
	     unit.stats.mana = unit.stats.manaMax;
	     unit.stats.speed = unit.stats.maxSpeed;

	     auto &units = objects.units;
	     auto &unitsPositions = objects.unitPositions;

	     auto &emptyUnitSlots = objects.emptyUnitSlots;
	     if (emptyUnitSlots.empty()) {
		     units.emplace_back(unit);
	     } else {
		     units.at(emptyUnitSlots.back()) = unit;
		     emptyUnitSlots.pop_back();
	     }
	     unitsPositions.emplace(position, units.size() - 1);
     }

     std::vector<Component::Position> Spawn_Unit(std::vector<Chunk::Room> &rooms) {
	     std::vector<Component::Position> placements;
	     Component::Position placement{};
	     Proc_Gen::Seed seed;

	     for (const auto &room: rooms) {
		     seed.seed = Proc_Gen::Create_Initial_Seed(room.x, room.y);
		     placement.x = Proc_Gen::Random_Int(room.x, room.x + room.w, seed);
		     placement.y = Proc_Gen::Random_Int(room.y, room.y + room.h, seed);
		     placements.emplace_back(placement);
	     }
	     return placements;
     }

     bool Add_Object(Units::Objects &objects, int level, Component::Position location, std::string &group, Component::Position position) {
	     if (position.x > Component::mapWidth - 1 || position.y > Component::mapWidth - 1 || position.x < 1 || position.y < 1) {
		     group.clear();
		     return false;
	     } else {
		     group += Utils::Prepend_Zero(position.x);
		     group += Utils::Prepend_Zero(position.y);

		     auto species = (Unit::Species) Utils::Random(0, (int) Unit::Species::SIZE - 1);
		     //check db if the species is gendered
		     auto gendered = DB::Query("isGendered", "units", "name", Units::species[(int) species]);
		     Unit::Gender gender;
		     (gendered == "1") ? gender = (Unit::Gender) Utils::Random(0, (int) Unit::Gender::SIZE - 1) : gender = Unit::Gender::FEMALE;
		     auto unitClass = (Unit::Class) Utils::Random(0, (int) Unit::Class::SIZE - 1);
		     auto alignment = (Unit::Alignment) Utils::Random(0, (int) Unit::Alignment::SIZE - 1);

		     //count the number of images in the assets folder and return a random number
		     uint8_t picNum = Files::Get_Random_Pic(pathToSpeciesImgs + Units::species[(int) species] + "/" + Units::gender[(int) gender][0] + "/");

		     //      std::vector<std::pair<std::string, std::string>> whereEquals = {{"race", Units::species[(int)species]}, {"type", Units::gender[(int)gender]}};
		     std::vector<std::pair<std::string, std::string>> whereEquals = {{"race", Units::species[(int) Unit::Species::ORC]},
		                                                                     {"type", Units::gender[(int) gender]}};
		     auto names = DB::Get_List("uID", "names", whereEquals);
		     uint16_t index = Utils::Random(0, (int) names.size() - 1);

		     Add_Unit(objects, level, location, position, stoi(names[index]), gender, species, unitClass, alignment, picNum);
		     return true;
	     }
     }

     std::string Random_Entities(Units::Objects &objects, int level, Component::Position location, const char entityType, int numEntities, int8_t x, int8_t y) {
	     std::string group;
	     auto tries = 10;
     reRoll:
	     if (tries == 0) {
		     return group;
	     }
	     for (auto i = 0; i < numEntities; ++i) {
		     group += entityType;
		     Component::Position position(x + i, y + i);
		     if (!Add_Object(objects, level, location, group, position)) {
			     tries--;
			     goto reRoll;
		     }
	     }
	     return group;
     }

     void Place_Entities_On_Map(std::vector<Chunk::Room> &rooms, int level, Component::Position location, Units::Objects &objects) {
	     auto placements = Spawn_Unit(rooms);
	     std::cout << "num placements: " << placements.size() << std::endl;

	     for (const auto &placement: placements) {
		     int numMonsters = Utils::Random(0, 3);
		     auto unitData = Random_Entities(objects, level, location, unitChars[(int) Unit::Species::GOBLIN], numMonsters, placement.x, placement.y);
//      objects.unitsString += unitData;
		     std::cout << "units added: " << unitData << std::endl;
	     }

	     std::cout << "init num entities: " << objects.units.size() << std::endl;
     }

     //we beed the chunk that the unit is being spawned in
     void Init(int level, Component::Position location, Chunk::Chunk chunk, std::vector<Chunk::Room> &rooms, Units::Objects &objects) {

	     if (objects.units.empty()) { //To save the 0 index for the player
		     Unit::Unit playerPlaceholder(level, location);
		     objects.units.emplace_back(playerPlaceholder);
	     }
	     Place_Entities_On_Map(rooms, level, location, objects);

	     for (auto &unit: objects.units) {
		     if (unit.stats.health > 0) {
			     Map::Set_Tile(chunk, unit.position.position.x, unit.position.position.y, unitChars[(int) unit.def.species]);
		     }
	     }
	     std::cout << "units inited" << std::endl;

     }
}