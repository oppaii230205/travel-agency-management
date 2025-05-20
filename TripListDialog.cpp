// TripListDialog.cpp
#include "TripListDialog.h"
#include "TripCard.h"
#include "TripDetailDialog.h"

#include <QScrollArea>
#include <QHBoxLayout>
#include <QMessageBox>

TripListDialog::TripListDialog(QSharedPointer<TripService> tripService,
                             QSharedPointer<BookingService> bookingService,
                             QWidget *parent)
    : QDialog(parent), _tripService(tripService), _bookingService(bookingService)
{
    // Tạo scroll area để chứa các card khi nhiều
    QScrollArea *scrollArea = new QScrollArea(this);
    _cardsContainer = new QWidget(scrollArea);
    QHBoxLayout *layout = new QHBoxLayout(_cardsContainer);

    // Thiết lập scroll area
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(_cardsContainer);

    // Layout chính
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);

    // Tải và hiển thị các card
    setupCards();
}

void TripListDialog::setupCards()
{
    // Xóa card cũ nếu có
    QLayoutItem *child;
    while (child = _cardsContainer->layout()->takeAt(0)) {
        delete child->widget();
        delete child;
    }

    // Tạo card mới cho mỗi trip
    QList<Trip> trips = _tripService->getAllTrips();
    for (const Trip &trip : trips) {
        TripCard *card = new TripCard(trip, _cardsContainer);
        connect(card, &TripCard::bookClicked, this, &TripListDialog::handleBookClicked);
        connect(card, &TripCard::detailsClicked, this, &TripListDialog::handleDetailsClicked);
        _cardsContainer->layout()->addWidget(card);
    }
}

void TripListDialog::handleBookClicked(int tripId)
{
    // Xử lý đặt chỗ
    if (_bookingService->bookTrip(tripId)) {
        QMessageBox::information(this, "Success", "Trip booked successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to book trip");
    }
}

void TripListDialog::handleDetailsClicked(int tripId)
{
    // Hiển thị dialog chi tiết
    Trip trip = _tripService->getTripById(tripId);
    QSharedPointer<TripDetailDialog> detailsDialog = QSharedPointer<TripDetailDialog>::create(trip, _cardsContainer);
    // ... thiết kế dialog chi tiết ...
    detailsDialog->exec();
}
