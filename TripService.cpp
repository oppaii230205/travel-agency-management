#include "TripService.h"
#include <QDebug>

TripService::TripService(TripRepository* repository, QObject* parent)
    : QObject(parent), _repository(repository) {
    Q_ASSERT(repository != nullptr); // Đảm bảo repository không null
}

QList<Trip> TripService::getAllTrips() {
    try {
        return _repository->getAllTrips();
    } catch (const std::exception& e) {
        emit errorOccurred(tr("Failed to get trips: %1").arg(e.what()));
        return QList<Trip>();
    }
}

Trip TripService::getTripById(int tripId) {
    if (tripId <= 0) {
        emit errorOccurred(tr("Invalid trip ID"));
        return Trip();
    }
    return _repository->getTripById(tripId);
}

bool TripService::createTrip(const Trip& trip) {
    if (!validateTrip(trip)) {
        emit errorOccurred(tr("Invalid trip data"));
        return false;
    }

    if (!isTripNameAvailable(trip.getTripName())) {
        emit errorOccurred(tr("Trip name already exists"));
        return false;
    }

    bool success = _repository->addTrip(trip);
    if (success) {
        emit tripAdded(trip);
    } else {
        emit errorOccurred(tr("Failed to add trip to database"));
    }
    return success;
}

bool TripService::updateTrip(const Trip& trip) {
    if (!validateTrip(trip)) {
        emit errorOccurred(tr("Invalid trip data"));
        return false;
    }

    bool success = _repository->updateTrip(trip);
    if (success) {
        emit tripUpdated(trip);
    } else {
        emit errorOccurred(tr("Failed to update trip"));
    }
    return success;
}

bool TripService::deleteTrip(int tripId) {
    if (tripId <= 0) {
        emit errorOccurred(tr("Invalid trip ID"));
        return false;
    }

    bool success = _repository->deleteTrip(tripId);
    if (success) {
        emit tripDeleted(tripId);
    } else {
        emit errorOccurred(tr("Failed to delete trip"));
    }
    return success;
}

// Business logic implementations
QList<Trip> TripService::findTripsByDifficulty(const QString& difficulty) {
    QList<Trip> allTrips = getAllTrips();
    QList<Trip> filteredTrips;

    for (const Trip& trip : allTrips) {
        if (trip.getDifficulty().compare(difficulty, Qt::CaseInsensitive) == 0) {
            filteredTrips.append(trip);
        }
    }
    return filteredTrips;
}

QList<Trip> TripService::findTripsInPriceRange(int minPrice, int maxPrice) {
    if (minPrice > maxPrice) {
        emit errorOccurred(tr("Invalid price range"));
        return QList<Trip>();
    }

    QList<Trip> allTrips = getAllTrips();
    QList<Trip> filteredTrips;

    for (const Trip& trip : allTrips) {
        int price = trip.getPrice();
        if (price >= minPrice && price <= maxPrice) {
            filteredTrips.append(trip);
        }
    }
    return filteredTrips;
}

bool TripService::isTripNameAvailable(const QString& tripName) const {
    QList<Trip> allTrips = _repository->getAllTrips();
    for (const Trip& trip : allTrips) {
        if (trip.getTripName().compare(tripName, Qt::CaseInsensitive) == 0) {
            return false;
        }
    }
    return true;
}

bool TripService::validateTrip(const Trip& trip) const {
    if (trip.getTripName().isEmpty()) {
        return false;
    }
    if (trip.getDuration() <= 0) {
        return false;
    }
    if (trip.getPrice() < 0) {
        return false;
    }
    return true;
}