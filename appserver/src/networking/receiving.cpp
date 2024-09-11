
#include "string"

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include "map.h"
#include "receiving.h"
#include "units.h"

namespace Network {

  typedef websocketpp::server<websocketpp::config::asio> server;
  server print_server;


  // This function will be called when a new connection is opened.
  // You can put your code here to handle the new connection.
  void On_Open(websocketpp::connection_hdl hdl) {
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

    //response = "0Map: ";
//    print_server.send(hdl, response, websocketpp::frame::opcode::text);
    print_server.send(hdl, Map::Send(), websocketpp::frame::opcode::text);

    //this will place Entities on a map with every connect, what we want to do is run this on startup then send the map that's already in memory
//    response = "0sending units: ";
//    print_server.send(hdl, response, websocketpp::frame::opcode::text);
//      print_server.send(hdl, Units::unitsOnMap[0], websocketpp::frame::opcode::text);
    print_server.send(hdl, Units::Send_Units(), websocketpp::frame::opcode::text);
  }

  void On_close(websocketpp::connection_hdl hdl) {
    std::cout << "Connection Closed: " << hdl.lock().get() << std::endl;
  }

  void On_fail(websocketpp::connection_hdl hdl) {

  }

  bool On_ping(websocketpp::connection_hdl hdl, std::string payload) {
      std::string response = "pinging: ";
      print_server.send(hdl, response, websocketpp::frame::opcode::text);
      return true;
  }

  void On_pong(websocketpp::connection_hdl hdl, std::string payload) {

  }

  void On_pong_timeout(websocketpp::connection_hdl hdl, std::string payload) {

  }

  void On_interrupt(websocketpp::connection_hdl hdl) {

  }

  void On_http(websocketpp::connection_hdl hdl) {

  }

  bool On_validate(websocketpp::connection_hdl hdl) {

    return true;
  }

  void On_Message(const websocketpp::connection_hdl& hdl, const server::message_ptr& msg) {
      //I will need to send this somewhere to get parsed and decide what the response should be
      std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;

     //keep websocket alive
      std::string response;


    //[0] message type [1-2] ID (uint16_t stored as 2 chars) [3] message;
    //ie: 1a2w;
    if (!msg->get_payload().empty()) {
        if (msg->get_payload()[0] == '1') { //"1" is the action turn, right now it only means move.
            //move player
            std::string direction = &msg->get_payload()[1];
            Units::Update(direction);
            //Map::Send();
            //Units::Send_Units();

            response = "0I hear you pressing: ";
            response.append(&msg->get_payload()[1]);
            print_server.send(hdl, response, websocketpp::frame::opcode::text);
        }
        else {
            response = "0pinging";
            print_server.send(hdl, response, websocketpp::frame::opcode::text);
        }
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
