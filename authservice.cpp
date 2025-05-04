#include "authservice.h"

AuthService::AuthService(QSharedPointer<UserRepository> userRepo, QObject* parent)
    : QObject(parent), _userRepository(userRepo) {}

bool AuthService::login(const QString& email, const QString& password) {
    auto user = _userRepository->getUserByEmail(email);
    if (!user) {
        emit loginFailed("Email không tồn tại");
        return false;
    }

    if (user->password() != password) {
        emit loginFailed("Mật khẩu không đúng");
        return false;
    }

    _currentUser = user;
    emit loginSuccess();
    return true;
}

bool AuthService::signup(const QString& email, const QString& password, const QString& name) {
    if (_userRepository->userExists(email)) {
        emit signupFailed("Email đã được sử dụng");
        return false;
    }

    User newUser(email, password, name, "customer"); // Mặc định role là "customer"!! Cho nhập role thì lỏ vcl :v
    if (!_userRepository->addUser(newUser)) {
        emit signupFailed("Lỗi khi tạo tài khoản");
        return false;
    }

    emit signupSuccess();
    return true;
}

void AuthService::logout() {
    _currentUser.reset();
    emit logoutPerformed();
}

QSharedPointer<User> AuthService::getCurrentUser() const {
    return _currentUser;
}

bool AuthService::hasPermission(const QString& requiredRole) const {
    return _currentUser && _currentUser->role() == requiredRole;
}
