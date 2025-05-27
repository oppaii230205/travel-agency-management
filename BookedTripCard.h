#ifndef BOOKEDTRIPCARD_H
#define BOOKEDTRIPCARD_H

#include "TripCard.h"
#include "Booking.h"

class BookedTripCard : public TripCard
{
    Q_OBJECT

public:
    explicit BookedTripCard(const Trip& trip, const Booking& booking, QWidget *parent = nullptr);

signals:
    void cancelClicked(int tripId);

private:
    void setupCancelButton();
    Booking _booking;
};

#endif // BOOKEDTRIPCARD_H
