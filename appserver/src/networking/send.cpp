//
// Created by desktop on 9/30/24.
//
#include "string"
#include "iostream"
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include "map.h"
#include "pathing.h"
#include "spawn.h"
#include "update.h"
#include "goblin.h"
#include "game.h"
#include "player.h"

namespace Send {

  void Init(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::Instance &game) {
    int level = 0;
    Component::Position location = {0, 0};
    int x = 6;
    int y = 6;

    std::string map = Map::Init(game.map[level][location].defaultChunk, game.map[level][location].chunk, game.map[level][location].rooms, game.seed);
    Pathing::Init(game.map[level][location].pathing, map);
    Player::Spawn(game, level, location, x, y, msg);
    Spawn::Init(level, location, game.map[level][location].chunk, game.map[level][location].rooms, game.objects[level][location]); // msg->get_payload()
    print_server.send(hdl, Player::Get_Stats(game), websocketpp::frame::opcode::text);

    if (!game.objects[level][location].units.empty()) {
      print_server.send(hdl, Map::SendMapSegment(game, "q"), websocketpp::frame::opcode::text);
    }

    std::cout << "Ready!" << std::endl;
  }

  void Update(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::Instance &game) {
    // move player
    std::cout << "sending char stats back  to client" << std::endl;
    print_server.send(hdl, Player::Get_Stats(game), websocketpp::frame::opcode::text);

    const char *direction = &msg[1];
    auto action = Update::Update_Units(game, direction);
    // send map
    print_server.send(hdl, Map::SendMapSegment(game, action), websocketpp::frame::opcode::text);
  }

  void On_Message(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::Instance &game) {
    // keep websocket alive
    std::string response;

    if (msg[0] == '1') { // Update
      Update(hdl, msg, print_server, game);
    }

    else if (msg[0] == '2') { //unused
      //
    }

    else if (msg[0] == '3') { // send map
      Init(hdl, msg, print_server, game);
    }

    else if (msg[0] == '4') { // Reconnect
      response = "4";
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
      Update(hdl, msg, print_server, game);
    }

    else if (msg[0] == '5') { // click event
      response.append(msg.substr(1, 4));
      response = "5" + Species::Get_Unit_Data_As_string(game, response);
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }

    else if (msg[0] == '6') {
      //
    }

    else {
      //
    }

    //[0] message type [1-2] ID (uint16_t stored as 2 chars) [3] message;
    // ie: 1a2w;
    if (!msg.empty()) {
    }
  }
}

