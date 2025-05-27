#ifndef BOOKEDTRIPSDIALOG_H
#define BOOKEDTRIPSDIALOG_H

#include "BaseTripDialog.h"
#include "BookedTripCard.h"
#include "Booking.h"

class BookedTripsDialog : public BaseTripDialog
{
    Q_OBJECT

public:
    explicit BookedTripsDialog(QSharedPointer<TripService> tripService,
                               QSharedPointer<BookingService> bookingService,
                               QSharedPointer<ReviewService> reviewService,
                               QWidget *parent = nullptr);

protected:
    // Implementation of abstract methods from BaseTripDialog
    QString getWindowTitle() const override;
    QList<Trip> getTripsToDisplay() override;
    TripCard* createTripCard(const Trip& trip) override;

    // Hook method implementation
    void onTripCardCreated(TripCard* card, const Trip& trip) override;
    void setupAdditionalUI() override;

private slots:
    void handleCancelClicked(int tripId);
    void onBookingsUpdated();

private:
    QList<Booking> _userBookings;
    Booking findBookingForTrip(int tripId) const;
};

#endif // BOOKEDTRIPSDIALOG_H
