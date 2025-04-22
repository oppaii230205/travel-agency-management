#ifndef SQLTRIPREPOSITORY_H
#define SQLTRIPREPOSITORY_H

#include "TripRepository.h"
#include "DatabaseManager.h"

class SqlTripRepository : public TripRepository {
public:
    explicit SqlTripRepository(DatabaseManager& dbManager);

    // Triển khai các phương thức từ interface
    QList<Trip> getAllTrips() override;
    bool addTrip(const Trip& trip) override;
    // ... các phương thức khác

private:
    DatabaseManager& dbManager; // Tham chiếu đến DatabaseManager
};

#endif // SQLTRIPREPOSITORY_H
