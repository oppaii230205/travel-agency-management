#ifndef BOOKING_H
#define BOOKING_H

#include <QDateTime>
#include <QString>

class Booking {
public:
    Booking(const QString& userEmail = "", int tripId = 0, const QDateTime& bookingDate = QDateTime::currentDateTime())
        : _tripId(tripId), _userEmail(userEmail), _bookingDate(bookingDate) {}

    int getTripId() const { return _tripId; }
    QString getUserEmail() const { return _userEmail; }
    QDateTime getBookingDate() const { return _bookingDate; }

private:
    QString _userEmail;
    int _tripId;
    QDateTime _bookingDate;
};

#endif // BOOKING_H
