#ifndef _SQLUSERREPOSITORY_H_
#define _SQLUSERREPOSITORY_H_

#include "UserRepository.h"
#include <QSqlDatabase>

class SqlUserRepository: public UserRepository{
    private:
        const QSqlDatabase& _database;
    public:
        explicit SqlUserRepository(const QSqlDatabase& db);

        bool addUser(const User& user);
        QSharedPointer<User> getUserByEmail(const QString& email);
        QList<User> getAllUsers();
        bool updateUser(const User& user);
        bool deleteUser(const QString& email);
        bool userExists(const QString& email);
    private:
        User mapResultToUser(const QSqlQuery& query) const;
        bool executeQuery(QSqlQuery& query) const;
};

#endif
