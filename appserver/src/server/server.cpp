//
// Created by desktop on 10/30/24.
//

#include "server.h"

namespace Server {

     struct Codes {
	char UPDATE = '1';
	char LOOT = '0';
	char NEWGAME = '0';
	char RECONNECT = '0';
	char STATS = '0';
	char RESTARTGAME = '0';
	char EXITGAME = '0';
	char RESUMEBUTTON = '0';
	char RESUMEGAME = '0';
     };

     server print_server;
     Connections client_connections;
     Reverse_Connections reverse_client_connections;
     Games game_instances;
     Codes codes;

     server &Print_Server() {
	     return print_server;
     };

     Connections &Client_Connections() {
	     return client_connections;
     };

     Games &Game_Instances() {
	     return game_instances;
     };

     Game::Instance &Hdl(const websocketpp::connection_hdl &hd) {
	     return *reverse_client_connections[hd];
     };

     void Send(const websocketpp::connection_hdl &hdl, std::string &message) {
	     print_server.send(hdl, message, websocketpp::frame::opcode::text);
     };


     std::string Resume_Game(const std::string &session_id, const websocketpp::connection_hdl &hdl) {
	     auto it = Server::Client_Connections().find(session_id);
	     if (it != Server::Client_Connections().end()) {
		     std::cout << "reconnecting player from session id: " << game_instances.at(session_id).Get_Player().name.firstName << std::endl;
		     Server::Client_Connections().erase(session_id);
		     std::cout << "removed ol hdl " << std::endl;
		     reverse_client_connections[hdl] = &game_instances.at(session_id);
		     std::cout << "successfully reconnected player: " << reverse_client_connections[hdl]->Get_Player().name.firstName << std::endl;
		     Server::Client_Connections()[session_id] = hdl;

		     return "41";
	     }
	     return "";
     }

     void Start_Game(const std::string &session_id, const websocketpp::connection_hdl &hdl) {
	     Server::Client_Connections()[session_id] = hdl;
	     std::cout << "New connection opened with session ID: " << session_id << std::endl;
	     game_instances.emplace(session_id, Game::Instance(session_id));
	     reverse_client_connections[hdl] = &game_instances.at(session_id);
	     std::cout << "mapped sessionID from hdl: " << reverse_client_connections[hdl]->session_id << std::endl;
     }

     void Close_Game(const std::string &session_id) {
	     game_instances.erase(session_id);
	     reverse_client_connections.erase(Server::Client_Connections()[session_id]);
	     Server::Client_Connections().erase(session_id);
	     std::cout << "Game Closed" << std::endl;
     }

     void Exit_Game(const std::string &session_id) {
//    game_instances.erase(session_id);
//    reverse_client_connections.erase(client_connections[session_id]);
//    client_connections.erase(session_id);
	     std::cout << "Exiting game" << std::endl;
     }

     std::string Get_SessionID(const websocketpp::connection_hdl &hdl) {
	     server::connection_ptr con = Server::Print_Server().get_con_from_hdl(hdl);
	     auto session_id = con->get_resource().substr(con->get_resource().find('=') + 1);
	     std::cout << "Session ID: " << session_id << std::endl;
	     return session_id;
     }

     void Close_Connection(const websocketpp::connection_hdl &hdl) {
	     std::string session_id = Server::Get_SessionID(hdl);

	     if (session_id.empty()) {
		     Server::Print_Server().close(hdl, websocketpp::close::status::policy_violation, "Session ID is required.");
		     return;
	     }
	     reverse_client_connections.erase(hdl);
	     std::cout << "Connection Closed: " << hdl.lock().get() << std::endl;
     }


     void Init_Connection(const websocketpp::connection_hdl &hdl) {
	     std::cout << "New connection opened: " << hdl.lock().get() << std::endl;
	     std::string response = "0You have initially connected to the server, yay!";
	     Server::Print_Server().send(hdl, response, websocketpp::frame::opcode::text);
	     auto session_id = Get_SessionID(hdl);

	     if (session_id.empty()) {
		     Server::Print_Server().close(hdl, websocketpp::close::status::policy_violation, "Session ID is required.");
		     return;
	     }

	     //if the game does not exist, create a new game
	     if (game_instances.find(session_id) == game_instances.end()) {
		     Start_Game(session_id, hdl);
	     }
//    else {
//      Close_Game(session_id);
//      Start_Game(session_id, hdl);
//      std::cout << "Game Instance already exists for session id: " << session_id << "Closing and starting a new one" << std::endl;
//    }

	     std::cout << "number of connections: " << Server::Client_Connections().size() << std::endl;
	     std::cout << "number of reverse connections: " << reverse_client_connections.size() << std::endl;
	     std::cout << "number of game instances: " << game_instances.size() << std::endl;
     }

     bool Enter_Game(const websocketpp::connection_hdl &hdl, int8_t gg) {
	     if (gg == 0) {
		     Server::Close_Game(Server::Get_SessionID(hdl));
		     auto session_id = Server::Get_SessionID(hdl);
		     Server::Start_Game(session_id, hdl);
	     } else if (gg == 1) { //close game
		     Server::Exit_Game(Server::Get_SessionID(hdl));
		     Server::Print_Server().close(hdl, websocketpp::close::status::normal, "Game Exited");
	     } else if (gg == 2) { //create resume button
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
	     } else if (gg == 3) { //resume game
		     std::cout << "Resuming game" << std::endl;
		     auto response = Server::Resume_Game(Server::Get_SessionID(hdl), hdl);
		     if (!response.empty()) {
			     return true;
		     }
	     } else if (gg == 4) { //New Game
		     std::cout << "No action taken" << std::endl;
		     Server::Close_Game(Server::Get_SessionID(hdl));
		     Server::Start_Game(Server::Get_SessionID(hdl), hdl);
		     return true;
	     }
	     return false;
     }
};
