#include "SqlBookingRepository.h"

SqlBookingRepository::SqlBookingRepository(DatabaseManager& dbManager)
    : _dbManager(dbManager) {}

bool SqlBookingRepository::addBooking(const Booking& booking) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("INSERT INTO bookings (userEmail, tripId, bookingDate) "
                  "VALUES (:user_email, :trip_id, :booking_date)");
    query.bindValue(":user_email", booking.getUserEmail());
    query.bindValue(":trip_id", booking.getTripId());
    query.bindValue(":booking_date", booking.getBookingDate());

    if (!query.exec()) {
        qCritical() << "Booking failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<Booking> SqlBookingRepository::getBookingsByUser(const QString& userEmail) {
    QList<Booking> bookings;
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("SELECT * FROM bookings WHERE userEmail = :user_email");
    query.bindValue(":user_email", userEmail);

    if (query.exec()) {
        while (query.next()) {
            bookings.append(mapToBooking(query));
        }
    } else {
        qWarning() << "Failed to fetch bookings:" << query.lastError().text();
    }
    return bookings;
}

bool SqlBookingRepository::hasBooking(const QString& userEmail, int tripId) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("SELECT COUNT(*) FROM bookings "
                  "WHERE userEmail = :user_email AND tripId = :trip_id");
    query.bindValue(":user_email", userEmail);
    query.bindValue(":trip_id", tripId);

    return query.exec() && query.next() && query.value(0).toInt() > 0;
}

bool SqlBookingRepository::cancelBooking(const QString& userEmail, int tripId) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("DELETE FROM bookings "
                  "WHERE userEmail = :user_email AND tripId = :trip_id");
    query.bindValue(":user_email", userEmail);
    query.bindValue(":trip_id", tripId);

    return query.exec() && query.numRowsAffected() > 0;
}

Booking SqlBookingRepository::mapToBooking(const QSqlQuery& query) const {
    return Booking(
        query.value("userEmail").toString(),
        query.value("tripId").toInt(),
        query.value("bookingDate").toDateTime()
        );
}
