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
#include "pathing.h"

namespace Chunk {

  typedef char Chunk[Component::mapWidth][Component::mapWidth] ;

  struct Room {
    uint8_t x;
    uint8_t y;
    uint8_t w;
    uint8_t h;
  };

  struct Map_Chunk {
    Chunk chunk;
    Chunk defaultChunk;
    Pathing::Map pathing;

    std::vector<Room> rooms;
  };

  void Create_Chunk(Map_Chunk &mapChunk, int8_t level, Component::Position location, std::vector<Room> &rooms, Proc_Gen::Seed &seed, Units::Objects &objects);
  void Add_Rooms(Chunk defaultChunk, std::vector<Room> &rooms);
}