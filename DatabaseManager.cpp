#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Database opened successfully!" << std::endl;
    }
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(db);
}

bool DatabaseManager::execute(const std::string& query) {
    char* errorMessage;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}
