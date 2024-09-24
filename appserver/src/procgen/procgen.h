//
// Created by desktop on 9/24/24.
//
#pragma once
#ifndef BROWSERRPG_PROCGEN_H
#define BROWSERRPG_PROCGEN_H

#endif // BROWSERRPG_PROCGEN_H

namespace Proc_Gen {
  struct Seed {
    uint32_t seed = 0;
  };

  uint32_t Create_Initial_Seed(uint32_t x, uint32_t y);
  int Random_Int(int min, int max, Seed &seed);
  double Random_Int(double min, double max, Seed &seed);
  float Random_float(int min, int max, Seed &seed);
}