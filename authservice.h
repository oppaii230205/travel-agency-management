#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "UserRepository.h"
#include <QObject>
#include <QSharedPointer>

class AuthService : public QObject {
    Q_OBJECT
public:
    explicit AuthService(QSharedPointer<UserRepository> userRepo, QObject* parent = nullptr);
    AuthService() = default;
    bool login(const QString& email, const QString& password);
    bool signup(const QString& email, const QString& password, const QString& name);
    QSharedPointer<User> getCurrentUser() const;
    bool hasPermission(const QString& requiredRole) const;

signals:
    void loginSuccess();
    void loginFailed(const QString& reason);
    void signupSuccess();
    void signupFailed(const QString& reason);
    void logoutPerformed();
public slots:
    void logout();

private:
    QSharedPointer<UserRepository> _userRepository;
    QSharedPointer<User> _currentUser;
};

#endif // AUTHSERVICE_H
