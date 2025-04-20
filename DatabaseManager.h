#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

class DatabaseManager {
private:
    QSqlDatabase db;
    static DatabaseManager* instance;
    DatabaseManager(); // Private constructor

public:
    ~DatabaseManager();
    static DatabaseManager& getInstance();
    bool connect();
    QSqlDatabase getDatabase() const;
};

#endif // DATABASEMANAGER_H
