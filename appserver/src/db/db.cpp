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
  const char *db_filepath = "/var/www/onlinerpg.ca/appserver/db/data.db";
  int rc = sqlite3_open(db_filepath, &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);
    db = nullptr;
  } else {
    std::cout << "Opened database successfully" << std::endl;
  }
}

std::string Query(const int &itemIB) {
  if (!db) {
    std::cerr << "Database not initialized" << std::endl;
    return "";
  }

  std::string query = "SELECT equipSlot FROM Items WHERE uID = " + std::to_string(itemIB);
  std::cout << query << std::endl;

  sqlite3_stmt *stmt;
  std::cout << "querying" << std::endl;

  int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    return "";
  }

  std::cout << "step" << std::endl;
  rc = sqlite3_step(stmt);
  std::cout << "step success" << std::endl;

  std::string result;
  if (rc == SQLITE_ROW) {
    const unsigned char *text = sqlite3_column_text(stmt, 0);
    if (text) {
      result = std::string(reinterpret_cast<const char *>(text));
    } else {
      result = ""; // or handle the null case as needed
    }
  } else if (rc != SQLITE_DONE) {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
  }

  std::cout << "result: " << result << std::endl;

  sqlite3_finalize(stmt);
  std::cout << "finalized" << std::endl;

  return result;
}
};