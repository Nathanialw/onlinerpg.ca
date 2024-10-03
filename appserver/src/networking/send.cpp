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

  void Init(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::State &game) {
    auto player = game.Get_Player();
    std::string map = Map::Init(game.map[game.level][game.location].defaultChunk, game.map[game.level][game.location].chunk, game.map[game.level][game.location].rooms, game.seed);
    Pathing::Init(game.map[game.level][game.location].pathing, map);
    Player::Spawn(game, msg);
    Spawn::Init(game.map[game.level][game.location].chunk, game.map[game.level][game.location].rooms, game.objects); // msg->get_payload()
    print_server.send(hdl, Player::Get_Stats(game), websocketpp::frame::opcode::text);

    if (!game.objects.units.empty()) {
      print_server.send(hdl, Map::SendMapSegment(game, "q"), websocketpp::frame::opcode::text);
    }

    std::cout << "Ready!" << std::endl;
  }

  void Update(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::State &game) {
    // move player
    const char *direction = &msg[1];
    auto action = Update::Update_Units(game, direction);
    // send map
    print_server.send(hdl, Map::SendMapSegment(game, action), websocketpp::frame::opcode::text);

    std::string response = "0I hear you pressing: ";
    response.append(&msg[1]);
    print_server.send(hdl, response, websocketpp::frame::opcode::text);

    std::cout << "sending char stats back  to client" << std::endl;
    print_server.send(hdl, Player::Get_Stats(game), websocketpp::frame::opcode::text);
  }

  void On_Message(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::State &game) {
    // keep websocket alive
    std::string response;

    if (msg[0] == '1') { //"1" is the action turn, right now it only means move.
      Update(hdl, msg, print_server, game);
    }

    else if (msg[0] == '2') { //unused
      response = "0 response \"2\" is unused, message was: ";
      response.append(&msg[1]);
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }

    else if (msg[0] == '3') { // send map
      Init(hdl, msg, print_server, game);
    }

    else if (msg[0] == '4') {
      std::cout << "4" << msg << std::endl;
      print_server.send(hdl, Player::Get_Stats(game),
                        websocketpp::frame::opcode::text);
      std::cout << "char stats sent!" << std::endl;

      if (!game.objects.units.empty()) {
        print_server.send(hdl, Map::SendMapSegment(game, "1   0"), websocketpp::frame::opcode::text);
      }
    }

    else if (msg[0] == '5') {
      response.append(msg.substr(1, 4));
      response = "5" + Species::Get_Unit_Data_As_string(game, response);
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }

    else {
    }

    //[0] message type [1-2] ID (uint16_t stored as 2 chars) [3] message;
    // ie: 1a2w;
    if (!msg.empty()) {
    }
  }
}

