#ifndef REVIEW_H
#define REVIEW_H

#include <QDateTime>
#include <QString>

class Review {
private:
    int _tripId;
    QString _userEmail;
    int _rating;  // 1-5 sao
    QString _comment;
    QDateTime _createdAt;

public:
    Review() = default;
    Review(int tripId = 0,
           const QString& userEmail = "",
           int rating = 0,
           const QString& comment = "",
           const QDateTime& createdAt = QDateTime::currentDateTime());

    // Getter methods
    int getTripId() const;
    QString getUserEmail() const;
    int getRating() const;
    QString getComment() const;
    QDateTime getCreatedAt() const;

    // Validation
    bool isValid() const;
};

#endif // REVIEW_H
