//
// Created by desktop on 9/30/24.
//
#include "string"
#include "iostream"
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include "send.h"
#include "map.h"
#include "pathing.h"
#include "spawn.h"
#include "update.h"
#include "goblin.h"
#include "game.h"
#include "player.h"
#include "equipment.h"
#include "update_items.h"

namespace Send {

  void Init(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::Instance &game) {
    int level = 0;
    Component::Position location(0,0);
    Component::Position startPos(6,6);

    std::string map = Map::Init(game.Get_Map(level, location).defaultChunk, game.Get_Map(level, location).chunk, game.Get_Map(level, location).rooms, game.seed);
    Pathing::Init(game.Get_Map(level, location).pathing, map);
    Player::Spawn(game, level, location, startPos, msg);
    Spawn::Init(level, location, game.Get_Map(level, location).chunk, game.Get_Map(level, location).rooms, game.Get_Objects(level, location)); // msg->get_payload()
    print_server.send(hdl, Player::Get_Stats(game), websocketpp::frame::opcode::text);

    if (!game.Get_Objects(level, location).units.empty()) {
      std::string action = "d    10";
      // append inventory
      action.append(Inventory::Update_Inventory(game.Get_Player().pack, game.Get_Player().pack.maxSlots));
      // append equipment
      action.append(Equipment::Get_Equipment(game.Get_Player().equipment));
      print_server.send(hdl, Map::SendMapSegment(game, action), websocketpp::frame::opcode::text);
    }

    std::cout << "Ready!" << std::endl;
  }


  void Update(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::Instance &game) {
    //  update units
    auto action = Update::Update_Units(game, &msg[1]);
    //  send stats
    print_server.send(hdl, Player::Get_Stats(game), websocketpp::frame::opcode::text);
    // append inventory
    action.append(Inventory::Update_Inventory(game.Get_Player().pack, game.Get_Player().pack.maxSlots));
    // append equipment
    action.append(Equipment::Get_Equipment(game.Get_Player().equipment));
    // send map
    print_server.send(hdl, Map::SendMapSegment(game, action), websocketpp::frame::opcode::text);
  }

  int On_Message(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::Instance &game) {
    // keep websocket alive
    std::string response;

    if (msg[0] == '1') { // Update
      Update(hdl, msg, print_server, game);
    }

    else if (msg[0] == '2') {  // loot item
      Update_Items::Update(msg, game);
      std::string skip = "1 ";
      Update(hdl, skip, print_server, game);
    }

    else if (msg[0] == '3') { // Initials player
      return 4;
    }

    else if (msg[0] == '4') { // Reconnect
      print_server.send(hdl, msg, websocketpp::frame::opcode::text);
      response.append(msg.substr(1));
      Update(hdl, response, print_server, game);
    }

    else if (msg[0] == '5') { // send unit stats
      response.append(msg.substr(1, 4));
      response = "5" + Species::Get_Unit_Data_As_string(game, response);
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }

    else if (msg[0] == '6') { // restart game
      std::cout << "restart game" << std::endl;
      return 0;
    }

    else if (msg[0] == '7') { // close game
      std::cout << "close game" << std::endl;
      return 1;
    }

    else if (msg[0] == '8') { // create resume button
      std::cout << "resume button" << std::endl;
      return 2;
    }

    else if (msg[0] == '9') { // resume game
      std::cout << "resume game" << std::endl;
      return 3;
    }

    else {
      //
    }

    //[0] message type [1-2] ID (uint16_t stored as 2 chars) [3] message;
    // ie: 1a2w;
    if (!msg.empty()) {
    }
    return -1;
  }
}

