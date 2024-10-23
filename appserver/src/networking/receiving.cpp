#include "string"

#include "config/asio_no_tls.hpp"
#include "server.hpp"
#include "receiving.h"

#include "send.h"
#include "game.h"

namespace Network {

  typedef websocketpp::server<websocketpp::config::asio> server;
  server print_server;
  std::unordered_map<std::string, websocketpp::connection_hdl> client_connections;

  struct connection_hdl_hash {
    std::size_t operator()(const websocketpp::connection_hdl& hdl) const {
      return std::hash<std::uintptr_t>()(reinterpret_cast<std::uintptr_t>(hdl.lock().get()));
    }
  };
  struct connection_hdl_equal {
    bool operator()(const websocketpp::connection_hdl& hdl1, const websocketpp::connection_hdl& hdl2) const {
      return !hdl1.owner_before(hdl2) && !hdl2.owner_before(hdl1);
    }
  };
  std::unordered_map<websocketpp::connection_hdl, Game::Instance*, connection_hdl_hash, connection_hdl_equal> reverse_client_connections;
  std::unordered_map<std::string, Game::Instance> game_instances;

  std::string Get_SessionID(const websocketpp::connection_hdl& hdl) {
    server::connection_ptr con = print_server.get_con_from_hdl(hdl);
    auto session_id = con->get_resource().substr(con->get_resource().find('=') + 1);
    std::cout << "Session ID: " << session_id << std::endl;
    return session_id;
  }

  //need a map of hdl to Games

  //receive a message from a client
  //check which client sent the message
  //run update on that game world
  //send the message back to the client that sent it

  bool Resume_Game(const std::string& session_id, const websocketpp::connection_hdl& hdl) {
    auto it = client_connections.find(session_id);
    if (it != client_connections.end()) {
      std::cout << "reconnecting player from session id: " << game_instances[session_id].Get_Player().name << std::endl;
      client_connections.erase(session_id);
      std::cout << "removed ol hdl " << std::endl;
      reverse_client_connections[hdl] = &game_instances[session_id];
      std::cout << "successfully reconnected player: " << reverse_client_connections[hdl]->Get_Player().name << std::endl;
      client_connections[session_id] = hdl;

      std:: string response = "41 ";
      Send::On_Message(hdl, response, print_server, *reverse_client_connections[hdl]);
      return true;
    }
    return false;
  }

  void Start_Game(const std::string& session_id, const websocketpp::connection_hdl& hdl) {
    client_connections[session_id] = hdl;
    std::cout << "New connection opened with session ID: " << session_id << std::endl;
    game_instances[session_id] = Game::Init(session_id);
    reverse_client_connections[hdl] = &game_instances[session_id];
    std::cout << "mapped sessionID from hdl: " << reverse_client_connections[hdl]->session_id << std::endl;
  }

  void Close_Game(const std::string& session_id) {
    game_instances.erase(session_id);
    reverse_client_connections.erase(client_connections[session_id]);
    client_connections.erase(session_id);
  }

  void Init_Connection(const websocketpp::connection_hdl& hdl) {
    std::cout << "New connection opened: " << hdl.lock().get() << std::endl;
    std::string response = "0You have initially connected to the server, yay!";
    print_server.send(hdl, response, websocketpp::frame::opcode::text);
    auto session_id = Get_SessionID(hdl);

    if (session_id.empty()) {
      print_server.close(hdl, websocketpp::close::status::policy_violation, "Session ID is required.");
      return;
    }

    if (!Resume_Game(session_id, hdl)) {
      Start_Game(session_id, hdl);
    }

    std::cout << "number of connections: " << client_connections.size() << std::endl;
    std::cout << "number of reverse connections: " << reverse_client_connections.size() << std::endl;
    std::cout << "number of game instances: " << game_instances.size() << std::endl;
  }

  // This function will be called when a new connection is opened.
  // You can put your code here to handle the new connection.
  void On_Open(const websocketpp::connection_hdl& hdl) {
    Init_Connection(hdl);
  }

  void On_close(const websocketpp::connection_hdl& hdl) {
    std::string session_id = Get_SessionID(hdl);

    if (session_id.empty()) {
      print_server.close(hdl, websocketpp::close::status::policy_violation, "Session ID is required.");
      return;
    }
    reverse_client_connections.erase(hdl);
    std::cout << "Connection Closed: " << hdl.lock().get() << std::endl;
  }

  void On_fail(const websocketpp::connection_hdl& hdl) {

  }

  bool On_ping(const websocketpp::connection_hdl& hdl, const std::string& payload) {
//      std::string response = "pinging: ";
//      print_server.send(hdl, response, websocketpp::frame::opcode::text);
      return true;
  }

  void On_pong(const websocketpp::connection_hdl& hdl, const std::string& payload) {
//      std::string response = "ping received: ";
//      print_server.send(hdl, response, websocketpp::frame::opcode::text);
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

  void On_Message(const websocketpp::connection_hdl& hdl, const server::message_ptr& msg) {
    auto gg = Send::On_Message(hdl, msg->get_payload(), print_server, *reverse_client_connections[hdl]);
    if (gg == 0) {
      Close_Game(Get_SessionID(hdl));
      auto session_id = Get_SessionID(hdl);
      Start_Game(session_id, hdl);
    }
    else if (gg == 1) {
      Close_Game(Get_SessionID(hdl));
      print_server.close(hdl, websocketpp::close::status::normal, "Game Closed");
    }
    else if (gg == 2) {

//      print_server.close(hdl, websocketpp::close::status::normal, "Game in progress");
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
