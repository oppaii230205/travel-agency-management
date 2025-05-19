#include "SqlUserRepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

//Do "User" là từ khóa riêng của SQL server nên đặt vào []

SqlUserRepository::SqlUserRepository(DatabaseManager& dbManager) : _dbManager(dbManager){
    if (!_dbManager.getDatabase().isOpen()) {
        qCritical() << "Database is not open!";
    }
}

bool SqlUserRepository::addUser(const User& user){
    if(!user.isValid()){
        qWarning() << "Invalid user data";
        return false;
    }
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("INSERT INTO [USER] (email, password, name, role) VALUES (:email, :password, :name, :role)");
    query.bindValue(":email", user.email());
    query.bindValue(":password", user.password());
    query.bindValue(":name", user.name());
    query.bindValue(":role", user.role());

    return executeQuery(query);
}

QSharedPointer<User> SqlUserRepository::getUserByEmail(const QString& email){
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("Select * FROM [USER] WHERE email = :email");
    query.bindValue(":email", email);
    if(!executeQuery(query) || !query.next()){
        return nullptr;
    }
    return QSharedPointer<User>::create(mapResultToUser(query));
}


QList<User> SqlUserRepository::getAllUsers(){
    QList<User> users;
    QSqlQuery query("SELECT * FROM [USER]", _dbManager.getDatabase());
    if(executeQuery(query)){
        while(query.next()){
            users.append(mapResultToUser(query));
        }
    }
    return users;
}

bool SqlUserRepository::updateUser(const User& user){
    if(!user.isValid()){
        qWarning() << "Invalid user data";
        return false;
    }

    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("UPDATE [USER] SET password = :password, name = :name, role = :role WHERE email = :email");
    query.bindValue(":password", user.password());
    query.bindValue(":name", user.name());
    query.bindValue(":role", user.role());
    query.bindValue(":email", user.email());

    return executeQuery(query);
}

bool SqlUserRepository::deleteUser(const QString& email) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("DELETE FROM [USER] WHERE email = :email");
    query.bindValue(":email", email);
    
    return executeQuery(query);
}

bool SqlUserRepository::userExists(const QString& email) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("SELECT COUNT(*) FROM [USER] WHERE email = :email");
    query.bindValue(":email", email);
    
    return executeQuery(query) && query.next() && query.value(0).toInt() > 0;
}

User SqlUserRepository::mapResultToUser(const QSqlQuery& query) const {
    return User(
        query.value("email").toString(),
        query.value("password").toString(),
        query.value("name").toString(),
        query.value("role").toString(),
        query.value("avatar_url").toString()
    );
}

bool SqlUserRepository::executeQuery(QSqlQuery& query) const {
    if (!query.exec()) {
        qWarning() << "Database error:" << query.lastError().text();
        return false;
    }
    return true;
}

bool SqlUserRepository::updateUserAvatar(const QString &email, const QString &avatarUrl) {
    QSqlQuery query;
    query.prepare("UPDATE [user] SET avatar_url = ? WHERE email = ?");
    query.addBindValue(avatarUrl);
    query.addBindValue(email);
    return query.exec();
}
