#include "DBConnection.h"

bool DBConnection::connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    
    // Chuỗi kết nối cho Azure SQL (tương đương với phiên bản C)
    QString connectionString = 
        "Driver={ODBC Driver 18 for SQL Server};"
        "Server=tcp:hcmus-194200-project.database.windows.net,1433;"
        "Database=TripAgency;"
        "Uid=hcmustripagency@hcmus-194200-project;"
        "Pwd=Hcmus-194200;"
        "Encrypt=yes;"
        "TrustServerCertificate=no;"
        "Connection Timeout=30;";

    db.setDatabaseName(connectionString);

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Database Connection Error", 
                            "Connection failed:\n" + db.lastError().text());
        return false;
    }

    qDebug() << "Database connected successfully.";
    return true;
}
