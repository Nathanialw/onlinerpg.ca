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
#include "loot.h"
#include "inventory.h"
#include "equipment.h"

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
      std::string action = "d    10";
      // append inventory
      action.append(Inventory::Update_Inventory(game.Get_Player().inventory));
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
    action.append(Inventory::Update_Inventory(game.Get_Player().inventory));
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
//      response = "2";
      auto type = msg.substr(1, 1);
      auto mod = msg.substr(2, 1);
      auto index = msg.substr(3);
      std::cout << "panel clicked: " << type << std::endl;

      if (type == "0") {
        std::cout << "Looting item at index: " << index << std::endl;
        Loot::Pick_Up_Item(game.items[game.Get_Player().level][game.Get_Player().location][game.Get_Player().position], game.Get_Player().inventory, stoi(index));
      }
      else if (type == "1") {
        std::cout << "interacting with inventory at index: " << index << std::endl;
        if (mod == "c") { //throw away
          std::cout << "control clicked: " << mod << std::endl;
          Inventory::Drop_Item(game.Get_Player().inventory, game.items[game.Get_Player().level][game.Get_Player().location][game.Get_Player().position], stoi(index));
        }
        else if (mod == "a") { //equip offhand
          std::cout << "alt clicked: " << mod << std::endl;
          Equipment::Equip_Second_Item(game.Get_Player().inventory, game.Get_Player().equipment, stoi(index));
        }
        else if (mod == "s") { //
          std::cout << "shift clicked, thusfar unused" << std::endl;
        }
        else { //equip standard / use item
          std::cout << "unmodded clicked: " << mod << std::endl;
          auto item = Equipment::Use_Item(game.Get_Player().inventory, game.Get_Player().equipment, stoi(index));
          if (!item.empty()) {
            std::cout << "item not equippable, use item: " << item << std::endl;
          }
        }
      }
      else if (type == "2") {
        std::cout << "interacting with equipment at index: " << index << std::endl;
        Equipment::Unequip_Item(game.Get_Player().inventory, game.Get_Player().equipment, index);
      }

      std::string skip = "1 ";
      Update(hdl, skip, print_server, game);
    }

    else if (msg[0] == '3') { // send map
      Init(hdl, msg, print_server, game);
    }

    else if (msg[0] == '4') { // Reconnect
      print_server.send(hdl, msg, websocketpp::frame::opcode::text);
      response.append(msg.substr(1));
      Update(hdl, response, print_server, game);
    }

    else if (msg[0] == '5') { // query map object
      response.append(msg.substr(1, 4));
      response = "5" + Species::Get_Unit_Data_As_string(game, response);
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }

    else if (msg[0] == '6') { // restart game
      return 0;
    }

    else if (msg[0] == '7') { // close game
      return 1;
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

