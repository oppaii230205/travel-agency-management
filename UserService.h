#ifndef _USERSERVICE_H_
#define _USERSERVICE_H_

#include <QObject>
#include <QSharedPointer>
#include "SqlUserRepository.h"
#include "CrypToUtils.h"
#include "constants.h"
#include <QSqlQuery>

class UserService : public QObject
{
    Q_OBJECT
public:
    explicit UserService(QSharedPointer<SqlUserRepository> userRepo, QObject* parent = nullptr);
    UserService() = default;

    QSharedPointer<User> getUserByEmail(const QString& email);
    QList<User> getAllUsers();
    bool updateUser(const QString& email, const QString& newPassword, const QString& newName);
    bool deleteUser(const QString& email);
    bool updateUserAvatar(const QString &email, const QString &avatarUrl);
private:
    QSharedPointer<SqlUserRepository> _userRepo;
};

#endif // USERSERVICE_H
