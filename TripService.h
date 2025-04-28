#ifndef TRIPSERVICE_H
#define TRIPSERVICE_H

#include <QObject>
#include <QList>
#include "Trip.h"
#include "TripRepository.h"

class TripService : public QObject
{
    Q_OBJECT

public:
    explicit TripService(TripRepository* repository, QObject* parent = nullptr);

    // Basic CRUD operations
    QList<Trip> getAllTrips();
    Trip getTripById(int tripId);
    bool createTrip(const Trip& trip);
    bool updateTrip(const Trip& trip);
    bool deleteTrip(int tripId);

    // Business logic methods
    QList<Trip> findTripsByDifficulty(const QString& difficulty);
    QList<Trip> findTripsInPriceRange(int minPrice, int maxPrice);
    bool isTripNameAvailable(const QString& tripName) const;

signals:
    void tripAdded(const Trip& newTrip);
    void tripUpdated(const Trip& updatedTrip);
    void tripDeleted(int tripId);
    void errorOccurred(const QString& errorMessage);

private:
    TripRepository* _repository;
    bool validateTrip(const Trip& trip) const;
};

#endif // TRIPSERVICE_H