#include "DatabaseManager.h"

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QODBC");
    QString connectionString = "Driver={ODBC Driver 18 for SQL Server};"
                               "Server=LAPTOP-EMC6ONQH\\NHTHINH;"
                               "Database=cpp_travelagency_db;"
                               "Uid=sa;"
                               "Pwd=Tinhthinh69@;"
                               "Encrypt=no;";
    db.setDatabaseName(connectionString);
}

DatabaseManager::~DatabaseManager() {
    if (db.isOpen()) {
        db.close();
    }
    instance = nullptr;
}

DatabaseManager& DatabaseManager::getInstance() {
    if (!instance) {
        instance = new DatabaseManager();
    }
    return *instance;
}

bool DatabaseManager::connect() {
    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return false;
    }
    qDebug() << "Database connected successfully.";
    return true;
}

QSqlDatabase DatabaseManager::getDatabase() const {
    return db;
}
