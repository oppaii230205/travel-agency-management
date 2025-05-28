/**
 * @file DatabaseManager.h
 * @brief Singleton class quản lý kết nối và tương tác với cơ sở dữ liệu
 */

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

/**
 * @brief Class quản lý kết nối cơ sở dữ liệu theo mẫu Singleton
 * 
 * Class này đảm bảo chỉ có một kết nối duy nhất đến cơ sở dữ liệu
 * trong toàn bộ ứng dụng. Sử dụng mẫu thiết kế Singleton để:
 * - Quản lý kết nối cơ sở dữ liệu một cách tập trung
 * - Tránh tạo nhiều kết nối không cần thiết
 * - Đảm bảo tính nhất quán của dữ liệu
 */
class DatabaseManager {
private:
    QSqlDatabase _db;                      ///< Đối tượng kết nối cơ sở dữ liệu
    static DatabaseManager* _instance;      ///< Con trỏ đến instance duy nhất của DatabaseManager

    /**
     * @brief Constructor riêng tư của DatabaseManager
     * 
     * Constructor này được đặt ở private để đảm bảo không thể tạo
     * instance mới của DatabaseManager từ bên ngoài class.
     */
    DatabaseManager();

public:
    /**
     * @brief Destructor
     * 
     * Giải phóng tài nguyên và đóng kết nối cơ sở dữ liệu
     */
    ~DatabaseManager();

    /**
     * @brief Lấy instance duy nhất của DatabaseManager
     * 
     * Phương thức static này đảm bảo chỉ có một instance của
     * DatabaseManager được tạo và sử dụng trong toàn bộ ứng dụng.
     * 
     * @return Tham chiếu đến instance duy nhất của DatabaseManager
     */
    static DatabaseManager& getInstance();

    /**
     * @brief Thiết lập kết nối đến cơ sở dữ liệu
     * 
     * Phương thức này thực hiện:
     * - Cấu hình thông số kết nối
     * - Mở kết nối đến cơ sở dữ liệu
     * - Kiểm tra tính hợp lệ của kết nối
     * 
     * @return true nếu kết nối thành công, false nếu thất bại
     */
    bool connect();

    /**
     * @brief Lấy đối tượng QSqlDatabase để thực hiện các truy vấn
     * 
     * @return Tham chiếu đến đối tượng QSqlDatabase đang quản lý kết nối
     */
    QSqlDatabase& getDatabase();
};

#endif // DATABASEMANAGER_H
