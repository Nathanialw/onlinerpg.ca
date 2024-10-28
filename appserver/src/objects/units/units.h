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

namespace Units {

     enum class Species {
	ALP,
	BASILISK,
	CENTAUR,
	DWARF,
	ELF,
	FOX,
	GOBLIN,
	HUMAN,
	IGUANA,
	JACKAL,
	KOBOLD,
	LAMIA,
	MINOTAUR,
	NYMPH,
	ORC,
	PIXIE,
	QAT,
	RAT,
	SKELETON,
	TREANT,
	UNICORN,
	VALKYRIE,
	WARG,
	XANA,
	YALE,
	ZOMBIE,

	ANGEL,
	BYAKHEE,
	CHIMERA,
	DRAGON,
	EBON,
	FAIRY,
	GOLEM,
	HARPY,
	IMP,
	JINN,
	KRAMPUS,
	LICH,
	MEDUSA,
	NAGA,
	OGRE,
	POLTERGEIST,
	QUINOTAUR,
	ROC,
	SATYR,
	TROLL,
	URIAS,
	VAMPIRE,
	WITCH,
	XANTHUS, //man-eating horse
	YETI,
	Ziburinis, //lithuanian glowing skeleton

//    EMPTY,

	SIZE
     };

     static std::string species[(uint8_t) Species::SIZE] = {
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

     enum class Gender {
	MALE,
	FEMALE,
	SIZE,
     };

     static std::string gender[(uint8_t) Gender::SIZE] = {
	"male",
	"female"
     };

     enum class Class {
	FIGHTER,
	MYSTIC,
	SLAVE,
	SIZE,
     };

     enum class Alignment {
	GOOD,
	NEUTRAL,
	EVIL,
	SIZE,
     };

     struct Def {
	Species species = Species::GOBLIN;
	Gender gender = Gender::MALE;
	Class unitClass = Class::FIGHTER;
	Alignment alignment = Alignment::NEUTRAL;
     };

     struct Base_Stats {
	uint8_t srength; // damage melee and ranged
	uint8_t intelligence; // magic
	uint8_t dexterity; // dual wielding
	uint8_t constitution; // health
	uint8_t authority; // leadership
	uint8_t charisma; // social interactions


	Base_Stats() {
		srength = 0;
		intelligence = 0;
		dexterity = 0;
		constitution = 0;
		authority = 0;
		charisma = 0;
	}

	explicit Base_Stats(Def def) {
		//query db for all of this based on def
		//then add random modifiers
		srength = 0;
		intelligence = 0;
		dexterity = 0;
		constitution = 0;
		authority = 0;
		charisma = 0;
	}
     };

     struct Name {
	uint16_t firstName;
	uint16_t surname;
	uint16_t titlePrefix;
	uint16_t titleSuffix;
     };

     struct Stats {
	uint16_t health = 0;
	uint16_t healthMax = 0;

	uint8_t minDamage = 0;
	uint8_t maxDamage = 0;
	uint8_t unitID = 0;
	uint8_t picNum = 1;

	uint8_t age = 0;

	uint8_t vision = 0;
	uint8_t speed = 0;
	uint8_t maxSpeed = 0;
	uint8_t AC = 0;

	uint8_t onHit = 0;
     };

     struct Position {
	//unit data to send
	Component::Position position{};
	Component::Position location{};
	int8_t level{};
     };

     struct Unit {
	Items::Equipped equipment;
	Items::Backpack pack;
	Def def;

	Name name{};
	Position position;

	Base_Stats baseStats;
	Stats stats;

	//    bool dead = false;


	//every unit can have one of these for unarmed combat


	//items are just an ID that is in the db
	//db contains the damage, AC, icon path, description, etc
//    Items::Bags bags{}; //items
//    Items::Max_Slots maxSlots{}; //items



	//constructor
	Unit(int8_t iLevel, Component::Position sLocation) {
		position.level = iLevel;
		position.location = sLocation;

		baseStats = Base_Stats(def);

		//starting bags,
		pack.maxSlots[0] = 4;
		pack.bags[0].Set(37);

		pack.maxSlots[1] = 4;
		pack.bags[1].Set(37);

		pack.maxSlots[2] = 2;
		pack.bags[2].Set(75);

		pack.maxSlots[3] = 2;
		pack.bags[3].Set(32);
	}
     };





//  struct Map_Position {
//    Component::Position chunk;
//    Component::Position position;
//  };

     struct Objects {
	std::vector<Unit> units;
	std::unordered_map<Component::Position, uint8_t> unitPositions;
	std::vector<uint8_t> emptyUnitSlots;
     };

     int Get_Unit_Index(std::unordered_map<Component::Position, uint8_t> &unitPositions, Component::Position position);

     void Update_Unit_Position(std::unordered_map<Component::Position, uint8_t> &unitPositions, const Component::Position &position, const Component::Position &newPosition);

     void Remove_Unit(std::unordered_map<Component::Position, uint8_t> &unitPositions, std::vector<uint8_t> &emptyUnitSlots, Component::Position position);

//  Unit& Get_Unit_At_Position(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, int> &unitPositions, Component::Position &newPosition);
     Unit &Get_Unit_At_Position(std::vector<Units::Unit> &units, std::unordered_map<Component::Position, uint8_t> &unitPositions, Component::Position &position);

     void Update_UnitsString(std::string &unitsString, int x, int y);

}

