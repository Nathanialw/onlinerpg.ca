#pragma once

//
// Created by desktop on 10/1/24.
//

#ifndef BROWSERRPG_CHUNK_H
#define BROWSERRPG_CHUNK_H

#endif // BROWSERRPG_CHUNK_H
//#include "map.h"
//#include "pathing.h"
//#include "game.h"
#include "components.h"

namespace Chunk {

  struct Room {
    int x;
    int y;
    int w;
    int h;
  };

  struct Map_Chunk {
    char chunk[Component::mapWidth][Component::mapWidth];
    char defaultChunk[Component::mapWidth][Component::mapWidth];
    Component::sNode pathing[Component::mapWidth * Component::mapWidth];

    std::vector<Room> rooms;
  };

//  void Add_Map_Chunk(Game::State &game);
  void Add_Rooms(char defaultChunk[Component::mapWidth][Component::mapWidth], std::vector<Room> &rooms);
}