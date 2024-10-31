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

     void On_close(const websocketpp::connection_hdl &hdl) {
	     std::string session_id = Server::Get_SessionID(hdl);

	     if (session_id.empty()) {
		     Server::Print_Server().close(hdl, websocketpp::close::status::policy_violation, "Session ID is required.");
		     return;
	     }
//	     reverse_client_connections.erase(hdl);
	     std::cout << "Connection Closed: " << hdl.lock().get() << std::endl;
     }

     void On_fail(const websocketpp::connection_hdl &hdl) {

     }

     bool On_ping(const websocketpp::connection_hdl &hdl, const std::string &payload) {
	     std::string response = "pinging: ";
	     Server::Print_Server().send(hdl, response, websocketpp::frame::opcode::text);
	     return true;
     }

     void On_pong(const websocketpp::connection_hdl &hdl, const std::string &payload) {
	     std::string response = "ping received: ";
	     Server::Print_Server().send(hdl, response, websocketpp::frame::opcode::text);
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
	     auto gg = Send::On_Message(hdl, msg->get_payload(), Server::Print_Server(), Server::Hdl(hdl));
	     if (gg == 0) {
		     Server::Close_Game(Server::Get_SessionID(hdl));
		     auto session_id = Server::Get_SessionID(hdl);
		     Server::Start_Game(session_id, hdl);
	     } else if (gg == 1) {
		     Server::Exit_Game(Server::Get_SessionID(hdl));
		     Server::Print_Server().close(hdl, websocketpp::close::status::normal, "Game Exited");
	     } else if (gg == 2) {
		     //check if game exists based on session id
		     auto session_id = Server::Get_SessionID(hdl);
		     if (Server::Game_Instances().find(session_id) != Server::Game_Instances().end()) {
			     // get the game
			     std::cout << "Game Instance exists for session id: " << session_id << std::endl;
			     auto game = Server::Game_Instances().at(session_id);
			     if (game.Exists()) {
				     std::string response = "8 ";
				     std::cout << "Game exists for session id: " << session_id << std::endl;
				     Server::Print_Server().send(hdl, response, websocketpp::frame::opcode::text);
			     } else {
				     std::cout << "Game Exists, but bugged " << session_id << std::endl;
			     }
		     } else {
			     std::cout << "Game Instance does not exist for session id: " << session_id << std::endl;
		     }
	     } else if (gg == 3) {
		     std::cout << "Resuming game" << std::endl;
		     auto response = Server::Resume_Game(Server::Get_SessionID(hdl), hdl);
		     if (!response.empty()) {
			     Send::On_Message(hdl, response, Server::Print_Server(), Server::Hdl(hdl));
		     }
	     } else if (gg == 4) {
		     std::cout << "No action taken" << std::endl;
		     Server::Close_Game(Server::Get_SessionID(hdl));
		     Server::Start_Game(Server::Get_SessionID(hdl), hdl);
		     Send::Init(hdl, msg->get_payload(), Server::Print_Server(), Server::Game_Instances().at(Server::Get_SessionID(hdl)));

	     }

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
