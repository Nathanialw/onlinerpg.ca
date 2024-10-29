#pragma once
//
// Created by desktop on 10/12/24.
//

#ifndef BROWSERRPG_ITEMS_H
#define BROWSERRPG_ITEMS_H

#include "array"
#include "iostream"
#include "string"
#include "utils.h"


namespace Items {
     enum class BagType {
	Items0,
	Items1,
	Scrolls,
	Potions,
	SIZE,
     };

     enum class ItemSlot {
	Helmet,
	amulet,
	cloak,
	chest,
	belt,
	gloves,
	leggings,
	boots,
	ring0,
	ring1,
	mainHand,
	offHand,
	twoHanded,
	ammo,
	SIZE,
     };

     typedef uint16_t ItemID;

     class Mod {
	public:
	uint8_t uID = 0;

	[[nodiscard]] bool Empty() const {
		if (uID == 0)
			return true;
		return false;
	}

	void Set_Empty() { uID = 0; }

	bool operator==(const Mod &rhs) const { return uID == rhs.uID; }
     };

     class Item {
	private:
	static const uint8_t numModifiers = 8;


	ItemID uID;                                                                                   // is this not jsut the icon basically?
	uint8_t durability{};                                                                // 0-100
	std::array<Mod, numModifiers> modifiers{};        // keys to the static modifiers in the db
	uint8_t rarity{};                                                                         // 0-5

	// requirements
	public:
	explicit Item(uint8_t powerLevel = 0) {
		// passin the power level of item to create
		// get a random uID from the db of that level
		// roll for rarity
		// roll for modifers based on rarity
		// set the icon
		uID = 0; // 0-255 name of the icon png in the directory referenced in the db
		// set the durability
		durability = 100; // probably will be random later
		// set the rarity
		rarity = 0; // 0-5
		// set the modifiers
		for (auto &modifier: modifiers) {
			modifier.Set_Empty();
		}
	}

	void Durability_Down(uint8_t damage) { durability -= damage; }

	void Durability_Up(uint8_t repair) { durability += repair; }

	[[nodiscard]] bool Empty() const { return !uID; }

	[[nodiscard]] uint8_t Get_uID() const { return uID; }

	void Print() {
		std::cout << "Item: " << uID << " Rarity: " << rarity << " Durability: " << durability;
		for (const auto &mod: modifiers) {
			if (mod.Empty())
				break;
			std::cout << ", Modifier: " << mod.uID;
		}
		std::cout << std::endl;
	}

	void Set(uint8_t _uID = 0, uint8_t _rarity = 0, uint8_t _durability = 100, std::array<Mod, numModifiers> _modifier = {}) {
		uID = _uID;
		rarity = _rarity;
		durability = _durability;
		modifiers = _modifier;
	}

	void Set(const Item &item) {
		uID = item.uID;
		rarity = item.rarity;
		durability = item.durability;
		modifiers = item.modifiers;
	}

	void Set_Empty() {
		uID = 0; // 0-255 name of the icon png in the directory referenced in the db
		rarity = 0;     // 0-5
		durability = 0; // 0-100
		for (auto &modifier: modifiers) {
			modifier.Set_Empty();
		}
	}

	[[nodiscard]] std::string As_Sendable_String() const {
		std::string itemStr;
		itemStr += Utils::Prepend_Zero_By_Digits(uID, 3);
		itemStr += Utils::Prepend_Zero_By_Digits(rarity, 1);
		itemStr += Utils::Prepend_Zero_By_Digits(durability, 3);

		auto num = 0;
		std::string modsStr;

		for (auto &mod: modifiers) {
			if (Empty())
				break;
			modsStr += Utils::Prepend_Zero_By_Digits(mod.uID, 3);
			num++;
		}

		itemStr += Utils::Prepend_Zero_By_Digits(num, 1) + modsStr;
		std::cout << "item: " << itemStr << std::endl;
		return itemStr;
	}

	bool operator==(const Item &rhs) const {
		return uID == rhs.uID && modifiers == rhs.modifiers &&
		       rarity == rhs.rarity && durability == rhs.durability;
	}
     };

     typedef std::array<Item, (uint8_t) BagType::SIZE> Bags;
     typedef std::array<uint8_t, (uint8_t) BagType::SIZE> Max_Slots;
     typedef std::array<std::array<Item, 12>, (uint8_t) BagType::SIZE> Inventory;

     struct Backpack {
	Inventory inventory;
	Bags bags;
	Max_Slots maxSlots{};

	uint16_t copper = 0;
	uint16_t silver = 0;
	uint16_t gold = 0;

	//get bag uID at index as a string
	[[nodiscard]] std::string Sendable_BagID(uint8_t index) const {
		return Utils::Prepend_Zero_By_Digits(bags[index].Get_uID(), 3);
	}
     };

     typedef std::array<Item, 14> Ground;
     typedef std::array<Item, (uint8_t) ItemSlot::SIZE> Equipped;
} // namespace Items

#endif // BROWSERRPG_ITEMS_H
