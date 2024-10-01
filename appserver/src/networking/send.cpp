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

namespace Send {

  void Init(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server) {
    std::string map = Map::Init();
    std::cout << "map inited" << std::endl;
    Pathing::Init(map);
    std::cout << "path inited" << std::endl;
    Spawn::Init(msg); // msg->get_payload()
    std::cout << "units inited" << std::endl;
    print_server.send(hdl, Units::GetCharStats(),
                      websocketpp::frame::opcode::text);
    std::cout << "char stats sent!" << std::endl;

    if (!Units::Get_Units()->empty()) {
      print_server.send(hdl, Map::SendMapSegment(Units::Get_Player(), "q"),
                        websocketpp::frame::opcode::text);
      std::cout << "map sent!" << std::endl;
    }

    std::cout << "Ready!" << std::endl;
  }

  void Update(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::State &game) {
    std::string response;
    // move player
    const char *direction = &msg[1];
    auto action = Update::Update_Units(game, direction);
    // send map
    print_server.send(hdl, Map::SendMapSegment(Units::Get_Player(), action),
                      websocketpp::frame::opcode::text);

    response = "0I hear you pressing: ";
    response.append(&msg[1]);
    print_server.send(hdl, response, websocketpp::frame::opcode::text);

    std::cout << "sending char stats back  to client" << std::endl;
    print_server.send(hdl, Units::GetCharStats(),
                      websocketpp::frame::opcode::text);
  }

  void On_Message(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::State &game) {
    // I will need to send this somewhere to get parsed and decide what the response should be
    //     std::cout << "on_message called with hdl: " << hdl.lock().get() << " and message: " << msg->get_payload() << std::endl;
    // keep websocket alive
    std::string response;

    if (msg[0] == '1') { //"1" is the action turn, right now it only means move.
      std::cout << "1" << msg << std::endl;
      Update(hdl, msg, print_server, game);
    }

    else if (msg[0] == '2') {
      std::cout << "2" << msg << std::endl;
      // unused
      response = "0 response \"2\" is unused, message was: ";
      response.append(&msg[1]);
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }

    else if (msg[0] == '3') {
      std::cout << "3" << msg << std::endl;
      // send map
      Init(hdl, msg, print_server);
    }

    else if (msg[0] == '4') {
      std::cout << "4" << msg << std::endl;
      print_server.send(hdl, Units::GetCharStats(),
                        websocketpp::frame::opcode::text);
      std::cout << "char stats sent!" << std::endl;

      if (!Units::Get_Units()->empty()) {
        print_server.send(hdl, Map::SendMapSegment(Units::Get_Player(), "1   0"),
                          websocketpp::frame::opcode::text);
      }
      std::cout << "Ready!" << std::endl;
    }

    else if (msg[0] == '5') {
      std::cout << "5" << msg << std::endl;
      response.append(msg.substr(1, 4));
      response = "5" + Species::Get_Unit_Data_As_string(response);
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }

    else {
      //            response = "0pinging";
      //            print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }

    //[0] message type [1-2] ID (uint16_t stored as 2 chars) [3] message;
    // ie: 1a2w;
    if (!msg.empty()) {
    }
  }
}

