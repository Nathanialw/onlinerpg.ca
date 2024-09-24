#pragma once
//
// Created by nathanial on 3/29/24.
//
#ifndef BROWSERRPG_LABYRINTH_H
#define BROWSERRPG_LABYRINTH_H

#endif //BROWSERRPG_LABYRINTH_H

namespace Labyrinth {

  const int labyrinthWidth = 32;


  bool Generate_Map();
  std::array<int, labyrinthWidth * labyrinthWidth> Get_Labyrinth();
  std::array<std::string, 15> Get_Map_Cells();
}