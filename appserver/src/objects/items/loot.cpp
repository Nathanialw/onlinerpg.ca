//
// Created by desktop on 10/12/24.
//
#include "loot.h"
#include "components.h"
#include "iostream"
#include "utils.h"
#include "items.h"
#include "db.h"

namespace Loot {

     void Generate_Loot(Items::Ground &items) {
	     uint8_t numItems = Utils::Random(1, 4);
	     for (auto &item: items) {
		     if (numItems == 0)
			     break;
		     if (item.Empty()) {
			     Items::ItemID itemID = Utils::Random(1, DB::Get_Num_Items());
			     item.Generate(itemID);
			     numItems--;
		     }
	     }
     }

     std::string Query_Loot(Items::Ground &items) {
	     std::string itemsStr;
	     int size = 0;
	     for (auto item: items) {
		     if (item.Empty())
			     break;
		     itemsStr += Utils::Prepend_Zero_By_Digits(item.Get_uID(), 3);
		     size++;
	     }

	     itemsStr = Utils::Prepend_Zero_By_Digits(size, 2) + itemsStr;
	     return itemsStr;
     }

     std::string Pick_Up_Item(Items::Ground &loot, Items::Inventory &inventory, const Items::Max_Slots &maxSlots, uint8_t index) {
	     auto item = loot[index];
	     int inventoryIndex = 999;

	     auto type = DB::Query("type", "items", "uID", std::to_string(item.Get_uID()));
	     auto bagIndex = stoi(DB::Query("slotNum", "equipSlots", "type", type));

	     //get the type of item items/scroll/potion
	     //put it in the preferred bag
	     //if bag is full, put it in the items bag
	     //if items bag is full, return "inventory full"

	     //search for first empty slot in inventory
	     for (int i = 0; i < maxSlots[bagIndex]; ++i) {
		     if (inventory[bagIndex][i].Empty()) {
			     inventoryIndex = i;
			     break;
		     }
	     }

	     if (bagIndex == 0 && 999 == inventoryIndex) {
		     bagIndex++;
		     for (int i = 0; i < maxSlots[bagIndex]; ++i) {
			     if (inventory[bagIndex][i].Empty()) {
				     inventoryIndex = i;
				     break;
			     }
		     }
	     }

	     if (999 == inventoryIndex) {
		     return " ";
	     }

	     // add item to inventory array
	     inventory[bagIndex][inventoryIndex] = item;
	     //remove from loot array and resize
	     for (int i = index; i < loot.size() - 1; ++i) {
		     loot[i] = loot[i + 1];
	     }
	     loot[loot.size() - 1].Set_Empty(); // Set the last element to 0

	     // return the index of the inventory slot to update and the index of the item in the db
	     std::string inventoryStr = Utils::Prepend_Zero_By_Digits(inventoryIndex, 2) + Utils::Prepend_Zero_By_Digits(item.Get_uID(), 3);
	     return inventoryStr;
     }
}