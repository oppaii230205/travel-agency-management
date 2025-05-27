#ifndef BOOKINGSERVICE_H
#define BOOKINGSERVICE_H

#include "BookingRepository.h"
#include "TripService.h"
#include "AuthService.h"

#include "Observable.h"
#include "TripBookedEvent.h"

#include <QObject>

class BookingService : public QObject {
    Q_OBJECT
public:
    explicit BookingService(QSharedPointer<BookingRepository> bookingRepo,
                            QSharedPointer<TripService> tripService,
                            QSharedPointer<AuthService> authService,
                            QObject* parent = nullptr);

    // Đặt chỗ trip
    Q_INVOKABLE bool bookTrip(int tripId);

    // Lấy danh sách booking của user hiện tại
    Q_INVOKABLE QList<Booking> getUserBookings() const;

    // Kiểm tra user đã book trip chưa
    Q_INVOKABLE bool hasUserBooked(int tripId) const;

    // Hủy booking
    Q_INVOKABLE bool cancelBooking(int tripId);

    // Provide access to observable functionality
    void subscribe(QSharedPointer<IObserver> observer);
    
    void unsubscribe(QSharedPointer<IObserver> observer);

signals:
    void bookingSuccess(const QString& message);
    void bookingFailed(const QString& error);
    void bookingsUpdated();

private:
    QSharedPointer<Observable> _observable;
    QSharedPointer<BookingRepository> _bookingRepo;
    QSharedPointer<TripService> _tripService;
    QSharedPointer<AuthService> _authService;
};

#endif // BOOKINGSERVICE_H
