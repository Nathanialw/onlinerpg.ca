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
#include "backpack.h"
#include "loot.h"
#include "use.h"

namespace Send {

     void Init(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::Instance &game) {
	     Use::Init();
	     int level = 0;
	     Component::Position location(0, 0);
	     Component::Position startPos(6, 6);
	     std::string map = Map::Init(game.Get_Map(level, location).defaultChunk, game.Get_Map(level, location).chunk, game.Get_Map(level, location).rooms, game.seed);
	     Pathing::Init(game.Get_Map(level, location).pathing, map);
	     Player::Spawn(game, level, location, startPos, msg);
	     Spawn::Init(level, location, game.Get_Map(level, location).chunk, game.Get_Map(level, location).rooms, game.Get_Objects(level, location)); // msg->get_payload()

	     if (!game.Get_Objects(level, location).units.empty()) {
		     Player::Update_Stats(game.Get_Player());
		     std::string action = "d____1";
		     action.append(Loot::Query_Loot(game.Get_Items()));
		     action.append(Backpack::Get_Bags(game.Get_Player().pack.bags));
		     action.append(Inventory::Get_Inventory(game.Get_Player().pack, game.Get_Player().pack.maxSlots));
		     action.append(Equipment::Get_Equipment(game.Get_Player().equipment));

		     auto response = Map::SendMapSegment(game, action) + Player::Get_Stats(game);
		     print_server.send(hdl, response, websocketpp::frame::opcode::text);
	     }

	     std::cout << "Ready!" << std::endl;
     }

     std::string stats;
     std::string prevStats;

     void Update(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::Instance &game) {
	     Player::Update_Stats(game.Get_Player(), game.updateEquipment);
	     auto action = Update::Update_Units(game, &msg[1]);
	     if (action[0] == 'm') {
		     auto move = Update::Move_Direction(game, &msg[1]);
		     Component::Position targetPosition = game.Get_Player().position.position.Add(move);
		     auto response = "5" + Species::Get_Unit_Data_As_string(game, targetPosition);
		     print_server.send(hdl, response, websocketpp::frame::opcode::text);
	     }
	     action.append(Loot::Query_Loot(game.Get_Items()));
	     action.append(Backpack::Get_Bags(game.Get_Player().pack.bags, game.updateBag));
	     action.append(Inventory::Get_Inventory(game.Get_Player().pack, game.updateInventory));
	     action.append(Equipment::Get_Equipment(game.Get_Player().equipment, game.updateEquipment));
	     auto response = Map::SendMapSegment(game, action);

	     //only send stats if they have changed
	     stats = Player::Get_Stats(game);
	     std::cout << "stats           : " << stats << std::endl;
	     std::cout << "prevStats: " << prevStats << std::endl;
	     if (prevStats != stats)
		     response.append(Player::Get_Stats(game));
	     prevStats = stats;

	     print_server.send(hdl, response, websocketpp::frame::opcode::text);
     }

     void Full_Update(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::Instance &game) {
	     Player::Update_Stats(game.Get_Player());
	     auto action = Update::Update_Units(game, &msg[1]);

	     action.append(Loot::Query_Loot(game.Get_Items()));
	     action.append(Backpack::Get_Bags(game.Get_Player().pack.bags));
	     action.append(Inventory::Get_Inventory(game.Get_Player().pack, game.Get_Player().pack.maxSlots));
	     action.append(Equipment::Get_Equipment(game.Get_Player().equipment));

	     auto response = Map::SendMapSegment(game, action) + Player::Get_Stats(game);
	     print_server.send(hdl, response, websocketpp::frame::opcode::text);
     }

     int8_t On_Message(const websocketpp::connection_hdl &hdl, const std::basic_string<char> &msg, websocketpp::server<websocketpp::config::asio> &print_server, Game::Instance &game) {
	     std::string response;

	     //TODO: function pointer hashmap
	     if (msg[0] == '1') { // Update
		     Update(hdl, msg, print_server, game);
	     } else if (msg[0] == '2') {  // loot item
		     auto itemEffect = Update_Items::Update(msg, game);
		     Use::Update_Known_Usable_Effects(game.knownUsables, game.Get_Player(), hdl, print_server, itemEffect);
		     std::string skip = "1_";
		     Update(hdl, skip, print_server, game);
	     } else if (msg[0] == '3') { // New Game
		     return 4;
	     } else if (msg[0] == '4') { // Reconnect
		     print_server.send(hdl, msg, websocketpp::frame::opcode::text);
		     response.append(msg.substr(1));
		     Full_Update(hdl, response, print_server, game);
	     } else if (msg[0] == '5') { // send unit stats
		     response.append(msg.substr(1, 4));
		     response = "5" + Species::Get_Unit_Data_As_string(game, response);
		     print_server.send(hdl, response, websocketpp::frame::opcode::text);
	     } else if (msg[0] == '6') { // restart game
		     std::cout << "restart game" << std::endl;
		     return 0;
	     } else if (msg[0] == '7') { // close game
		     std::cout << "close game" << std::endl;
		     return 1;
	     } else if (msg[0] == '8') { // create resume button
		     std::cout << "resume button" << std::endl;
		     return 2;
	     } else if (msg[0] == '9') { // resume game
		     std::cout << "resume game" << std::endl;
		     return 3;
	     } else {
		     //
	     }

	     if (!msg.empty()) {
	     }
	     return -1;
     }
}

