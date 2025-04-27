#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "Trip.h"
#include "SqlTripRepository.h"

SqlTripRepository::SqlTripRepository(DatabaseManager& dbManager) : _dbManager(dbManager) {
    if (!_dbManager.getDatabase().isOpen()) {
        qCritical() << "Database is not open!";
        // Xử lý lỗi tại đây (throw exception hoặc thông báo)
    }
}

QList<Trip> SqlTripRepository::getAllTrips() {
    QList<Trip> trips;
    QSqlQuery query("SELECT * FROM TRIP", _dbManager.getDatabase());
    
    while (query.next()) {
        Trip trip(
            query.value("tripId").toInt(),
            query.value("tripName").toString(),
            query.value("duration").toInt(),
            query.value("maxGroupSize").toInt(),
            query.value("difficulty").toString(),
            query.value("price").toInt(),
            query.value("summary").toString(),
            query.value("description").toString()
            // Thêm các trường khác nếu cần thiết
        );
        trips.append(trip);
    }
    return trips;
}

Trip SqlTripRepository::getTripById(int tripId) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("SELECT * FROM TRIP WHERE tripId = :tripId");
    query.bindValue(":tripId", tripId);
    
    if (query.exec() && query.next()) {
        return Trip(
            query.value("tripId").toInt(),
            query.value("tripName").toString(),
            query.value("duration").toInt(),
            query.value("maxGroupSize").toInt(),
            query.value("difficulty").toString(),
            query.value("price").toInt(),
            query.value("summary").toString(),
            query.value("description").toString()
            // Thêm các trường khác nếu cần thiết
        );
    }
    return Trip(); // Trả về trip mặc định nếu không tìm thấy
}

bool SqlTripRepository::addTrip(const Trip& trip) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("INSERT TRIP (tripName, duration, maxGroupSize, difficulty, price, summary, description) VALUES (:tripName, :duration, :maxGroupSize, :difficulty, :price, :summary, :description)");
    // query.bindValue(":tripId", trip.getTripId());
    query.bindValue(":tripName", trip.getTripName());
    query.bindValue(":duration", trip.getDuration());
    query.bindValue(":maxGroupSize", trip.getMaxGroupSize());
    query.bindValue(":difficulty", trip.getDifficulty());
    query.bindValue(":price", trip.getPrice());
    query.bindValue(":summary", trip.getSummary());
    query.bindValue(":description", trip.getDescription());
    
    // Look before you leap: check if the SQL query is executed successfully
    if (!query.exec()) {
        qDebug() << "Add trip error:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool SqlTripRepository::updateTrip(const Trip& trip) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("UPDATE TRIP SET tripName = :tripName, duration = :duration, maxGroupSize = :maxGroupSize, difficulty = :difficulty, price = :price, summary = :summary, decription = :description WHERE tripId = :tripId");
    query.bindValue(":tripId", trip.getTripId());
    query.bindValue(":tripName", trip.getTripName());
    query.bindValue(":duration", trip.getDuration());
    query.bindValue(":maxGroupSize", trip.getMaxGroupSize());
    query.bindValue(":difficulty", trip.getDifficulty());
    query.bindValue(":price", trip.getPrice());
    query.bindValue(":summary", trip.getSummary());
    query.bindValue(":description", trip.getDescription());

    
    // Look before you leap: check if the SQL query is executed successfully
    if (!query.exec()) {
        qDebug() << "Add trip error:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool SqlTripRepository::deleteTrip(int tripId) {
    QSqlQuery query(_dbManager.getDatabase());
    query.prepare("DELETE FROM TRIP WHERE tripId = :tripId");
    query.bindValue(":tripId", tripId);
    
    return query.exec();
}
