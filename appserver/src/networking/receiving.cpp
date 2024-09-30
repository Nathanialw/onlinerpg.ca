

#include "string"

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include "map.h"
#include "receiving.h"
#include "update.h"
#include "goblin.h"
#include "pathing.h"
#include "spawn.h"

namespace Network {

  typedef websocketpp::server<websocketpp::config::asio> server;
  server print_server;
  std::unordered_map<std::string, websocketpp::connection_hdl> client_connections;


  // This function will be called when a new connection is opened.
  // You can put your code here to handle the new connection.
  void On_Open(const websocketpp::connection_hdl& hdl) {
    //send the client the map information
    //create/load player object for the client
    std::cout << "New connection opened: " << hdl.lock().get() << std::endl;
    std::string response = "0You have initially connected to the server, yay!";
    print_server.send(hdl, response, websocketpp::frame::opcode::text);

    //client logs in
    //on start client will need to ask for his user data
    //should write it in PHP;

    //client will get his uID and store it
    //client will get all the uIDs for all other units on the map and store them and himself in the unordered_map
    server::connection_ptr con = print_server.get_con_from_hdl(hdl);
    std::string session_id = con->get_resource().substr(con->get_resource().find('=') + 1);
    std::cout << "Session ID: " << session_id << std::endl;

    if (session_id.empty()) {
      print_server.close(hdl, websocketpp::close::status::policy_violation, "Session ID is required.");
      return;
    }

    client_connections[session_id] = hdl;
    std::cout << "New connection opened with session ID: " << session_id << std::endl;


    //this will place Entities on a map with every connect, what we want to do is run this on startup then send the map that's already in memory
//    response = "0sending units: ";
//    print_server.send(hdl, response, websocketpp::frame::opcode::text);
//      print_server.send(hdl, Units::unitsOnMap[0], websocketpp::frame::opcode::text);

    //print_server.send(hdl, Units::Send_Units(), websocketpp::frame::opcode::text);
  }

  void On_close(const websocketpp::connection_hdl& hdl) {
    server::connection_ptr con = print_server.get_con_from_hdl(hdl);
    std::string session_id = con->get_resource().substr(con->get_resource().find('=') + 1);

    if (session_id.empty()) {
      print_server.close(hdl, websocketpp::close::status::policy_violation, "Session ID is required.");
      return;
    }

    client_connections[session_id] = hdl;
    std::cout << "New connection opened with session ID: " << session_id << std::endl;

    std::cout << "Connection Closed: " << hdl.lock().get() << std::endl;
  }

  void On_fail(const websocketpp::connection_hdl& hdl) {

  }

  bool On_ping(const websocketpp::connection_hdl& hdl, const std::string& payload) {
      //std::string response = "pinging: ";
      //print_server.send(hdl, response, websocketpp::frame::opcode::text);
      return true;
  }

  void On_pong(const websocketpp::connection_hdl& hdl, const std::string& payload) {

  }

  void On_pong_timeout(const websocketpp::connection_hdl& hdl, const std::string& payload) {

  }

  void On_interrupt(const websocketpp::connection_hdl& hdl) {

  }

  void On_http(const websocketpp::connection_hdl& hdl) {

  }

  bool On_validate(const websocketpp::connection_hdl& hdl) {

    return true;
  }

  void Start(const websocketpp::connection_hdl& hdl, const server::message_ptr& msg) {
    std::string map = Map::Init();
    std::cout << "map inited" << std::endl;
    Pathing::Init(map);
    std::cout << "path inited" << std::endl;
    Spawn::Init(msg->get_payload());
    std::cout << "units inited" << std::endl;
    print_server.send(hdl, Units::GetCharStats(), websocketpp::frame::opcode::text);
    std::cout << "char stats sent!" << std::endl;

    if (!Units::Get_Units()->empty()) {
      print_server.send(hdl, Map::SendMapSegment(Units::Get_Player(), "q"), websocketpp::frame::opcode::text);
      std::cout << "map sent!" << std::endl;
    }

    std::cout << "Ready!" << std::endl;
  }

  void Update(const websocketpp::connection_hdl& hdl, const server::message_ptr& msg) {
    std::string response;
    //move player
    const char* direction = &msg->get_payload()[1];
    auto action = Update::Update_Units(direction);
    //send map
    print_server.send(hdl, Map::SendMapSegment(Units::Get_Player(), action), websocketpp::frame::opcode::text);

    response = "0I hear you pressing: ";
    response.append(&msg->get_payload()[1]);
    print_server.send(hdl, response, websocketpp::frame::opcode::text);

    std::cout << "sending char stats back  to client" << std::endl;
    print_server.send(hdl, Units::GetCharStats(), websocketpp::frame::opcode::text);
  }

  void On_Message(const websocketpp::connection_hdl& hdl, const server::message_ptr& msg) {
    //I will need to send this somewhere to get parsed and decide what the response should be
//    std::cout << "on_message called with hdl: " << hdl.lock().get() << " and message: " << msg->get_payload() << std::endl;
   //keep websocket alive
    std::string response;
    if (msg->get_payload()[0] == '1') { //"1" is the action turn, right now it only means move.
      std::cout << "1" << msg->get_payload() << std::endl;
      Update(hdl, msg);
    }
    else if (msg->get_payload()[0] == '2') {
      std::cout << "2" << msg->get_payload() << std::endl;
      //unused
      response = "0 response \"2\" is unused, message was: ";
      response.append(&msg->get_payload()[1]);
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }
    else if (msg->get_payload()[0] == '3') {
      std::cout << "3" << msg->get_payload() << std::endl;
      //send map
      Start(hdl, msg);
    }
    else if (msg->get_payload()[0] == '4') {
      std::cout << "4" << msg->get_payload() << std::endl;
      print_server.send(hdl, Units::GetCharStats(), websocketpp::frame::opcode::text);
      std::cout << "char stats sent!" << std::endl;

      if (!Units::Get_Units()->empty()) {
        print_server.send(hdl, Map::SendMapSegment(Units::Get_Player(), "1   0"), websocketpp::frame::opcode::text);
      }
      std::cout << "Ready!" << std::endl;
    }
    else if (msg->get_payload()[0] == '5') {
      std::cout << "5" << msg->get_payload() << std::endl;
      response.append(msg->get_payload().substr(1, 4));
      response = "5" + Species::Get_Unit_Data_As_string(response);
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }

    else {
//            response = "0pinging";
//            print_server.send(hdl, response, websocketpp::frame::opcode::text);
    }


    //[0] message type [1-2] ID (uint16_t stored as 2 chars) [3] message;
    //ie: 1a2w;
    if (!msg->get_payload().empty()) {
    }
    //when a player moves, send the new position to all the clients except the one that sent it right away

    //every entity needs to be saved as a uID
    //each client will need to know which entity is the player that moved
    //so every client needs a map of uID to entity
    //ill need to send the uID and the position and let the client update the position



    //I think send the full update every 2 seconds
  }


  void Init () {
    print_server.set_close_handler(On_close);
    print_server.set_fail_handler(On_fail);
    print_server.set_ping_handler(On_ping);
    print_server.set_pong_handler(On_pong);
    print_server.set_pong_timeout_handler(On_pong_timeout);
    print_server.set_interrupt_handler(On_interrupt);
    print_server.set_http_handler(On_http);
    print_server.set_validate_handler(On_validate);
    print_server.set_open_handler(&On_Open);
    print_server.set_message_handler(&On_Message);

    print_server.init_asio();
    print_server.listen(9002);
    print_server.start_accept();
  }

  void Run() {
    Init();
    print_server.run();
  }
}
