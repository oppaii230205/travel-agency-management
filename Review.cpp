#include "Review.h"

Review::Review(int tripId, const QString& userEmail, int rating,
               const QString& comment, const QDateTime& createdAt)
    : _tripId(tripId), _userEmail(userEmail), _rating(rating),
    _comment(comment), _createdAt(createdAt) {}

// Getters
int Review::getTripId() const { return _tripId; }
QString Review::getUserEmail() const { return _userEmail; }
int Review::getRating() const { return _rating; }
QString Review::getComment() const { return _comment; }
QDateTime Review::getCreatedAt() const { return _createdAt; }

// Validate rating (1-5) và bắt buộc có userEmail
bool Review::isValid() const {
    return _rating >= 1 && _rating <= 5 && !_userEmail.isEmpty();
}
