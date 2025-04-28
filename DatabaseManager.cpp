#include "DatabaseManager.h"

DatabaseManager* DatabaseManager::_instance = nullptr;

DatabaseManager::DatabaseManager() {
    _db = QSqlDatabase::addDatabase("QODBC");
    QString connectionString = "Driver={ODBC Driver 18 for SQL Server};"
                               "Server=tcp:hcmus-194200-project.database.windows.net,1433;"
                               "Database=TripAgency;"
                               "Uid=hcmustripagency@hcmus-194200-project;"
                               "Pwd=Hcmus-194200;"
                               "Encrypt=yes;"
                               "TrustServerCertificate=no;"
                               "Connection Timeout=30;";
    // QString connectionString = "Driver={ODBC Driver 18 for SQL Server};"
    //                            "Server=LAPTOP-EMC6ONQH\\NHTHINH;"
    //                            "Database=cpp_travelagency_db;"
    //                            "Uid=sa;"                        // <-- use SQL Server account
    //                            "Pwd=Tinhthinh69@;"             // <-- change this!
    //                            "Encrypt=no;";

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

QSqlDatabase& DatabaseManager::getDatabase() {
    if (!_db.isOpen()) {
        _db.open(); // Tự động mở lại nếu bị đóng
    }
    return _db;
}
