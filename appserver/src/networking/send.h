//
// Created by desktop on 9/30/24.
//
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include "game.h"

#ifndef BROWSERRPG_SEND_H
#define BROWSERRPG_SEND_H

#endif // BROWSERRPG_SEND_H

namespace Send {

//  void Init(const websocketpp::connection_hdl& hdl, const std::basic_string<char>& msg, websocketpp::server<websocketpp::config::asio>& print_server);
  void On_Message(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::State &game);
}