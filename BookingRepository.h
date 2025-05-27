/**
 * @file BookingRepository.h
 * @brief Interface định nghĩa các thao tác với dữ liệu đặt chỗ
 */

#ifndef BOOKINGREPOSITORY_H
#define BOOKINGREPOSITORY_H

#include "Booking.h"
#include <QList>

/**
 * @brief Interface cung cấp các phương thức truy xuất và quản lý dữ liệu đặt chỗ
 * 
 * Interface này định nghĩa các thao tác cơ bản với dữ liệu đặt chỗ:
 * - Thêm đặt chỗ mới
 * - Truy vấn danh sách đặt chỗ theo người dùng
 * - Kiểm tra trạng thái đặt chỗ
 * - Hủy đặt chỗ
 */
class BookingRepository {
public:
    /**
     * @brief Destructor ảo mặc định
     */
    virtual ~BookingRepository() = default;

    /**
     * @brief Thêm một đặt chỗ mới vào hệ thống
     * @param booking Đối tượng Booking chứa thông tin đặt chỗ
     * @return true nếu thêm thành công, false nếu thất bại
     */
    virtual bool addBooking(const Booking& booking) = 0;

    /**
     * @brief Lấy danh sách đặt chỗ của một người dùng
     * @param userEmail Email của người dùng cần truy vấn
     * @return Danh sách các đặt chỗ của người dùng
     */
    virtual QList<Booking> getBookingsByUser(const QString& userEmail) = 0;

    /**
     * @brief Kiểm tra xem người dùng đã đặt chỗ cho chuyến đi cụ thể chưa
     * @param userEmail Email của người dùng
     * @param tripId ID của chuyến đi cần kiểm tra
     * @return true nếu người dùng đã đặt chỗ, false nếu chưa
     */
    virtual bool hasBooking(const QString& userEmail, int tripId) = 0;

    /**
     * @brief Hủy đặt chỗ của người dùng cho một chuyến đi
     * @param userEmail Email của người dùng
     * @param tripId ID của chuyến đi cần hủy
     * @return true nếu hủy thành công, false nếu thất bại hoặc không tìm thấy đặt chỗ
     */
    virtual bool cancelBooking(const QString& userEmail, int tripId) = 0;
};

#endif // BOOKINGREPOSITORY_H
