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


  std::string Init(char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], std::vector<Chunk::Room> &rooms, Proc_Gen::Seed &seed);
  std::string SendMapSegment(Game::State &game, const std::string& direction, int state = 1);
  std::string Get_Adjacent_Tile(Game::State &game, int x, int y);
  std::string Get_Map(char chunk[Component::mapWidth][Component::mapWidth]);
  void Update(Game::State &game, int px, int py, int x, int y, const char &tile);
  void Set_Tile(char chunk[Component::mapWidth][Component::mapWidth], int x, int y, const char &tile);
  void Reset_Tile(char defaultChunk[Component::mapWidth][Component::mapWidth], char chunk[Component::mapWidth][Component::mapWidth], int x, int y);
  void Check_Map_Chunk(Game::State &game);
}