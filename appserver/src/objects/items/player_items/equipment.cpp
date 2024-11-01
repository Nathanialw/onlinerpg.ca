//
// Created by desktop on 10/13/24.
//

#include "equipment.h"
#include "string"
#include "array"
#include "iostream"
#include "items.h"
#include "utils.h"
#include "db.h"
#include "backpack.h"

namespace Equipment {

     void Swap_Item(Items::Inventory &inventory, Items::Equipped &equipment, const int8_t equipSlot, const int invSlot, uint8_t bag, std::vector<std::pair<uint8_t, uint8_t>> &updateItems, int8_t &updateEquipment) {
	     auto swapItemID = equipment[equipSlot];
	     equipment[equipSlot] = inventory[bag][invSlot];
	     std::cout << "equipment slot now contains itemID: " << equipment[equipSlot].Get_uID() << std::endl;
	     inventory[bag][invSlot] = swapItemID;
	     updateItems.emplace_back(bag, invSlot);
	     updateEquipment = equipSlot;
     }

     //set equipment slot index to itemID
     //clear inventory slot index
     void Unequip_Item(Items::Inventory &inventory, Items::Equipped &equipment, const uint8_t &slot, const Items::Max_Slots &maxSlots, std::vector<std::pair<uint8_t, uint8_t>> &updateItems, int8_t &updateEquipment) {
	     //swap equipment slot itemID with inventory itemID
	     auto swapItemID = equipment[slot];

	     for (int bag = 0; bag < (int) Items::BagType::Scrolls; ++bag) {
		     for (int i = 0; i < maxSlots[bag]; ++i) {
			     if (inventory[bag][i].Empty()) {
				     inventory[bag][i] = swapItemID;
				     equipment[slot].Set_Empty();
				     updateItems.emplace_back(bag, i);
				     updateEquipment = (int8_t) slot;
				     return;
			     }
		     }
	     }
	     std::cout << "no space in inventory" << std::endl;
     }

     int8_t Dual_Equip(Items::Equipped &equipment, int8_t slot0, int8_t slot1) {
	     if (equipment[slot0].Empty())
		     return slot0;
	     else if (equipment[slot1].Empty())
		     return slot1;
	     else
		     return slot0;
     }

     void Equip_Item(Items::Inventory &inventory, Items::Equipped &equipment, uint8_t index, const std::string &equipSlot, uint8_t bag, std::vector<std::pair<uint8_t, uint8_t>> &updateItems, int8_t &updateEquipment) {
	     int8_t slotNum = stoi(DB::Query("slotNum", "equipSlots", "slotName", equipSlot)); //retrieve slotNum using slotName from the db

	     std::cout << "equip slot num: " << slotNum << std::endl;

	     //if slotNum == Items::ItemSlot::mainHand, then it can fit in Items::ItemSlot::mainHand or Items::ItemSlot::offHand
	     if (slotNum == (int8_t) Items::ItemSlot::mainHand)
		     slotNum = Dual_Equip(equipment, (int8_t) Items::ItemSlot::mainHand, (int8_t) Items::ItemSlot::offHand);
	     else if (slotNum == (int8_t) Items::ItemSlot::ring0)
		     slotNum = Dual_Equip(equipment, (int8_t) Items::ItemSlot::ring0, (int8_t) Items::ItemSlot::ring1);

	     std::cout << "equip slot num: " << slotNum << std::endl;

	     Swap_Item(inventory, equipment, slotNum, index, bag, updateItems, updateEquipment);
     }

     void Equip_Second_Item(Items::Backpack &pack, Items::Ground &groundItems, Items::Equipped &equipment, uint8_t index, uint8_t bag, std::vector<std::pair<uint8_t, uint8_t>> &updateItems, int8_t &updateEquipment, int8_t &updateBag) {
	     auto item = pack.inventory[bag][index];
	     auto slotStr = DB::Query("equipSlot", "Items", "uID", std::to_string(item.Get_uID())); //retrieve equipSlot using itemID from the db
	     if (slotStr == "bag") {
		     Backpack::Equip_Bag(pack, groundItems, index, bag, Items::BagType::Items1, updateItems, updateBag);
		     return;
	     }

	     auto slotNum = stoi(DB::Query("slotNum", "equipSlots", "slotName", slotStr)); //retrieve slotNum using slotName from the db
	     if (slotNum == (int) Items::ItemSlot::mainHand || slotNum == (int) Items::ItemSlot::offHand) {
		     Swap_Item(pack.inventory, equipment, (int) Items::ItemSlot::offHand, index, bag, updateItems, updateEquipment);
		     return;
	     } else if (slotNum == (int) Items::ItemSlot::ring0 || slotNum == (int) Items::ItemSlot::ring1) {
		     Swap_Item(pack.inventory, equipment, (int) Items::ItemSlot::ring1, index, bag, updateItems, updateEquipment);
		     return;
	     }

	     Use_Item(pack, groundItems, equipment, index, bag, updateItems, updateEquipment, updateBag); //equip the item normally
     }

     std::pair<ItemID, ItemEffectUID> Use_Item(Items::Backpack &pack, Items::Ground &groundItems, Items::Equipped &equipment, uint8_t invSlot, uint8_t bag, std::vector<std::pair<uint8_t, uint8_t>> &updateItems, int8_t &updateEquipment, int8_t &updateBag) {
	     auto item = pack.inventory[bag][invSlot];
	     std::cout << "itemID: " << item.Get_uID() << std::endl;

	     auto slotStr = DB::Query("equipSlot", "Items", "uID", std::to_string(item.Get_uID())); //retrieve equipSlot using itemID from the db
	     std::cout << "equip slot: " << slotStr << std::endl;

	     if (slotStr == "consumable") {
		     std::pair<ItemID, ItemEffectUID> itemEffect = pack.inventory[bag][invSlot].Use();
		     updateItems.emplace_back(bag, invSlot);
		     return itemEffect;
	     }

	     if (slotStr == "notEquippable") {
		     return {0,0};
	     }

	     //if any of these send the client an update for the bags as well as the inv slot
	     if (slotStr == "bag") {
		     Backpack::Equip_Bag(pack, groundItems, invSlot, bag, Items::BagType::Items0, updateItems, updateBag);
		     return {0,0};
	     }

	     if (slotStr == "tome") {
		     Backpack::Equip_Bag(pack, groundItems, invSlot, bag, Items::BagType::Scrolls, updateItems, updateBag);
		     return {0,0};
	     }

	     if (slotStr == "belt") {
		     Backpack::Equip_Bag(pack, groundItems, invSlot, bag, Items::BagType::Potions, updateItems, updateBag);
		     return {0,0};
	     }

	     Equip_Item(pack.inventory, equipment, invSlot, slotStr, bag, updateItems, updateEquipment);
	     return {0,0};
     }

     std::string Get_Equipment(Items::Equipped &equipment) {
	     std::string equipmentStr = Utils::Prepend_Zero_By_Digits(equipment.size(), 2);
	     for (int i = 0; i < equipment.size(); ++i) {
		     equipmentStr += Utils::Prepend_Zero_By_Digits(i, 2) + equipment[i].As_Sendable_String();
	     }
	     return equipmentStr;
     }

     std::string Get_Equipment(Items::Equipped &equipment, int8_t &slot) {
	     if (slot != -1) {
		     std::string equipmentStr = "01";
		     equipmentStr += Utils::Prepend_Zero_By_Digits(slot, 2) + equipment[slot].As_Sendable_String();
		     slot = -1;
		     return equipmentStr;
	     } else
		     return "00";
     }
}
