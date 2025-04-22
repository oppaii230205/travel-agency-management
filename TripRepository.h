#ifndef TRIPREPOSITORY_H
#define TRIPREPOSITORY_H

#include <QList>
#include "Trip.h"

class TripRepository {
public:
    virtual ~TripRepository() = default;
    virtual QList<Trip> getAllTrips() = 0;
    virtual Trip getTripById(int id) = 0;
    virtual bool addTrip(const Trip& trip) = 0;
    virtual bool updateTrip(const Trip& trip) = 0;
    virtual bool deleteTrip(int id) = 0;
};

#endif // TRIPREPOSITORY_H
