//
// Created by desktop on 9/30/24.
//
#include "game.h"

namespace Game {

//  void Run() {
Instance Init(const std::string& session_id) {
  Instance Game;
    Game.session_id = session_id;
    return Game;
  }

}