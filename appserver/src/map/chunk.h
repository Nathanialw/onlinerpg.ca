#pragma once

//
// Created by desktop on 10/1/24.
//

#ifndef BROWSERRPG_CHUNK_H
#define BROWSERRPG_CHUNK_H

#endif // BROWSERRPG_CHUNK_H

#include "components.h"
#include "units.h"
#include "procgen.h"

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

  void Create_Chunk(char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], std::vector<Room> &rooms, Component::sNode pathing[Component::mapWidth * Component::mapWidth], Proc_Gen::Seed &seed, Units::Objects &objects);
  void Add_Rooms(char defaultChunk[Component::mapWidth][Component::mapWidth], std::vector<Room> &rooms);
}