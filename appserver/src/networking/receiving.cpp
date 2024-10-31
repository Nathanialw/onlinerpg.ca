#include "string"

#include "server.hpp"
#include "receiving.h"

#include "send.h"
#include "server.h"


namespace Network {


     // This function will be called when a new connection is opened.
     // You can put your code here to handle the new connection.
     void On_Open(const websocketpp::connection_hdl &hdl) {
	     Server::Init_Connection(hdl);
     }

     //TODO: fix the bug where the client is repeatedly reconnecting when idling on a different tab
     void On_close(const websocketpp::connection_hdl &hdl) {
	     Server::Close_Connection(hdl);
     }

     void On_fail(const websocketpp::connection_hdl &hdl) {

     }

     bool On_ping(const websocketpp::connection_hdl &hdl, const std::string &payload) {
	     std::string response = "pinging: ";
	     Server::Send(hdl, response);
	     return true;
     }

     void On_pong(const websocketpp::connection_hdl &hdl, const std::string &payload) {
	     std::string response = "ping received: ";
	     Server::Send(hdl, response);
     }

     void On_pong_timeout(const websocketpp::connection_hdl &hdl, const std::string &payload) {

     }

     void On_interrupt(const websocketpp::connection_hdl &hdl) {

     }

     void On_http(const websocketpp::connection_hdl &hdl) {

     }

     bool On_validate(const websocketpp::connection_hdl &hdl) {
	     return true;
     }

     void On_Message(const websocketpp::connection_hdl &hdl, const Server::server::message_ptr &msg) {
	     int8_t code = Send::On_Message(hdl, msg->get_payload(), Server::Print_Server(), Server::Hdl(hdl));
	     if (Server::Enter_Game(hdl, code))
	          Send::Init(hdl, msg->get_payload(), Server::Print_Server(), Server::Hdl(hdl));

	     //when a player moves, send the new position to all the clients except the one that sent it right away

	     //every entity needs to be saved as a uID
	     //each client will need to know which entity is the player that moved
	     //so every client needs a map of uID to entity
	     //ill need to send the uID and the position and let the client update the position



	     //I think send the full update every 2 seconds
     }


     void Init() {
	     Server::Print_Server().set_close_handler(On_close);
	     Server::Print_Server().set_fail_handler(On_fail);
	     Server::Print_Server().set_ping_handler(On_ping);
	     Server::Print_Server().set_pong_handler(On_pong);
	     Server::Print_Server().set_pong_timeout_handler(On_pong_timeout);
	     Server::Print_Server().set_interrupt_handler(On_interrupt);
	     Server::Print_Server().set_http_handler(On_http);
	     Server::Print_Server().set_validate_handler(On_validate);
	     Server::Print_Server().set_open_handler(&On_Open);
	     Server::Print_Server().set_message_handler(&On_Message);

	     Server::Print_Server().init_asio();
	     Server::Print_Server().listen(9002);
	     Server::Print_Server().start_accept();
     }

     void Run() {
	     Init();
	     Server::Print_Server().run();
     }
}
