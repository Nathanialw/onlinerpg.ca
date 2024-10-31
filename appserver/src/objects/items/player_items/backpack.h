//
// Created by desktop on 10/22/24.
//

#ifndef BROWSERRPG_BACKPACK_H
#define BROWSERRPG_BACKPACK_H

#endif // BROWSERRPG_BACKPACK_H

#include "items.h"
#include "vector"

namespace Backpack {

     void Equip_Bag(Items::Backpack &pack, Items::Ground &groundItems, uint8_t invSlot, uint8_t bag, Items::BagType bagSlot, std::vector<std::pair<uint8_t, uint8_t>> &updateItems, int8_t &updateBag);

     std::string Get_Bags(Items::Bags &bags);

     std::string Get_Bags(Items::Bags &bags, int8_t &slot);

     void Unequip_Bag(Items::Backpack &pack, uint8_t bagSlot);
}