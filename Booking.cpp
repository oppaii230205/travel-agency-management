#include "Booking.h"

Booking::Booking(const QString& userEmail, int tripId, const QDateTime& bookingDate)
    : _tripId(tripId), _userEmail(userEmail), _bookingDate(bookingDate) {}

int Booking::getTripId() const { return _tripId; }
QString Booking::getUserEmail() const { return _userEmail; }
QDateTime Booking::getBookingDate() const { return _bookingDate; }
