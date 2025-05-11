#include "ReviewService.h"

ReviewService::ReviewService(QSharedPointer<ReviewRepository> repo,
                             QSharedPointer<AuthService> authService,
                             QSharedPointer<BookingService> bookingService,
                             QObject* parent)
    : QObject(parent), _repo(repo), _authService(authService),
    _bookingService(bookingService) {}

bool ReviewService::submitReview(int tripId, int rating, const QString& comment) {
    // Kiểm tra user đã đăng nhập
    if (!_authService->getCurrentUser()) {
        emit reviewError("Please login to submit a review");
        return false;
    }

    // Kiểm tra user đã booking trip này chưa
    if (!_bookingService->hasUserBooked(tripId)) {
        emit reviewError("You must book this trip before reviewing");
        return false;
    }

    // Kiểm tra đã review chưa
    if (_repo->hasUserReviewed(tripId, _authService->getCurrentUser()->email())) {
        emit reviewError("You've already reviewed this trip");
        return false;
    }

    // Tạo review
    Review newReview(tripId,
                     _authService->getCurrentUser()->email(),
                     rating,
                     comment);

    if (_repo->addReview(newReview)) {
        emit reviewSubmitted();
        return true;
    }

    emit reviewError("Failed to submit review");
    return false;
}

QList<Review> ReviewService::getTripReviews(int tripId) const {
    return _repo->getReviewsByTrip(tripId);
}

double ReviewService::getTripAverageRating(int tripId) const {
    return _repo->getAverageRating(tripId);
}

bool ReviewService::canUserReview(int tripId) const {
    if (!_authService->getCurrentUser()) return false;
    return _bookingService->hasUserBooked(tripId) &&
           !_repo->hasUserReviewed(tripId, _authService->getCurrentUser()->email());
}
