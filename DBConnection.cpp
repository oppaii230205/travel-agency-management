#include "DBConnection.h"

bool DBConnection::connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    // DSN-less connection
    QString connectionString = "Driver={ODBC Driver 18 for SQL Server};"
                               "Server=LAPTOP-EMC6ONQH\\NHTHINH;"
                               "Database=cpp_travelagency_db;"
                               "Uid=sa;"                        // <-- use SQL Server account
                               "Pwd=Tinhthinh69@;"             // <-- change this!
                               "Encrypt=no;";

    db.setDatabaseName(connectionString);

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Database Connection Error", db.lastError().text());
        return false;
    }

    qDebug() << "Database connected successfully.";
    return true;
}
