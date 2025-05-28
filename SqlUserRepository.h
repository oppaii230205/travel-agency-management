/**
 * @file SqlUserRepository.h
 * @brief Triển khai UserRepository interface sử dụng SQL database
 * 
 * Class này cung cấp các thao tác với người dùng thông qua:
 * - Kết nối SQL database
 * - Thực thi các câu query
 * - Ánh xạ kết quả sang đối tượng User
 * - Quản lý thông tin người dùng
 */

#ifndef _SQLUSERREPOSITORY_H_
#define _SQLUSERREPOSITORY_H_

#include "UserRepository.h"
#include "DatabaseManager.h"

/**
 * @brief Class triển khai UserRepository sử dụng SQL database
 * 
 * Class này:
 * - Kế thừa interface UserRepository
 * - Sử dụng DatabaseManager để kết nối database
 * - Thực hiện các thao tác CRUD với bảng users
 * - Quản lý thông tin và ảnh đại diện người dùng
 */
class SqlUserRepository: public UserRepository {
    private:
        DatabaseManager& _dbManager;  ///< Tham chiếu đến DatabaseManager singleton

    public:
        /**
         * @brief Constructor với DatabaseManager
         * 
         * @param dbManager Tham chiếu đến DatabaseManager singleton
         */
        explicit SqlUserRepository(DatabaseManager& dbManager);

        /**
         * @brief Thêm một người dùng mới vào database
         * 
         * @param user Đối tượng User cần thêm
         * @return true nếu thêm thành công
         * @return false nếu có lỗi (ví dụ: email đã tồn tại)
         */
        bool addUser(const User& user);

        /**
         * @brief Lấy thông tin người dùng theo email
         * 
         * @param email Email của người dùng cần tìm
         * @return QSharedPointer<User> Con trỏ thông minh đến đối tượng User
         * 
         * @note Trả về nullptr nếu không tìm thấy người dùng
         */
        QSharedPointer<User> getUserByEmail(const QString& email);

        /**
         * @brief Lấy danh sách tất cả người dùng
         * 
         * @return QList<User> Danh sách các người dùng
         * 
         * @note Trả về danh sách rỗng nếu không có người dùng nào
         */
        QList<User> getAllUsers();

        /**
         * @brief Cập nhật thông tin người dùng
         * 
         * @param user Đối tượng User chứa thông tin cần cập nhật
         * @return true nếu cập nhật thành công
         * @return false nếu không tìm thấy người dùng hoặc có lỗi
         */
        bool updateUser(const User& user);

        /**
         * @brief Xóa người dùng khỏi database
         * 
         * @param email Email của người dùng cần xóa
         * @return true nếu xóa thành công
         * @return false nếu không tìm thấy người dùng hoặc có lỗi
         * 
         * @note Việc xóa có thể thất bại nếu có các ràng buộc khóa ngoại
         */
        bool deleteUser(const QString& email);

        /**
         * @brief Kiểm tra sự tồn tại của người dùng
         * 
         * @param email Email cần kiểm tra
         * @return true nếu email đã tồn tại trong database
         * @return false nếu email chưa được sử dụng
         */
        bool userExists(const QString& email);

        /**
         * @brief Cập nhật URL ảnh đại diện của người dùng
         * 
         * @param email Email của người dùng
         * @param avatarUrl URL mới của ảnh đại diện
         * @return true nếu cập nhật thành công
         * @return false nếu không tìm thấy người dùng hoặc có lỗi
         */
        bool updateUserAvatar(const QString &email, const QString &avatarUrl);

    private:
        /**
         * @brief Ánh xạ kết quả query thành đối tượng User
         * 
         * @param query Query đã thực thi thành công
         * @return User Đối tượng user được tạo từ dữ liệu query
         * 
         * @note Query phải chứa đầy đủ các trường của bảng users
         */
        User mapResultToUser(const QSqlQuery& query) const;

        /**
         * @brief Thực thi một câu query SQL
         * 
         * @param query Query cần thực thi
         * @return true nếu thực thi thành công
         * @return false nếu có lỗi xảy ra
         * 
         * @note Phương thức này xử lý các lỗi SQL và log chúng
         */
        bool executeQuery(QSqlQuery& query) const;
};

#endif
