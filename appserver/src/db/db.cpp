//
// Created by desktop on 10/13/24.
//

#include "db.h"
#include "sqlite3.h"
#include "string"
#include "iostream"

namespace DB {
  //create db
  sqlite3 *db;

  void Init() {
      sqlite3_open("db/data.db", &db);
  }

  std::string Query(const int &itemIB) {
      //take a single string and return a single string from the db
      std::string query = "SELECT equipSlot FROM Items WHERE uID = " + std::to_string(itemIB);
      std::cout << query << std::endl;

      sqlite3_stmt *stmt;
      std::cout << "querying" << std::endl;

      sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
      std::cout << "step" << std::endl;

      sqlite3_step(stmt);
      std::cout << "step success" << std::endl;

      std::string result = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
      std::cout << "result: " << result << std::endl;

      sqlite3_finalize(stmt);
      std::cout << "finalized" << std::endl;

      return result;
  }
};