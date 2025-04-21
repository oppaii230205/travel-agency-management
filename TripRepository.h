#ifndef TRIPREPOSITORY_H
#define TRIPREPOSITORY_H

#include <QList>
#include "Trip.h"

class TripRepository {
public:
    virtual ~TripRepository() = default;
    virtual QList<Trip> getAllTrips() = 0;
    virtual bool addTrip(const Trip& trip) = 0;
    // ... các phương thức thuần ảo khác
};

#endif // TRIPREPOSITORY_H
