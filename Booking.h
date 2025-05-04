#ifndef BOOKING_H
#define BOOKING_H

#include <QDateTime>
#include <QString>

class Booking {
public:
    Booking(const QString& userEmail = "", int tripId = 0, const QDateTime& bookingDate = QDateTime::currentDateTime());

    int getTripId() const;
    QString getUserEmail() const;
    QDateTime getBookingDate() const;

private:
    QString _userEmail;
    int _tripId;
    QDateTime _bookingDate;
};

#endif // BOOKING_H
