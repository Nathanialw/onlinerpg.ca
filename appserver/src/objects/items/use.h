#pragma  once
//
// Created by desktop on 10/30/24.
//

#ifndef BROWSERRPG_USE_H
#define BROWSERRPG_USE_H

#endif //BROWSERRPG_USE_H

#include "unordered_map"

namespace Use {

     void Init();

     std::string Activate(Unit::Unit &unit, ItemEffectUID effectID);
}