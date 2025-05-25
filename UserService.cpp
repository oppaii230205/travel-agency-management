#include "UserService.h"

UserService::UserService(QSharedPointer<UserRepository> userRepo, QObject* parent): QObject(parent), _userRepo(userRepo){
    if(!_userRepo){
        qCritical() << "UserRepository is null!";
    }
}

QSharedPointer<User> UserService::getUserByEmail(const QString& email){
    if (!_userRepo){
        return nullptr;
    }
    return _userRepo->getUserByEmail(email);
}

QList<User> UserService::getAllUsers(){
    if (!_userRepo){
        return QList<User>();
    }
    return _userRepo->getAllUsers();
}

bool UserService::updateUser(const QString &email, const QString &newPassword, const QString &newName){
    if (!_userRepo) return false;

    auto user = _userRepo->getUserByEmail(email);
    if (!user) return false;
    QString ePassword = CryptoUtils::encrypt(newPassword, eKey);
    User updatedUser(email, newPassword.isEmpty() ? user->password() : ePassword, newName.isEmpty() ? user->name() : newName, user->role(), user->avatarUrl());

    return _userRepo->updateUser(updatedUser);

}

bool UserService::deleteUser(const QString& email){
    if(!_userRepo){
        return false;
    }
    return _userRepo->deleteUser(email);
}

bool UserService::updateUserAvatar(const QString &email, const QString &avatarUrl) {
    if (!_userRepo) return false;
    return _userRepo->updateUserAvatar(email, avatarUrl);
}
