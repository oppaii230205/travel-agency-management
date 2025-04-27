#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

class DatabaseManager {
private:
    QSqlDatabase _db;
    static DatabaseManager* _instance;
    DatabaseManager(); // Private constructor

public:
    ~DatabaseManager();
    static DatabaseManager& getInstance();
    bool connect();
    QSqlDatabase& getDatabase();
};

#endif // DATABASEMANAGER_H
