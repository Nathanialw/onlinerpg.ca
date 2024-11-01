#pragma once
//
// Created by desktop on 10/13/24.
//

#include "string"
#include "vector"

namespace DB {

     std::string Query(const std::string &retrieve, const std::string &table, const std::string &where, const std::string &equals);

     std::vector<std::string> Get_List(const std::string &retrieve, const std::string &table, const std::vector<std::pair<std::string, std::string>> &whereEquals);

     void Init();

     int Get_Num_Items();
};
