#ifndef SQLBOOKINGREPOSITORY_H
#define SQLBOOKINGREPOSITORY_H

#include "BookingRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>

class SqlBookingRepository : public BookingRepository {
public:
    explicit SqlBookingRepository(DatabaseManager& dbManager);

    bool addBooking(const Booking& booking) override;
    QList<Booking> getBookingsByUser(const QString& userEmail) override;
    bool hasBooking(const QString& userEmail, int tripId) override;
    bool cancelBooking(const QString& userEmail, int tripId) override;

private:
    DatabaseManager& _dbManager;

    // Ánh xạ kết quả query -> Booking object
    Booking mapToBooking(const QSqlQuery& query) const;
};

#endif // SQLBOOKINGREPOSITORY_H
