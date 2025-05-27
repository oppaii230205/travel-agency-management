/**
 * @file Booking.h
 * @brief Class đại diện cho một đặt chỗ trong hệ thống
 */

#ifndef BOOKING_H
#define BOOKING_H

#include <QDateTime>
#include <QString>

/**
 * @brief Class quản lý thông tin về một đặt chỗ
 * 
 * Class này lưu trữ các thông tin cơ bản của một đặt chỗ:
 * - Email của người đặt
 * - ID của chuyến đi được đặt
 * - Thời gian đặt chỗ
 */
class Booking {
public:
    /**
     * @brief Constructor cho đối tượng Booking
     * 
     * @param userEmail Email của người đặt chỗ (mặc định là chuỗi rỗng)
     * @param tripId ID của chuyến đi được đặt (mặc định là 0)
     * @param bookingDate Thời gian đặt chỗ (mặc định là thời gian hiện tại)
     */
    Booking(const QString& userEmail = "", int tripId = 0, const QDateTime& bookingDate = QDateTime::currentDateTime());

    /**
     * @brief Lấy ID của chuyến đi được đặt
     * @return ID của chuyến đi
     */
    int getTripId() const;

    /**
     * @brief Lấy email của người đặt chỗ
     * @return Email của người đặt
     */
    QString getUserEmail() const;

    /**
     * @brief Lấy thời gian đặt chỗ
     * @return Thời gian đặt chỗ dưới dạng QDateTime
     */
    QDateTime getBookingDate() const;

private:
    QString _userEmail;    ///< Email của người đặt chỗ
    int _tripId;          ///< ID của chuyến đi được đặt
    QDateTime _bookingDate; ///< Thời gian đặt chỗ
};

#endif // BOOKING_H
