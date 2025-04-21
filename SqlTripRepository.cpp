#include "SqlTripRepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SqlTripRepository::SqlTripRepository(DatabaseManager& dbManager)
    : dbManager(dbManager) {}

QList<Trip> SqlTripRepository::getAllTrips() {
    QList<Trip> trips;
    QSqlQuery query("SELECT * FROM travelagencytrips_tb", dbManager.getDatabase());

    while (query.next()) {
        trips.append(Trip(
            query.value("t_id").toInt(),
            query.value("t_trip").toString()
            ));
    }
    return trips;
}

bool SqlTripRepository::addTrip(const Trip& trip) {
    QSqlQuery query(dbManager.getDatabase());
    query.prepare("INSERT INTO travelagencytrips_tb (t_trip) VALUES (?)");
    query.addBindValue(trip.getName());
    return query.exec();
}
