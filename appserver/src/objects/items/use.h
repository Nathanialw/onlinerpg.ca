#pragma  once
//
// Created by desktop on 10/30/24.
//

#include "unordered_map"

namespace Use {

     void Init();

     void Update_Known_Usable_Effects(std::unordered_map<ItemID, ItemEffectUID> &knownUsables, Unit::Unit &unit, const websocketpp::connection_hdl &hdl, websocketpp::server<websocketpp::config::asio> &print_server, const std::pair<ItemID, ItemEffectUID> &itemEffect);
}