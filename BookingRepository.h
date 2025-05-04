#ifndef BOOKINGREPOSITORY_H
#define BOOKINGREPOSITORY_H

#include "Booking.h"
#include <QList>

class BookingRepository {
public:
    virtual ~BookingRepository() = default;

    // Thêm booking mới
    virtual bool addBooking(const Booking& booking) = 0;

    // Lấy danh sách booking theo email user
    virtual QList<Booking> getBookingsByUser(const QString& userEmail) = 0;

    // Kiểm tra user đã booking trip này chưa
    virtual bool hasBooking(const QString& userEmail, int tripId) = 0;

    // Hủy booking (nếu cần)
    virtual bool cancelBooking(const QString& userEmail, int tripId) = 0;
};

#endif // BOOKINGREPOSITORY_H
