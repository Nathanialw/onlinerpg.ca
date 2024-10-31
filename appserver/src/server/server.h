#pragma  once
//
// Created by desktop on 10/30/24.
//

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
#include "game.h"

namespace Server {

     struct connection_hdl_hash {
	std::size_t operator()(const websocketpp::connection_hdl &hdl) const {
		return std::hash<std::uintptr_t>()(reinterpret_cast<std::uintptr_t>(hdl.lock().get()));
	}
     };

     struct connection_hdl_equal {
	bool operator()(const websocketpp::connection_hdl &hdl1, const websocketpp::connection_hdl &hdl2) const {
		return !hdl1.owner_before(hdl2) && !hdl2.owner_before(hdl1);
	}
     };

     typedef websocketpp::server<websocketpp::config::asio> server;
     typedef std::unordered_map<std::string, websocketpp::connection_hdl> Connections;
     typedef std::unordered_map<websocketpp::connection_hdl, Game::Instance *, connection_hdl_hash, connection_hdl_equal> Reverse_Connections;
     typedef std::unordered_map<std::string, Game::Instance> Games;


     struct Connection {
	websocketpp::connection_hdl hdl;
	websocketpp::server<websocketpp::config::asio> &print_server;
	const std::basic_string<char> &msg;
     };

     server &Print_Server();

     Connections &Client_Connections();

     Games &Game_Instances();

     Game::Instance &Hdl(const websocketpp::connection_hdl &hd);

     void Send(const websocketpp::connection_hdl &hdl, std::string &message);

     void Init_Connection(const websocketpp::connection_hdl &hdl);

     void Close_Connection(const websocketpp::connection_hdl &hdl);

     bool Enter_Game(const websocketpp::connection_hdl &hdl, int8_t gg);
};
















