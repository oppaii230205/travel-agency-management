#include "authservice.h"

AuthService::AuthService(QSharedPointer<UserRepository> userRepo, QObject *parent)
    : QObject(parent), m_userRepository(userRepo) {}

bool AuthService::login(const QString& email, const QString& password) {
    auto user = m_userRepository->getUserByEmail(email);
    if (!user) {
        emit loginFailed("Email không tồn tại");
        return false;
    }

    if (user->password() != password) {
        emit loginFailed("Mật khẩu không đúng");
        return false;
    }

    m_currentUser = user;
    emit loginSuccess();
    return true;
}

bool AuthService::signup(const QString& email, const QString& password, const QString& name) {
    if (m_userRepository->userExists(email)) {
        emit signupFailed("Email đã được sử dụng");
        return false;
    }

    User newUser(email, password, name, "customer"); // Mặc định role là "customer"!! Cho nhập role thì lỏ vcl :v
    if (!m_userRepository->addUser(newUser)) {
        emit signupFailed("Lỗi khi tạo tài khoản");
        return false;
    }

    emit signupSuccess();
    return true;
}

QSharedPointer<User> AuthService::getCurrentUser() const {
    return m_currentUser;
}
