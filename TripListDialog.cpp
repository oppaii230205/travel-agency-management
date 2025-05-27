#include "TripListDialog.h"
#include "CustomMessageBox.h"

TripListDialog::TripListDialog(QSharedPointer<TripService> tripService,
                               QSharedPointer<BookingService> bookingService,
                               QSharedPointer<ReviewService> reviewService,
                               QWidget *parent)
    : BaseTripDialog(tripService, bookingService, reviewService, parent)
{
    // Constructor now just calls parent constructor
    // Initialization will happen in showEvent via initializeDialog()
}

QString TripListDialog::getWindowTitle() const
{
    return "Available Trips";
}

QList<Trip> TripListDialog::getTripsToDisplay()
{
    if (!_tripService) {
        return QList<Trip>(); // Return empty list if service is null
    }
    return _tripService->getAllTrips();
}

TripCard* TripListDialog::createTripCard(const Trip& trip)
{
    return new TripCard(trip, this);
}

void TripListDialog::onTripCardCreated(TripCard* card, const Trip& trip)
{
    if (!card) return; // Safety check

    // Connect the book button signal
    connect(card, &TripCard::bookClicked, this, &TripListDialog::handleBookClicked);
}

void TripListDialog::handleBookClicked(int tripId)
{
    if (!_bookingService) {
        CustomMessageBox::show("Error", "Booking service not available");
        return;
    }

    if (_bookingService->bookTrip(tripId)) {
        CustomMessageBox::show("Success", "Trip booked successfully!");
    } else {
        CustomMessageBox::show("Error", "You've already booked this trip!");
    }
}
