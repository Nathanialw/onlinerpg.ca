#pragma once
//
// Created by desktop on 10/30/24.
//

#include "string"
#include "array"
#include "items.h"
#include "components.h"

namespace Unit {
     enum class Species : uint8_t {
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

     enum class Gender : uint8_t {
	MALE,
	FEMALE,
	SIZE,
     };

     enum class Class : uint8_t {
	FIGHTER,
	MYSTIC,
	SLAVE,
	SIZE,
     };

     enum class Alignment : uint8_t {
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

	[[nodiscard]] uint8_t SpeciesIDInt() const {
		return (uint8_t) (species) + 1;
	};

	[[nodiscard]] std::string SpeciesIDStr() const {
		return std::to_string((uint8_t) species + 1);
	};

	[[nodiscard]] uint8_t GenderIDInt() const {
		return (uint8_t) gender;
	}

	[[nodiscard]] std::string GenderIDStr() const {
		return std::to_string((uint8_t) gender);
	}

	[[nodiscard]] uint8_t ClassIDInt() const {
		return (uint8_t) unitClass;
	}

	[[nodiscard]] std::string ClassIDStr() const {
		return std::to_string((uint8_t) unitClass);
	}

	[[nodiscard]] uint8_t AlignmentIDInt() const {
		return (uint8_t) alignment;
	}

	[[nodiscard]] std::string AlignmentIDStr() const {
		return std::to_string((uint8_t) alignment);
	}
     };


     struct Base_Stats {
	uint8_t strength; // damage melee and ranged
	uint8_t intelligence; // magic
	uint8_t dexterity; // dual wielding/stealth
	uint8_t constitution; // health
	uint8_t authority; // leadership
	uint8_t charisma; // social interactions


	Base_Stats() {
		strength = 0;
		intelligence = 0;
		dexterity = 0;
		constitution = 0;
		authority = 0;
		charisma = 0;
	}

	explicit Base_Stats(Def def) {
		//query db for all of this based on def
		//then add random modifiers
		strength = 0;
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

	uint32_t XP = 0;
	uint8_t level = 1;

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

     class Traits {
	std::array<uint8_t, 17> traits{};

	public:
	Traits() {
		for (auto &trait: traits) {
			auto uID = Utils::Random(1, 255);
			trait = uID;
		}
	}

	void Set_Empty(uint8_t i) {
		traits[i] = 0;
		for (auto j = i; j < traits.size() - 1; ++j) {
			traits[j] = traits[j + 1];
		}
	}

	std::string As_Sendable_String() {
		std::string str;
		uint8_t numTraits = 0;
		for (const auto &trait: traits) {
			if (trait != 0) {
				numTraits++;
				str += Utils::Prepend_Zero_By_Digits(trait, 3);
			}
		}
		return Utils::Prepend_Zero_By_Digits(numTraits, 2) + str;
	}

	[[nodiscard]] uint8_t Get(uint8_t i) const {
		return traits[i];
	}

	void Set(uint8_t value) {
		for (auto &trait: traits) {
			if (trait == 0) {
				trait = value;
				return;
			}
		}
	}
     };

     class Unit {
	public:
	Items::Equipped equipment;
	Items::Backpack pack;
	Def def;
	Traits traits;
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


