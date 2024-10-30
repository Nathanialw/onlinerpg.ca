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

     void Update_Known_Usable_Effects(Unit::Unit &unit, std::unordered_map<ItemID, ItemEffectUID> &knownUsables, const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server,  const ItemEffectUID &itemEffect) ;
}