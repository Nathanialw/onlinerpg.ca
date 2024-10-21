//
// Created by desktop on 10/13/24.
//

#include "db.h"
#include "sqlite3.h"
#include "iostream"

namespace DB {
  //create db
  sqlite3 *db;

  //need to use this on the row data string when it is passed as a reference
  std::string Append_Quotes(std::string str) {
    return "'" + str + "'";
  }

  void Init() {
    const char *db_filepath = "db/data.db";
    int rc = sqlite3_open(db_filepath, &db);
    if (rc) {
      std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_close(db);
      db = nullptr;
    } else {
      std::cout << "Opened database successfully" << std::endl;
    }
  }

  int Get_Num_Items() {
    if (!db) {
      std::cerr << "Database not initialized" << std::endl;
      return 0;
    }

    std::string query = "SELECT MAX(uID) FROM Items";
    std::cout << query << std::endl;

    sqlite3_stmt *stmt;
    std::cout << "querying" << std::endl;

    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
      return 0;
    }

    std::cout << "step" << std::endl;
    rc = sqlite3_step(stmt);
    std::cout << "step success" << std::endl;

    int result = 0;
    if (rc == SQLITE_ROW) {
      result = sqlite3_column_int(stmt, 0);
    } else if (rc != SQLITE_DONE) {
      std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }

    std::cout << "result: " << result << std::endl;

    sqlite3_finalize(stmt);
    std::cout << "finalized" << std::endl;

    return result;
  }

  std::string Query(const std::string &retrieve, const std::string &table, const std::string &where, const std::string &equals) {
    if (!db) {
      std::cerr << "Database not initialized" << std::endl;
      return "";
    }

    std::string query = "SELECT " + retrieve + " FROM " + table + " WHERE " + where + " = " + Append_Quotes(equals);

    sqlite3_stmt *stmt;
    std::cout << "querying" << query << std::endl;

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

  std::vector<std::string> Get_List(const std::string &retrieve, const std::string &table, const std::vector<std::pair<std::string, std::string>> &whereEquals) {
    std::vector<std::string> results;
    if (!db) {
      std::cerr << "Database not initialized" << std::endl;
      return results;
    }

    std::string query = "SELECT " + retrieve + " FROM " + table + " WHERE ";
    for (int i = 0; i < whereEquals.size(); ++i) {
      query += whereEquals[i].first + " = " + Append_Quotes(whereEquals[i].second);
      if (i < whereEquals.size() - 1) {
        query += " AND ";
      }
    }

    sqlite3_stmt *stmt;
    std::cout << "querying: " << query << std::endl;

    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
      return results;
    }

    std::cout << "step" << std::endl;
    rc = sqlite3_step(stmt);
    std::cout << "step success" << std::endl;

    while (rc == SQLITE_ROW) {
      const unsigned char *text = sqlite3_column_text(stmt, 0);
      if (text) {
        results.emplace_back(reinterpret_cast<const char *>(text));
      }
      rc = sqlite3_step(stmt);
    }

    if (rc != SQLITE_DONE) {
      std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }

    std::cout << "number of results: " << results.size() << std::endl;

    sqlite3_finalize(stmt);
    std::cout << "finalized" << std::endl;

    if (results.empty()) {
      std::cerr << "No results found" << std::endl;
      results.emplace_back("Default");
    }
    return results;
  }

};