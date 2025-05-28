/**
 * @file UserService.h
 * @brief Service xử lý logic nghiệp vụ cho quản lý người dùng
 * 
 * Service này cung cấp:
 * - Xử lý logic nghiệp vụ liên quan đến người dùng
 * - Tương tác với UserRepository để thao tác dữ liệu
 * - Xử lý bảo mật và mã hóa thông tin người dùng
 * - Quản lý thông tin cá nhân và avatar
 */

#ifndef _USERSERVICE_H_
#define _USERSERVICE_H_

#include <QObject>
#include <QSharedPointer>
#include "SqlUserRepository.h"
#include "CrypToUtils.h"
#include "constants.h"
#include <QSqlQuery>

/**
 * @brief Service xử lý các thao tác và logic nghiệp vụ liên quan đến người dùng
 * 
 * Class này kế thừa từ QObject và:
 * - Đóng gói các thao tác với repository
 * - Xử lý logic nghiệp vụ và validation
 * - Đảm bảo tính bảo mật của thông tin người dùng
 * - Quản lý phiên làm việc của người dùng
 */
class UserService : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor khởi tạo service quản lý người dùng
     * @param userRepo Con trỏ đến repository xử lý dữ liệu người dùng
     * @param parent QObject cha (mặc định là nullptr)
     */
    explicit UserService(QSharedPointer<UserRepository> userRepo, QObject* parent = nullptr);

    /**
     * @brief Constructor mặc định
     */
    UserService() = default;

    /**
     * @brief Lấy thông tin người dùng theo email
     * @param email Email của người dùng cần tìm
     * @return QSharedPointer<User> con trỏ đến thông tin người dùng, nullptr nếu không tìm thấy
     */
    QSharedPointer<User> getUserByEmail(const QString& email);

    /**
     * @brief Lấy danh sách tất cả người dùng
     * @return QList<User> Danh sách các người dùng trong hệ thống
     */
    QList<User> getAllUsers();

    /**
     * @brief Cập nhật thông tin người dùng
     * @param email Email của người dùng cần cập nhật
     * @param newPassword Mật khẩu mới (sẽ được mã hóa)
     * @param newName Tên mới của người dùng
     * @return true nếu cập nhật thành công, false nếu thất bại
     */
    bool updateUser(const QString& email, const QString& newPassword, const QString& newName);

    /**
     * @brief Xóa một người dùng khỏi hệ thống
     * @param email Email của người dùng cần xóa
     * @return true nếu xóa thành công, false nếu thất bại
     */
    bool deleteUser(const QString& email);

    /**
     * @brief Cập nhật ảnh đại diện của người dùng
     * @param email Email của người dùng cần cập nhật avatar
     * @param avatarUrl URL mới của ảnh đại diện
     * @return true nếu cập nhật thành công, false nếu thất bại
     */
    bool updateUserAvatar(const QString &email, const QString &avatarUrl);

private:
    QSharedPointer<UserRepository> _userRepo; ///< Repository xử lý dữ liệu người dùng
};

#endif // USERSERVICE_H
