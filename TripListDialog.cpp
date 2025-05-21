// TripListDialog.cpp
#include "TripListDialog.h"
#include "TripDetailDialog.h"
#include <QPropertyAnimation>

#include <QScrollArea>
#include <QHBoxLayout>
#include <QMessageBox>

TripListDialog::TripListDialog(QSharedPointer<TripService> tripService,
                             QSharedPointer<BookingService> bookingService,
                             QWidget *parent)
    : QDialog(parent), _tripService(tripService), _bookingService(bookingService)
{
    // Thiết lập cửa sổ
    setWindowTitle("Available Trips");
    setMinimumSize(850, 625);

    // Tạo scroll area
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    // Widget chứa nội dung chính
    QWidget *contentWidget = new QWidget();
    _gridLayout = new QGridLayout(contentWidget); // Sử dụng QGridLayout thay vì QHBoxLayout
    _gridLayout->setSpacing(20); // Khoảng cách giữa các card
    _gridLayout->setContentsMargins(20, 20, 20, 20);

    scrollArea->setWidget(contentWidget);

    // Layout chính
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);

    // Tải các trip card
    refreshTripList();
}

void TripListDialog::refreshTripList()
{
    // Xóa card cũ
    QLayoutItem* item;
    while (item = _gridLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    // Tải danh sách trip
    QList<Trip> trips = _tripService->getAllTrips();

    // Thêm card mới
    for (int i = 0; i < trips.size(); ++i) {
        TripCard *card = new TripCard(trips[i], this);
        connect(card, &TripCard::bookClicked, this, &TripListDialog::handleBookClicked);
        connect(card, &TripCard::detailsClicked, this, &TripListDialog::handleDetailsClicked);

        // Tính toán vị trí trong grid
        int row = i / 3; // 3 cột
        int col = i % 3;
        _gridLayout->addWidget(card, row, col);
    }
}

// Xử lý sự kiện resize để điều chỉnh số cột
void TripListDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    QPropertyAnimation *anim = new QPropertyAnimation(this, "geometry");
    anim->setDuration(300);
    anim->setEasingCurve(QEasingCurve::InOutQuad);

    // Tính toán số cột dựa trên chiều rộng
    int cardWidth = 300; // Chiều rộng mỗi card
    int spacing = _gridLayout->spacing();
    int margin = _gridLayout->contentsMargins().left() + _gridLayout->contentsMargins().right();

    int availableWidth = width() - margin;
    int columns = qMax(1, availableWidth / (cardWidth + spacing));

    // Sắp xếp lại các card
    QList<TripCard*> cards = findChildren<TripCard*>();
    for (int i = 0; i < cards.size(); ++i) {
        int row = i / columns;
        int col = i % columns;
        _gridLayout->addWidget(cards[i], row, col);
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
    QSharedPointer<TripDetailDialog> detailsDialog = QSharedPointer<TripDetailDialog>::create(trip);
    // ... thiết kế dialog chi tiết ...
    detailsDialog->exec();
}
