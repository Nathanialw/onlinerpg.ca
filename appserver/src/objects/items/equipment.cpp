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

     void Swap_Item(Items::Inventory &inventory, Items::Equipped &equipment, const int equipSlot, const int invSlot, uint8_t bag) {
	     auto swapItemID = equipment[equipSlot];
	     equipment[equipSlot] = inventory[bag][invSlot];
	     std::cout << "equipment slot now contains itemID: " << equipment[equipSlot].Get_uID() << std::endl;
	     inventory[bag][invSlot] = swapItemID;
     }

     //set equipment slot index to itemID
     //clear inventory slot index
     void Unequip_Item(Items::Inventory &inventory, Items::Equipped &equipment, const std::string &slotNum, const Items::Max_Slots &maxSlots) {
	     //swap equipment slot itemID with inventory itemID
	     auto swapItemID = equipment[stoi(slotNum)];

	     for (int bag = 0; bag < (int) Items::BagType::Scrolls; ++bag) {
		     for (int i = 0; i < maxSlots[bag]; ++i) {
			     if (inventory[bag][i].Empty()) {
				     inventory[bag][i] = swapItemID;
				     equipment[stoi(slotNum)].Set_Empty();
				     return;
			     }
		     }
	     }
	     std::cout << "no space in inventory" << std::endl;
     }

     int Dual_Equip(Items::Equipped &equipment, int slot0, int slot1) {
	     if (equipment[slot0].Empty())
		     return slot0;
	     else if (equipment[slot1].Empty())
		     return slot1;
	     else
		     return slot0;
     }

     void Equip_Item(Items::Inventory &inventory, Items::Equipped &equipment, uint8_t index, const std::string &equipSlot, uint8_t bag) {
	     auto slotNum = stoi(DB::Query("slotNum", "equipSlots", "slotName", equipSlot)); //retrieve slotNum using slotName from the db

	     std::cout << "equip slot num: " << slotNum << std::endl;

	     //if slotNum == Items::ItemSlot::mainHand, then it can fit in Items::ItemSlot::mainHand or Items::ItemSlot::offHand
	     if (slotNum == (int) Items::ItemSlot::mainHand)
		     slotNum = Dual_Equip(equipment, (int) Items::ItemSlot::mainHand, (int) Items::ItemSlot::offHand);
	     else if (slotNum == (int) Items::ItemSlot::ring0)
		     slotNum = Dual_Equip(equipment, (int) Items::ItemSlot::ring0, (int) Items::ItemSlot::ring1);

	     std::cout << "equip slot num: " << slotNum << std::endl;

	     Swap_Item(inventory, equipment, slotNum, index, bag);
     }

     void Equip_Second_Item(Items::Backpack &pack, Items::Ground &groundItems, Items::Equipped &equipment, uint8_t index, uint8_t bag) {
	     auto item = pack.inventory[bag][index];
	     auto slotStr = DB::Query("equipSlot", "Items", "uID", std::to_string(item.Get_uID())); //retrieve equipSlot using itemID from the db
	     if (slotStr == "bag") {
		     Backpack::Equip_Bag(pack, groundItems, index, bag, Items::BagType::Items1);
		     return;
	     }

	     auto slotNum = stoi(DB::Query("slotNum", "equipSlots", "slotName", slotStr)); //retrieve slotNum using slotName from the db
	     if (slotNum == (int) Items::ItemSlot::mainHand || slotNum == (int) Items::ItemSlot::offHand) {
		     Swap_Item(pack.inventory, equipment, (int) Items::ItemSlot::offHand, index, bag);
		     return;
	     } else if (slotNum == (int) Items::ItemSlot::ring0 || slotNum == (int) Items::ItemSlot::ring1) {
		     Swap_Item(pack.inventory, equipment, (int) Items::ItemSlot::ring1, index, bag);
		     return;
	     }

	     Use_Item(pack, groundItems, equipment, index, bag); //equip the item normally
     }

     void Use_Item(Items::Backpack &pack, Items::Ground &groundItems, Items::Equipped &equipment, uint8_t invSlot, uint8_t bag) {
	     auto item = pack.inventory[bag][invSlot];
	     std::cout << "itemID: " << item.Get_uID() << std::endl;

	     auto slotStr = DB::Query("equipSlot", "Items", "uID", std::to_string(item.Get_uID())); //retrieve equipSlot using itemID from the db
	     std::cout << "equip slot: " << slotStr << std::endl;

	     if (slotStr == "notEquippable") {
		     // query the effect of the item and apply it
//      auto slotNum = DB::Query("slotNum", "equipSlots", "slotName", slot); //retrieve slotNum using slotName from the db
		     std::cout << "item not equippable" << std::endl;
		     return;
	     }

	     if (slotStr == "bag") {
		     Backpack::Equip_Bag(pack, groundItems, invSlot, bag, Items::BagType::Items0);
		     return;
	     }

	     if (slotStr == "tome") {
		     Backpack::Equip_Bag(pack, groundItems, invSlot, bag, Items::BagType::Scrolls);
		     return;
	     }

	     if (slotStr == "belt") {
		     Backpack::Equip_Bag(pack, groundItems, invSlot, bag, Items::BagType::Potions);
		     return;
	     }

	     Equip_Item(pack.inventory, equipment, invSlot, slotStr, bag);
     }

     std::string Get_Equipment(Items::Equipped &equipment) {
	     std::string equipmentStr = Utils::Prepend_Zero_By_Digits(equipment.size(), 2);
	     for (int i = 0; i < equipment.size(); ++i) {
		     equipmentStr += Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(equipment[i].Get_uID(), 3);
	     }
	     //first 2 chars is equip size
	     //each 5 of the next chars is equip slot and itemID
	     return equipmentStr;
     }
};
