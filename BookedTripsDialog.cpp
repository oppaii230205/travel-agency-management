#include "BookedTripsDialog.h"
#include "CustomMessageBox.h"
#include <QLabel>
#include <QVBoxLayout>

BookedTripsDialog::BookedTripsDialog(QSharedPointer<TripService> tripService,
                                     QSharedPointer<BookingService> bookingService,
                                     QSharedPointer<ReviewService> reviewService,
                                     QWidget *parent)
    : BaseTripDialog(tripService, bookingService, reviewService, parent)
{
    // Connect to booking service signals for real-time updates
    connect(_bookingService.data(), &BookingService::bookingsUpdated,
            this, &BookedTripsDialog::onBookingsUpdated);
}

QString BookedTripsDialog::getWindowTitle() const
{
    return "My Booked Trips";
}

QList<Trip> BookedTripsDialog::getTripsToDisplay()
{
    QList<Trip> bookedTrips;

    // Get user's bookings
    _userBookings = _bookingService->getUserBookings();

    // Get corresponding trips
    for (const Booking& booking : _userBookings) {
        Trip trip = _tripService->getTripById(booking.getTripId());
        if (trip.getTripId() != -1) { // Assuming -1 indicates invalid trip
            bookedTrips.append(trip);
        }
    }

    return bookedTrips;
}

TripCard* BookedTripsDialog::createTripCard(const Trip& trip)
{
    // Find the corresponding booking for this trip
    Booking booking = findBookingForTrip(trip.getTripId());

    // Create BookedTripCard instead of regular TripCard
    BookedTripCard* card = new BookedTripCard(trip, booking, this);
    return card;
}

void BookedTripsDialog::onTripCardCreated(TripCard* card, const Trip& trip)
{
    // Cast to BookedTripCard to connect cancel signal
    BookedTripCard* bookedCard = qobject_cast<BookedTripCard*>(card);
    if (bookedCard) {
        connect(bookedCard, &BookedTripCard::cancelClicked,
                this, &BookedTripsDialog::handleCancelClicked);
    }
}

void BookedTripsDialog::setupAdditionalUI()
{
    // Add additional UI elements specific to booked trips if needed
    // For example, a refresh button or booking statistics

    // Check if user has no bookings and show appropriate message
    if (_userBookings.isEmpty()) {
        QLabel* noBookingsLabel = new QLabel("You haven't booked any trips yet.", _contentWidget);
        noBookingsLabel->setAlignment(Qt::AlignCenter);
        noBookingsLabel->setStyleSheet("font-size: 16px; color: #666; padding: 50px;");
        _gridLayout->addWidget(noBookingsLabel, 0, 0, 1, 3); // Span across 3 columns
    }
}

void BookedTripsDialog::handleCancelClicked(int tripId)
{
    // Show confirmation dialog
    auto reply = CustomMessageBox::question(
        "Confirm Cancellation",
        "Are you sure you want to cancel this booking?"
        );

    if (reply == QMessageBox::Yes) {
        if (_bookingService->cancelBooking(tripId)) {
            CustomMessageBox::show("Success", "Booking cancelled successfully!");
            // Dialog will refresh automatically via onBookingsUpdated signal
        } else {
            CustomMessageBox::show("Error", "Failed to cancel booking. Please try again.");
        }
    }
}

void BookedTripsDialog::onBookingsUpdated()
{
    // Refresh the trip list when bookings are updated
    refreshTripList();
}

Booking BookedTripsDialog::findBookingForTrip(int tripId) const
{
    for (const Booking& booking : _userBookings) {
        if (booking.getTripId() == tripId) {
            return booking;
        }
    }

    // Return default booking if not found (shouldn't happen in normal flow)
    return Booking();
}
