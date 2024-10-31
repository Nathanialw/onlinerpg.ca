//
// Created by desktop on 10/30/24.
//

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

namespace Server {

     struct Connection {
	websocketpp::connection_hdl hdl;
          websocketpp::server<websocketpp::config::asio> &print_server;
          const std::basic_string<char> &msg;
     };



     void Send(const Connection &connection, std::string &message) {
	     connection.print_server.send(connection.hdl, message, websocketpp::frame::opcode::text);
     };
};


