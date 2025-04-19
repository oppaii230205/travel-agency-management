#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

class DBConnection {
private:
public:
    static bool connectToDatabase();
};

#endif // DBCONNECTION_H
