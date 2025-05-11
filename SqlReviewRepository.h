#ifndef SQLREVIEWREPOSITORY_H
#define SQLREVIEWREPOSITORY_H

#include "ReviewRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>

class SqlReviewRepository : public ReviewRepository {
public:
    explicit SqlReviewRepository(DatabaseManager& dbManager);

    bool addReview(const Review& review) override;
    QList<Review> getReviewsByTrip(int tripId) override;
    bool hasUserReviewed(int tripId, const QString& userEmail) override;
    double getAverageRating(int tripId) override;

private:
    DatabaseManager& _dbManager;
    Review mapToReview(const QSqlQuery& query) const;
};

#endif // SQLREVIEWREPOSITORY_H
