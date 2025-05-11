#ifndef REVIEWSERVICE_H
#define REVIEWSERVICE_H

#include "ReviewRepository.h"
#include "AuthService.h"
#include "BookingService.h"
#include <QObject>

class ReviewService : public QObject {
    Q_OBJECT
public:
    ReviewService(QSharedPointer<ReviewRepository> repo,
                  QSharedPointer<AuthService> authService,
                  QSharedPointer<BookingService> bookingService,
                  QObject* parent = nullptr);

    Q_INVOKABLE bool submitReview(int tripId, int rating, const QString& comment);
    Q_INVOKABLE QList<Review> getTripReviews(int tripId) const;
    Q_INVOKABLE double getTripAverageRating(int tripId) const;
    Q_INVOKABLE bool canUserReview(int tripId) const;

signals:
    void reviewSubmitted();
    void reviewError(const QString& message);

private:
    QSharedPointer<ReviewRepository> _repo;
    QSharedPointer<AuthService> _authService;
    QSharedPointer<BookingService> _bookingService;
};

#endif // REVIEWSERVICE_H
