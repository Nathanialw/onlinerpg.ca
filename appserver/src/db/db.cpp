//
// Created by desktop on 10/13/24.
//

#include "db.h"
#include "sqlite3.h"
#include "string"

namespace DB {
  //create db
  sqlite3 *db;

  void Init() {
      sqlite3_open("db/data.db", &db);
  }

  std::string Query(const int &itemIB) {
      //take a single string and return a single string from the db
      std::string query = "SELECT item_name FROM items WHERE item_id = " + std::to_string(itemIB);

      sqlite3_stmt *stmt;
      sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
      sqlite3_step(stmt);
      std::string result = (char *) sqlite3_column_text(stmt, 0);
      sqlite3_finalize(stmt);
      return result;
  }
};