#pragma once
//
// Created by nathanial on 3/29/24.
//

#ifndef BROWSERRPG_MAP_H
#define BROWSERRPG_MAP_H

#endif //BROWSERRPG_MAP_H

#include "string"
#include "units.h"
#include "game.h"

namespace Map {


  std::string Init(Chunk::Chunk defaultChunk, Chunk::Chunk chunk, std::vector<Chunk::Room> &rooms, Proc_Gen::Seed &seed);
  std::string SendMapSegment(Game::Instance &game, const std::string& direction, int state = 1);
  std::string Get_Adjacent_Tile(Game::Instance &game, int level, Component::Position location, Component::Position newPosition);
  std::string Get_Map(Chunk::Chunk chunk);
  void Update(Game::Instance &game, int level, Component::Position location, Component::Position &position,  Component::Position &move, const char &tile) ;
  void Update(Game::Instance &game, int level, Component::Position formerPosition, Component::Position newPosition, Component::Position formerLocation, Component::Position newLocation, const char &tile);
  void Set_Tile(Chunk::Chunk chunk, int x, int y, const char &tile);
  void Reset_Tile(Chunk::Chunk defaultChunk, Chunk::Chunk chunk, int x, int y);
  void Check_Map_Chunk(Game::Instance &game);
}