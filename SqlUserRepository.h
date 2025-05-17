#ifndef _SQLUSERREPOSITORY_H_
#define _SQLUSERREPOSITORY_H_

#include "UserRepository.h"
#include "DatabaseManager.h"

class SqlUserRepository: public UserRepository{
    private:
        DatabaseManager& _dbManager;
    public:
        explicit SqlUserRepository(DatabaseManager& dbManager);

        bool addUser(const User& user);
        QSharedPointer<User> getUserByEmail(const QString& email);
        QList<User> getAllUsers();
        bool updateUser(const User& user);
        bool deleteUser(const QString& email);
        bool userExists(const QString& email);
        bool updateUserAvatar(const QString &email, const QString &avatarUrl);
    private:
        User mapResultToUser(const QSqlQuery& query) const;
        bool executeQuery(QSqlQuery& query) const;
};

#endif
