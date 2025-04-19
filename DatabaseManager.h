#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <sqlite3.h>
#include <string>

class DatabaseManager {
private:
    sqlite3* db;

public:
    DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    bool execute(const std::string& query);
};

#endif
