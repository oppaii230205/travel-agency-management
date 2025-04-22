#ifndef SQLTRIPREPOSITORY_H
#define SQLTRIPREPOSITORY_H

#include "TripRepository.h"
#include "DatabaseManager.h"

class SqlTripRepository : public TripRepository {
public:
    explicit SqlTripRepository(DatabaseManager& dbManager);

    // Triển khai các phương thức từ interface
    QList<Trip> getAllTrips() override;

    Trip getTripById(int id) override;

    bool addTrip(const Trip& trip) override;

    bool updateTrip(const Trip& trip) override;

    bool deleteTrip(int id) override;

private:
    DatabaseManager& _dbManager; // Tham chiếu đến DatabaseManager
};

#endif // SQLTRIPREPOSITORY_H
