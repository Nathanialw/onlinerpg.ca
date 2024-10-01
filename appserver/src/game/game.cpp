//
// Created by desktop on 9/30/24.
//
#include "game.h"

namespace Game {

//  void Run() {
  State Init(const std::string& session_id) {
        State state;
        state.session_id = session_id;
        return state;
  }

}