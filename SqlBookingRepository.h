/**
 * @file SqlBookingRepository.h
 * @brief Triển khai BookingRepository interface sử dụng SQL database
 * 
 * Class này cung cấp các thao tác với booking thông qua:
 * - Kết nối SQL database
 * - Thực thi các câu query
 * - Ánh xạ kết quả sang đối tượng Booking
 * - Xử lý lỗi database
 */

#ifndef SQLBOOKINGREPOSITORY_H
#define SQLBOOKINGREPOSITORY_H

#include "BookingRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>

/**
 * @brief Class triển khai BookingRepository sử dụng SQL database
 * 
 * Class này:
 * - Kế thừa interface BookingRepository
 * - Sử dụng DatabaseManager để kết nối database
 * - Thực hiện các thao tác CRUD với bảng bookings
 * - Xử lý các lỗi liên quan đến database
 */
class SqlBookingRepository : public BookingRepository {
public:
    /**
     * @brief Constructor với DatabaseManager
     * 
     * @param dbManager Tham chiếu đến DatabaseManager singleton
     */
    explicit SqlBookingRepository(DatabaseManager& dbManager);

    /**
     * @brief Thêm một booking mới vào database
     * 
     * @param booking Đối tượng Booking cần thêm
     * @return true nếu thêm thành công
     * @return false nếu có lỗi (ví dụ: vi phạm ràng buộc unique)
     */
    bool addBooking(const Booking& booking) override;

    /**
     * @brief Lấy danh sách booking của một người dùng
     * 
     * @param userEmail Email của người dùng cần lấy booking
     * @return QList<Booking> Danh sách các booking
     * 
     * @note Trả về danh sách rỗng nếu không tìm thấy booking nào
     */
    QList<Booking> getBookingsByUser(const QString& userEmail) override;

    /**
     * @brief Kiểm tra xem người dùng đã đặt chuyến đi chưa
     * 
     * @param userEmail Email của người dùng
     * @param tripId ID của chuyến đi
     * @return true nếu người dùng đã đặt chuyến đi này
     * @return false nếu chưa đặt hoặc có lỗi xảy ra
     */
    bool hasBooking(const QString& userEmail, int tripId) override;

    /**
     * @brief Hủy booking của người dùng
     * 
     * @param userEmail Email của người dùng
     * @param tripId ID của chuyến đi cần hủy
     * @return true nếu hủy thành công
     * @return false nếu không tìm thấy booking hoặc có lỗi
     */
    bool cancelBooking(const QString& userEmail, int tripId) override;

private:
    DatabaseManager& _dbManager;  ///< Tham chiếu đến DatabaseManager singleton

    /**
     * @brief Ánh xạ kết quả query thành đối tượng Booking
     * 
     * @param query Query đã thực thi thành công
     * @return Booking Đối tượng booking được tạo từ dữ liệu query
     * 
     * @note Query phải chứa đầy đủ các trường của bảng bookings
     */
    Booking mapToBooking(const QSqlQuery& query) const;
};

#endif // SQLBOOKINGREPOSITORY_H
