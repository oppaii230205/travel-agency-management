#include "BookedTripCard.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

BookedTripCard::BookedTripCard(const Trip& trip, const Booking& booking, QWidget *parent)
    : TripCard(trip, parent), _booking(booking)
{
    setupCancelButton();

    // Add booking date information
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());
    if (layout) {
        // Find the "Book Now" button and replace it
        QList<QPushButton*> buttons = findChildren<QPushButton*>();
        QPushButton* bookBtn = nullptr;

        for (QPushButton* button : buttons) {
            if (button->text() == "Book Now") {
                bookBtn = button;
                break;
            }
        }

        if (bookBtn) {
            // Remove the "Book Now" button
            layout->removeWidget(bookBtn);
            bookBtn->deleteLater();

            // Add booking date label
            QLabel* bookingDateLabel = new QLabel(
                "📅 <b>Booked on:</b> " + _booking.getBookingDate().toString("dd/MM/yyyy hh:mm"),
                this
                );
            bookingDateLabel->setObjectName("bookingDateLabel");

            // Add cancel button
            QPushButton* cancelBtn = new QPushButton("Cancel Booking", this);
            cancelBtn->setObjectName("cancelBtn");

            // Insert before the last item (which should be the details button)
            int insertIndex = layout->count() - 1; // Before details button
            layout->insertWidget(insertIndex, bookingDateLabel);
            layout->insertWidget(insertIndex + 1, cancelBtn);

            // Connect cancel button
            connect(cancelBtn, &QPushButton::clicked, [this]() {
                emit cancelClicked(_tripId);
            });
        }
    }
}

void BookedTripCard::setupCancelButton()
{
    // Additional setup if needed
    // This method can be extended for more complex cancel button configurations
}
