#pragma once
//
// Created by desktop on 10/12/24.
//


#include "array"
#include "vector"
#include "iostream"
#include "string"
#include "utils.h"
#include "unordered_map"
#include "types.h"
#include "functional"

namespace Items {

     void Init_Item_Effects_Array(std::vector<std::string> &PotionIDs, std::vector<std::string> &effects);

     ItemEffectUID Get_Item_Effect(ItemID itemID);

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

     class Mod {
	public:
	uint8_t uID = 0;

	[[nodiscard]] bool Empty() const {
		if (uID == 0)
			return true;
		return false;
	}

	[[nodiscard]] std::string As_String() const {
		return std::to_string(uID);
	}

	void Set_Empty() { uID = 0; }

	bool operator==(const Mod &rhs) const { return uID == rhs.uID; }
     };

     class Item {
	private:
	static const uint8_t numModifiers = 8;

	ItemID uID{};                                                                                   // is this not jsut the icon basically?
	std::array<Mod, numModifiers> modifiers{};        // keys to the static modifiers in the db
	uint8_t rarity{};                                                                         // 0-5


	uint8_t durability{}; // 0-100


	public:
	// requirements
	explicit Item() {
		// passin the power level of item to create
		// get a random uID from the db of that level
		// roll for rarity
		// roll for modifers based on rarity
		// set the icon
		uID = 0; // 0-255 name of the icon png in the directory referenced in the db
		// set the durability
		durability = 255; // probably will be random later
		// set the rarity
//		rarity =  Utils::Random(0, 7);
		rarity = 0;
		// set the modifiers
		for (auto &modifier: modifiers) {
			modifier.Set_Empty();
		}
	}

	explicit Item(ItemID itemID) {
		// passin the power level of item to create
		// get a random uID from the db of that level
		// roll for rarity
		// roll for modifers based on rarity
		// set the icon
		uID = itemID; // 0-255 name of the icon png in the directory referenced in the db
		// set the durability
		durability = 255; // probably will be random later
		// set the rarity
//		rarity =  Utils::Random(0, 7);
		rarity = 0;

		for (auto &modifier: modifiers) {
			modifier.Set_Empty();
		}
	}

	//TODO: add a constructor that takes the level and the species of the unit and generates the item based on that
	void Generate(ItemID _uID) {
		// passin the power level of item to create
		// get a random uID from the db of that level
		// roll for rarity
		// roll for modifers based on rarity
		// set the icon
		uID = _uID; // 0-255 name of the icon png in the directory referenced in the db

		// set the durability
		durability = 255; // probably will be random later
		// set the rarity
		rarity = Utils::Random(0, 7);
		// set the modifiers

		//get a random number 1-8
		auto numMods = Utils::Random(1, 8);
		for (auto i = 0; i < numMods; ++i) {
			modifiers[i].uID = Utils::Random(1, 255);
		}
		for (int i = numMods; i < numModifiers; ++i) {
			modifiers[i].Set_Empty();
		}
		std::cout << "numMods: " << numMods << std::endl;
	}

	void Durability_Down(uint8_t damage) { durability -= damage; }

	void Durability_Up(uint8_t repair) { durability += repair; }

	[[nodiscard]] bool Empty() const { return !uID; }

	[[nodiscard]] ItemID Get_uID() const { return uID; }

	void Print() {
		std::cout << "Item: " << uID << " Rarity: " << rarity << " Durability: " << durability;
		for (const auto &mod: modifiers) {
			if (mod.Empty())
				break;
			std::cout << ", Modifier: " << mod.uID;
		}
		std::cout << std::endl;
	}

	std::string As_String(int a = 0) {
		std::string ss = "Item: " + std::to_string(uID) + " Rarity: " + std::to_string(rarity) + " Durability: " + std::to_string(durability);
		for (const auto &mod: modifiers) {
			if (mod.Empty())
				break;
			ss += ", Modifier: " + std::to_string(mod.uID);
		}
		return ss;
	}

	void Set(const ItemID &_uID = 0, const uint8_t &_rarity = 0, const uint8_t &_durability = 255, const std::array<Mod, numModifiers> &_modifier = {}) {
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

	[[nodiscard]] std::array<Mod, numModifiers> Get_Modifiers() const {
		return modifiers;
	}

	[[nodiscard]] std::string As_Sendable_String() const {
		std::string itemStr;
		itemStr += Utils::Prepend_Zero_By_Digits(uID, 3);
		itemStr += Utils::Prepend_Zero_By_Digits(rarity, 1);
		itemStr += Utils::Prepend_Zero_By_Digits(durability, 3);

		auto num = 0;
		std::string modsStr;

		for (const auto &mod: modifiers) {
			if (mod.Empty())
				break;
			modsStr += Utils::Prepend_Zero_By_Digits(mod.uID, 3);
			num++;
		}

		itemStr += Utils::Prepend_Zero_By_Digits(num, 1) + modsStr;
		std::cout << "item: " << itemStr << std::endl;
		return itemStr;
	}

	std::pair<ItemID, ItemEffectUID> Use() {
		auto effect = Get_Item_Effect(uID);
		std::pair<ItemID, ItemEffectUID> effectPair = {uID, effect};
		this->Set_Empty();
		return effectPair;
	}


	bool operator==(Item rhs) {
		return uID == rhs.uID &&
		       modifiers == rhs.modifiers &&
		       rarity == rhs.rarity &&
		       durability == rhs.durability;
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
     typedef std::array<Item, (int8_t) ItemSlot::SIZE> Equipped;

} // namespace Items

