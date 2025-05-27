#include "BookingService.h"
#include <QDebug>

BookingService::BookingService(QSharedPointer<BookingRepository> bookingRepo,
                               QSharedPointer<TripService> tripService,
                               QSharedPointer<AuthService> authService,
                               QObject* parent)
    : QObject(parent),
    _bookingRepo(bookingRepo),
    _tripService(tripService),
    _authService(authService) {
        _observable = QSharedPointer<Observable>::create();
    }

bool BookingService::bookTrip(int tripId) {
    // Kiểm tra user đăng nhập
    if (!_authService->getCurrentUser()) {
        emit bookingFailed("User not logged in");
        return false;
    }

    // TODO:
    /*
    // Kiểm tra trip tồn tại
    auto trip = _tripService->getTripById(tripId);
    if (!trip.isValid()) {
        emit bookingFailed("Trip not found");
        return false;
    }

    // Kiểm tra slot còn trống
    if (trip.getCurrentParticipants() >= trip.getMaxGroupSize()) {
        emit bookingFailed("Trip is fully booked");
        return false;
    }
    */

    // Kiểm tra đã booking chưa
    if (hasUserBooked(tripId)) {
        emit bookingFailed("You've already booked this trip");
        return false;
    }

    // Tạo booking mới
    Booking newBooking(
        _authService->getCurrentUser()->email(),
        tripId,
        QDateTime::currentDateTime()
        );

    if (_bookingRepo->addBooking(newBooking)) {
        // TODO:
        /*
        // Cập nhật số lượng participants
        trip.setCurrentParticipants(trip.getCurrentParticipants() + 1);
        _tripService->updateTrip(trip);
        */
        emit bookingSuccess("Booking successful!");
        emit bookingsUpdated();

        TripBookedEvent event(tripId, _authService->getCurrentUser()->email());
        _observable->notify(event); // Notify all observers

        return true;
    }

    emit bookingFailed("Failed to save booking");
    return false;
}

QList<Booking> BookingService::getUserBookings() const {
    if (!_authService->getCurrentUser()) return QList<Booking>();
    return _bookingRepo->getBookingsByUser(_authService->getCurrentUser()->email());
}

bool BookingService::hasUserBooked(int tripId) const {
    if (!_authService->getCurrentUser()) return false;
    return _bookingRepo->hasBooking(
        _authService->getCurrentUser()->email(),
        tripId
        );
}

bool BookingService::cancelBooking(int tripId) {
    if (!_authService->getCurrentUser()) {
        emit bookingFailed("User not logged in");
        return false;
    }

    if (_bookingRepo->cancelBooking(
            _authService->getCurrentUser()->email(),
            tripId
            )) {

        // TODO
        /*
        // Cập nhật số lượng participants
        auto trip = _tripService->getTripById(tripId);
        if (trip.isValid()) {
            trip.setCurrentParticipants(trip.getCurrentParticipants() - 1);
            _tripService->updateTrip(trip);
        }
        */

        emit bookingSuccess("Booking cancelled");
        emit bookingsUpdated();
        return true;
    }

    emit bookingFailed("Failed to cancel booking");
    return false;
}

void BookingService::subscribe(QSharedPointer<IObserver> observer) {
    _observable->subscribe(observer);
}

void BookingService::unsubscribe(QSharedPointer<IObserver> observer) {
    _observable->unsubscribe(observer);
}
