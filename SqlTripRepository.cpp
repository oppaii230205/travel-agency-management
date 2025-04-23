#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "Trip.h"
#include "SqlTripRepository.h"

SqlTripRepository::SqlTripRepository(DatabaseManager& dbManager) : _dbManager(dbManager) {
    // Khởi tạo kết nối đến cơ sở dữ liệu nếu cần thiết
    // if (!_dbManager.isConnected()) {
    //     _dbManager.connectToDatabase();
    // }
}

QList<Trip> SqlTripRepository::getAllTrips() {
    QList<Trip> trips;
    QSqlQuery query("SELECT * FROM travelagencytrips_tb");
    
    while (query.next()) {
        Trip trip(
            query.value("tripid").toInt(),
            query.value("tripname").toString(),
            query.value("duration").toInt(),
            query.value("maxgroupsize").toInt(),
            query.value("difficulty").toString(),
            query.value("price").toInt(),
            query.value("summary").toString(),
            query.value("description").toString()
        );
        trips.append(trip);
    }
    return trips;
}

Trip SqlTripRepository::getTripById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM travelagencytrips_tb WHERE t_id = :id");
    query.bindValue(":id", id);
    
    if (query.exec() && query.next()) {
        return Trip(
            query.value("tripid").toInt(),
            query.value("tripname").toString(),
            query.value("duration").toInt(),
            query.value("maxgroupsize").toInt(),
            query.value("difficulty").toString(),
            query.value("price").toInt(),
            query.value("summary").toString(),
            query.value("description").toString()
        );
    }
    return Trip(); // Trả về trip mặc định nếu không tìm thấy
}

bool SqlTripRepository::addTrip(const Trip& trip) {
    QSqlQuery query;
    query.prepare("INSERT INTO travelagencytrips_tb (t_trip) VALUES (:name)");
    query.bindValue(":name", trip.getTripName());
    
    if (!query.exec()) {
        qDebug() << "Add trip error:" << query.lastError().text();
        return false;
    }
    return true;
}

bool SqlTripRepository::updateTrip(const Trip& trip)  {
    QSqlQuery query;
    query.prepare("UPDATE travelagencytrips_tb SET t_trip = :name WHERE t_id = :id");
    query.bindValue(":name", trip.getTripName());
    query.bindValue(":id", trip.getTripId());
    
    return query.exec();
}

bool SqlTripRepository::deleteTrip(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM travelagencytrips_tb WHERE t_id = :id");
    query.bindValue(":id", id);
    
    return query.exec();
}
