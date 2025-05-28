#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "UserRepository.h"
#include <QObject>
#include <QSharedPointer>
#include "CrypToUtils.h"
#include "constants.h"

/**
 * @brief Service xử lý các thao tác xác thực người dùng
 * 
 * Class này cung cấp các chức năng:
 * - Đăng nhập và đăng xuất người dùng
 * - Đăng ký tài khoản mới
 * - Kiểm tra quyền truy cập
 * - Quản lý thông tin người dùng hiện tại
 */
class AuthService : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor với repository người dùng
     * @param userRepo Con trỏ thông minh đến UserRepository
     * @param parent QObject cha (mặc định là nullptr)
     */
    explicit AuthService(QSharedPointer<UserRepository> userRepo, QObject* parent = nullptr);

    /**
     * @brief Constructor mặc định
     */
    AuthService() = default;

    /**
     * @brief Xác thực và đăng nhập người dùng
     * @param email Email của người dùng
     * @param password Mật khẩu của người dùng
     * @return true nếu đăng nhập thành công, false nếu thất bại
     */
    bool login(const QString& email, const QString& password);

    /**
     * @brief Đăng ký tài khoản mới
     * @param email Email của người dùng mới
     * @param password Mật khẩu của người dùng mới
     * @param name Tên của người dùng mới
     * @return true nếu đăng ký thành công, false nếu thất bại
     */
    bool signup(const QString& email, const QString& password, const QString& name);

    /**
     * @brief Lấy thông tin người dùng hiện tại
     * @return Con trỏ thông minh đến đối tượng User hiện tại, nullptr nếu chưa đăng nhập
     */
    QSharedPointer<User> getCurrentUser() const;

    /**
     * @brief Kiểm tra quyền truy cập của người dùng hiện tại
     * @param requiredRole Quyền cần kiểm tra
     * @return true nếu người dùng có quyền, false nếu không
     */
    bool hasPermission(const QString& requiredRole) const;

signals:
    /**
     * @brief Signal được phát khi đăng nhập thành công
     */
    void loginSuccess();

    /**
     * @brief Signal được phát khi đăng nhập thất bại
     * @param reason Lý do thất bại
     */
    void loginFailed(const QString& reason);

    /**
     * @brief Signal được phát khi đăng ký thành công
     */
    void signupSuccess();

    /**
     * @brief Signal được phát khi đăng ký thất bại
     * @param reason Lý do thất bại
     */
    void signupFailed(const QString& reason);

    /**
     * @brief Signal được phát khi đăng xuất hoàn tất
     */
    void logoutPerformed();

public slots:
    /**
     * @brief Slot xử lý đăng xuất người dùng
     * 
     * Xóa thông tin người dùng hiện tại và phát signal logoutPerformed
     */
    void logout();

private:
    QSharedPointer<UserRepository> _userRepository; ///< Repository quản lý dữ liệu người dùng
    QSharedPointer<User> _currentUser;             ///< Thông tin người dùng đang đăng nhập
};

#endif // AUTHSERVICE_H
