/**
 * @file UserRepository.h
 * @brief Interface định nghĩa các thao tác với dữ liệu người dùng
 * 
 * Interface này định nghĩa các phương thức cơ bản để:
 * - Quản lý tài khoản người dùng
 * - Truy xuất thông tin người dùng
 * - Cập nhật thông tin cá nhân
 * - Xác thực người dùng
 */

#ifndef _USERREPOSITORY_H_
#define _USERREPOSITORY_H_

#include "User.h"
#include <QList>
#include <QSharedPointer>

/**
 * @brief Interface cho repository quản lý dữ liệu người dùng
 * 
 * Interface này định nghĩa các phương thức ảo thuần túy để:
 * - Thực hiện các thao tác CRUD với dữ liệu người dùng
 * - Kiểm tra sự tồn tại của tài khoản
 * - Quản lý thông tin cá nhân và avatar
 * - Cho phép thay đổi implementation của repository (ví dụ: SQL, NoSQL, File,...)
 */
class UserRepository {
    public:
        /**
         * @brief Destructor ảo mặc định
         */
        virtual ~UserRepository() = default;

        /**
         * @brief Thêm một người dùng mới vào hệ thống
         * @param user Thông tin người dùng cần thêm
         * @return true nếu thêm thành công, false nếu thất bại
         */
        virtual bool addUser(const User& user) = 0;

        /**
         * @brief Lấy thông tin người dùng theo email
         * @param email Email của người dùng cần tìm
         * @return QSharedPointer<User> con trỏ đến thông tin người dùng, nullptr nếu không tìm thấy
         */
        virtual QSharedPointer<User> getUserByEmail(const QString& email) = 0;

        /**
         * @brief Lấy danh sách tất cả người dùng
         * @return QList<User> Danh sách các người dùng
         */
        virtual QList<User> getAllUsers() = 0;

        /**
         * @brief Cập nhật thông tin người dùng
         * @param user Thông tin người dùng cần cập nhật (email phải tồn tại)
         * @return true nếu cập nhật thành công, false nếu thất bại
         */
        virtual bool updateUser(const User& user) = 0;

        /**
         * @brief Xóa một người dùng khỏi hệ thống
         * @param email Email của người dùng cần xóa
         * @return true nếu xóa thành công, false nếu thất bại
         */
        virtual bool deleteUser(const QString& email) = 0;

        /**
         * @brief Kiểm tra sự tồn tại của email trong hệ thống
         * @param email Email cần kiểm tra
         * @return true nếu email đã tồn tại, false nếu chưa tồn tại
         */
        virtual bool userExists(const QString& email) = 0;

        /**
         * @brief Cập nhật ảnh đại diện của người dùng
         * @param email Email của người dùng cần cập nhật avatar
         * @param avatarUrl URL mới của ảnh đại diện
         * @return true nếu cập nhật thành công, false nếu thất bại
         */
        virtual bool updateUserAvatar(const QString &email, const QString &avatarUrl) = 0;
};

#endif
