#ifndef TRIP_H
#define TRIP_H

#include <QString>
#include <QDate>

class Trip {
private:
    int _tripId;
    QString _tripName;
    int _duration; // in days
    int _maxGroupSize;
    QString _difficulty;
    int _price;
    QString _summary;
    QString _description;
    QString _imagePath;

public:
    Trip(); // Default constructor
    Trip(int tripId, const QString& tripName, int duration, int maxGroupSize, const QString& difficulty,
         int price, const QString& summary, const QString& description, const QString& _imagePath);

    int getTripId() const;
    QString getTripName() const;
    int getDuration() const;
    int getMaxGroupSize() const;
    QString getDifficulty() const;
    int getPrice() const;
    QString getSummary() const;
    QString getDescription() const;
    QString getImagePath() const;

    void setTripName(const QString& tripName);
    void setDuration(int duration);
    void setMaxGroupSize(int maxGroupSize);
    void setDifficulty(const QString& difficulty);
    void setPrice(int price);
    void setSummary(const QString& summary);
    void setDescription(const QString& description);
    void setImagePath(const QString& imagePath);
};

#endif // TRIP_H
