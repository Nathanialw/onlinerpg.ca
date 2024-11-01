#pragma once
//
// Created by desktop on 10/30/24.
//

#include "string"
#include "array"
#include "items.h"
#include "components.h"

namespace Unit {
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

     enum class Gender {
	MALE,
	FEMALE,
	SIZE,
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

     struct Name {
	uint16_t firstName;
	uint16_t surname;
	uint16_t titlePrefix;
	uint16_t titleSuffix;
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

     struct Stats {
	uint16_t health = 0;
	uint16_t healthMax = 0;
	uint16_t mana = 100;
	uint16_t manaMax = 100;


	uint8_t minDamage = 0;
	uint8_t maxDamage = 0;
	uint8_t unitID = 0;
	uint8_t picNum = 1;

	uint8_t age = 0;

	uint8_t vision = 0;
	uint8_t speed = 0;
	uint8_t maxSpeed = 0;
	uint8_t AC = 0;

	//every unit can have one of these for unarmed combat
	uint8_t onHit = 0;
     };

     struct Position {
	//unit data to send
	Component::Position position{};
	Component::Position location{};
	int8_t level{};
     };


     class Unit {
	public:
	Items::Equipped equipment;
	Items::Backpack pack;
	Def def;

	Name name{};
	Position position;

	Base_Stats baseStats;
	Stats stats;

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
}


