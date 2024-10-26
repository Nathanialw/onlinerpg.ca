//
// Created by desktop on 10/13/24.
//

#include "inventory.h"
#include "string"
#include "array"
#include "iostream"
#include "items.h"
#include "utils.h"

namespace Inventory {


  void Drop_Item(Items::Inventory &inventory, Items::Ground &groundItems, uint8_t bag, uint8_t index) {
    auto item = inventory[bag][index];
    for (auto & groundItem : groundItems) {
      if (groundItem.Empty()) {
        groundItem = item;
        inventory[bag][index].Set_Empty();
        return;
      }
    }
    std::cout << "item dropped: " << item.uID << std::endl;
  }

  std::string Update_Inventory(const Items::Backpack &backpack, const Items::Max_Slots &maxSlots) {
    std::cout << "inventory updated" << std::endl;
    std::string inventoryStr;

    //each itme needs
    //  the uID of the icon,  3
    //  the rarity,           1
    //  the durability,       3
    //  the modifiers         num +  3*num



    for (int j = 0; j < (int)Items::BagType::SIZE; ++j) {
      std::string bagStr;

      for (int i = 0; i < maxSlots[j]; ++i) {
        auto uID = backpack.inventory[j][i].uID;
        auto rarity = backpack.inventory[j][i].rarity;
        auto durability = backpack.inventory[j][i].durability;
        auto num = 0;
        std::string modStr;
        for (auto modifier : backpack.inventory[j][i].modifiers) {
          if (modifier.Empty())
            break;
          num++;
          modStr += Utils::Prepend_Zero_By_Digits(modifier.uID, 3);
        }
        std::string newBagStr = Utils::Prepend_Zero_By_Digits(uID, 3) + Utils::Prepend_Zero_By_Digits(rarity, 1) + Utils::Prepend_Zero_By_Digits(durability, 3) +  Utils::Prepend_Zero_By_Digits(num, 1) + modStr;
        std::cout << "item updated string: " << newBagStr << std::endl;

        bagStr += Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(backpack.inventory[j][i].uID, 3);
      }

      inventoryStr += Utils::Prepend_Zero_By_Digits(backpack.bags[j].uID, 3) + bagStr;
      std::cout << "bag updated " << j << ": " <<  Utils::Prepend_Zero_By_Digits(backpack.bags[j].uID, 3) + bagStr << std::endl;
    }
    return inventoryStr;
  }

  std::string Get_Inventory(Items::Inventory &inventory) {
    auto items = inventory[(int)Items::BagType::Items0];
    std::string itemsStr = Utils::Prepend_Zero_By_Digits(items.size(), 2);

    for (int i = 0; i < items.size(); ++i) {
      itemsStr +=  Utils::Prepend_Zero_By_Digits(i, 2) + Utils::Prepend_Zero_By_Digits(items[i].uID, 3);
    }

    std::cout << "inventories sent: " << itemsStr << std::endl;
    return itemsStr;
  }

};









































































































































































































































































































































































































































































































