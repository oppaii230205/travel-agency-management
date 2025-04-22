#include "DatabaseManager.h"

DatabaseManager* DatabaseManager::_instance = nullptr;

DatabaseManager::DatabaseManager() {
    _db = QSqlDatabase::addDatabase("QODBC");
    QString connectionString = "Driver={ODBC Driver 18 for SQL Server};"
                               "Server=LAPTOP-EMC6ONQH\\NHTHINH;"
                               "Database=cpp_travelagency_db;"
                               "Uid=sa;"
                               "Pwd=Tinhthinh69@;"
                               "Encrypt=no;";
    _db.setDatabaseName(connectionString);
}

DatabaseManager::~DatabaseManager() {
    if (_db.isOpen()) {
        _db.close();
    }
    _instance = nullptr;
}

DatabaseManager& DatabaseManager::getInstance() {
    if (!_instance) {
        _instance = new DatabaseManager();
    }
    return *_instance;
}

bool DatabaseManager::connect() {
    if (!_db.open()) {
        qDebug() << "Database connection failed:" << _db.lastError().text();
        return false;
    }
    qDebug() << "Database connected successfully.";
    return true;
}

QSqlDatabase DatabaseManager::getDatabase() const {
    return _db;
}
