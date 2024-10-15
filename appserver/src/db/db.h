#pragma once
//
// Created by desktop on 10/13/24.
//

#ifndef BROWSERRPG_DB_H
#define BROWSERRPG_DB_H
#include "string"

namespace DB {
  std::string Query(const std::string &retrieve, const std::string &table, const std::string &where, const std::string &equals);
  void Init();
  int Get_Num_Items();
};

#endif // BROWSERRPG_DB_H
