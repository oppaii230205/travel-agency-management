/**
 * @file IDataProvider.h
 * @brief Interface cung cấp truy cập đến các repository trong hệ thống
 * 
 * Interface này định nghĩa:
 * - Điểm truy cập tập trung đến tất cả các repository
 * - Áp dụng Abstract Factory Pattern cho việc tạo repository
 * - Cho phép thay đổi nguồn dữ liệu mà không ảnh hưởng đến code client
 */

#ifndef IDATAPROVIDER_H
#define IDATAPROVIDER_H

#include "TripRepository.h"
#include "UserRepository.h"
#include "BookingRepository.h"
#include "ReviewRepository.h"

/**
 * @brief Interface cung cấp truy cập đến các repository
 * 
 * Interface này triển khai Abstract Factory Pattern và:
 * - Cung cấp các phương thức để lấy repository cụ thể
 * - Cho phép thay đổi implementation của repository (SQL, NoSQL, etc.)
 * - Đảm bảo tính loose coupling giữa data access và business logic
 */
class IDataProvider {
public:
    /**
     * @brief Constructor mặc định
     */
    IDataProvider() = default;

    /**
     * @brief Destructor ảo cho phép kế thừa an toàn
     */
    virtual ~IDataProvider() = default;

    /**
     * @brief Lấy repository quản lý chuyến đi
     * @return QSharedPointer<TripRepository> Con trỏ đến TripRepository
     */
    virtual QSharedPointer<TripRepository> getTripRepository() const = 0;

    /**
     * @brief Lấy repository quản lý người dùng
     * @return QSharedPointer<UserRepository> Con trỏ đến UserRepository
     */
    virtual QSharedPointer<UserRepository> getUserRepository() const = 0;

    /**
     * @brief Lấy repository quản lý đặt chỗ
     * @return QSharedPointer<BookingRepository> Con trỏ đến BookingRepository
     */
    virtual QSharedPointer<BookingRepository> getBookingRepository() const = 0;

    /**
     * @brief Lấy repository quản lý đánh giá
     * @return QSharedPointer<ReviewRepository> Con trỏ đến ReviewRepository
     */
    virtual QSharedPointer<ReviewRepository> getReviewRepository() const = 0;
};

#endif // IDATAPROVIDER_H
