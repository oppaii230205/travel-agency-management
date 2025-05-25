#include "SqlDao.h"

SqlDao::SqlDao(DatabaseManager& db) : _dbManager(db) {

    if (!_dbManager.getDatabase().isOpen()) {
        qCritical() << "Database is not open!";
        // Xử lý lỗi tại đây (throw exception hoặc thông báo)
    }
}

QSharedPointer<TripRepository> SqlDao::getTripRepository() const {
    return QSharedPointer<SqlTripRepository>::create(_dbManager);
}

QSharedPointer<UserRepository> SqlDao::getUserRepository() const {
    return QSharedPointer<SqlUserRepository>::create(_dbManager);
}

QSharedPointer<BookingRepository> SqlDao::getBookingRepository() const {
    return QSharedPointer<SqlBookingRepository>::create(_dbManager);
}

QSharedPointer<ReviewRepository> SqlDao::getReviewRepository() const {
    return QSharedPointer<SqlReviewRepository>::create(_dbManager);
}
