#ifndef REVIEWREPOSITORY_H
#define REVIEWREPOSITORY_H

#include "Review.h"
#include <QList>

class ReviewRepository {
public:
    ReviewRepository() = default;
    virtual ~ReviewRepository() = default;

    virtual bool addReview(const Review& review) = 0;
    virtual QList<Review> getReviewsByTrip(int tripId) = 0;
    virtual bool hasUserReviewed(int tripId, const QString& userEmail) = 0;
    virtual double getAverageRating(int tripId) = 0;
};

#endif // IREVIEWREPOSITORY_H
