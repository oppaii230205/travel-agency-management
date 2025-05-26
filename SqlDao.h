#ifndef SQLDAO_H
#define SQLDAO_H

#include "IDataProvider.h"
#include "DatabaseManager.h"
#include "SqlTripRepository.h"
#include "SqlUserRepository.h"
#include "SqlBookingRepository.h"
#include "SqlReviewRepository.h"

class SqlDao : public IDataProvider {
private:
    DatabaseManager& _dbManager;
public:
    explicit SqlDao(DatabaseManager& db);
    ~SqlDao() = default;

    QSharedPointer<TripRepository> getTripRepository() const override;

    QSharedPointer<UserRepository> getUserRepository() const override;

    QSharedPointer<BookingRepository> getBookingRepository() const override;

    QSharedPointer<ReviewRepository> getReviewRepository() const override;
};

#endif // SQLDAO_H
