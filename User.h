/**
 * @file User.h
 * @brief Class đại diện cho người dùng trong hệ thống
 * 
 * Class này quản lý:
 * - Thông tin cá nhân của người dùng
 * - Thông tin xác thực (email, mật khẩu)
 * - Phân quyền người dùng
 * - Thông tin hiển thị (avatar)
 */

#ifndef _USER_H_
#define _USER_H_

#include<QString>
#include<QMetaType>

/**
 * @brief Class quản lý thông tin người dùng
 * 
 * Class này lưu trữ và quản lý:
 * - Thông tin đăng nhập (email, mật khẩu)
 * - Thông tin cá nhân (tên, avatar)
 * - Vai trò trong hệ thống
 */
class User {
    private:
        QString _email; ///< Email của người dùng, dùng để đăng nhập
        QString _password; ///< Mật khẩu đã được mã hóa của người dùng
        QString _name; ///< Tên hiển thị của người dùng
        QString _role; ///< Vai trò của người dùng trong hệ thống
        QString _avatarUrl; ///< URL của ảnh đại diện

    public:
        /**
         * @brief Constructor mặc định
         */
        User();

        /**
         * @brief Constructor với đầy đủ thông tin
         * @param email Email của người dùng
         * @param password Mật khẩu của người dùng
         * @param name Tên hiển thị
         * @param role Vai trò trong hệ thống
         * @param avatarUrl URL ảnh đại diện
         */
        User(const QString& email, const QString& password, const QString& name, const QString& role, const QString& avatarUrl);

        /**
         * @brief Lấy email của người dùng
         * @return QString chứa email
         */
        QString email() const;

        /**
         * @brief Lấy mật khẩu đã mã hóa
         * @return QString chứa mật khẩu đã mã hóa
         */
        QString password() const;

        /**
         * @brief Lấy tên hiển thị
         * @return QString chứa tên người dùng
         */
        QString name() const;

        /**
         * @brief Lấy vai trò trong hệ thống
         * @return QString chứa vai trò
         */
        QString role() const;

        /**
         * @brief Lấy URL ảnh đại diện
         * @return QString chứa URL ảnh
         */
        QString avatarUrl() const;

        /**
         * @brief Cập nhật URL ảnh đại diện
         * @param url URL mới của ảnh đại diện
         */
        void setAvatarUrl(const QString &url);

        /**
         * @brief Cập nhật email
         * @param email Email mới
         */
        void setEmail(const QString& email);

        /**
         * @brief Cập nhật mật khẩu
         * @param password Mật khẩu mới (sẽ được mã hóa)
         */
        void setPassord(const QString& password);

        /**
         * @brief Cập nhật tên hiển thị
         * @param name Tên mới
         */
        void setName(const QString& name);

        /**
         * @brief Cập nhật vai trò
         * @param role Vai trò mới
         */
        void setRole(const QString& role);

        /**
         * @brief Kiểm tra tính hợp lệ của thông tin người dùng
         * @return true nếu thông tin hợp lệ, false nếu không hợp lệ
         */
        bool isValid() const;
};

/**
 * @brief Đăng ký kiểu User với hệ thống meta-object của Qt
 */
Q_DECLARE_METATYPE(User)

#endif
