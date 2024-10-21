#pragma once
//
// Created by desktop on 10/13/24.
//

#ifndef BROWSERRPG_DB_H
#define BROWSERRPG_DB_H
#include "string"
#include "vector"

namespace DB {
  std::string Query(const std::string &retrieve, const std::string &table, const std::string &where, const std::string &equals);
//  std::vector<std::string> Get_List(const std::string &retrieve, const std::string &table, const std::string &where, const std::string &equals);
  std::vector<std::string> Get_List(const std::string &retrieve, const std::string &table, const std::string &where, const std::string &equals, const std::string &where2, const std::string &equals2);
  void Init();
  int Get_Num_Items();
};

#endif // BROWSERRPG_DB_H
