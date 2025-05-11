#include "SqlReviewRepository.h"
#include <QSqlError>

SqlReviewRepository::SqlReviewRepository(DatabaseManager& dbManager)
    : _dbManager(dbManager) {}

bool SqlReviewRepository::addReview(const Review& review) {
    if (!review.isValid()) return false;

    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("INSERT INTO reviews (tripId, userEmail, rating, comment, createdAt) "
                  "VALUES (:tripId, :userEmail, :rating, :comment, :createdAt)");
    query.bindValue(":tripId", review.getTripId());
    query.bindValue(":userEmail", review.getUserEmail());
    query.bindValue(":rating", review.getRating());
    query.bindValue(":comment", review.getComment());
    query.bindValue(":createdAt", review.getCreatedAt());

    if (!query.exec()) {
        qCritical() << "Add review failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<Review> SqlReviewRepository::getReviewsByTrip(int tripId) {
    QList<Review> reviews;
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("SELECT * FROM reviews WHERE tripId = :tripId ORDER BY createdAt DESC");
    query.bindValue(":tripId", tripId);

    if (query.exec()) {
        while (query.next()) {
            reviews.append(mapToReview(query));
        }
    }
    return reviews;
}

bool SqlReviewRepository::hasUserReviewed(int tripId, const QString& userEmail) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("SELECT COUNT(*) FROM reviews WHERE tripId = ? AND userEmail = ?");
    query.addBindValue(tripId);
    query.addBindValue(userEmail);

    return query.exec() && query.next() && query.value(0).toInt() > 0;
}

double SqlReviewRepository::getAverageRating(int tripId) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("SELECT AVG(rating) FROM reviews WHERE tripId = ?");
    query.addBindValue(tripId);

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

Review SqlReviewRepository::mapToReview(const QSqlQuery& query) const {
    return Review(
        query.value("tripId").toInt(),
        query.value("userEmail").toString(),
        query.value("rating").toInt(),
        query.value("comment").toString(),
        query.value("createdAt").toDateTime()
        );
}
