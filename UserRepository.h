#ifndef _USERREPOSITORY_H_
#define _USERREPOSITORY_H_

#include "User.h"
#include <QList>
#include <QSharedPointer>

class UserRepository {
    public:
        virtual ~UserRepository() = default;

        virtual bool addUser(const User& user) = 0;
        virtual QSharedPointer<User> getUserByEmail(const QString& email) = 0;
        virtual QList<User> getAllUsers() = 0;
        virtual bool updateUser(const User& user) = 0;
        virtual bool deleteUser(const QString& email) = 0;

        virtual bool userExists(const QString& email) = 0;
        virtual bool updateUserAvatar(const QString &email, const QString &avatarUrl) = 0;
};


#endif
