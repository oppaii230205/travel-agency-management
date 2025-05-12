/*
#include "TripCard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>


TripCard::TripCard(const Trip& trip, QWidget *parent)
    : QWidget(parent), _tripId(trip.getTripId())
{
    // Setup layout và các thành phần UI
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Hình ảnh (có thể lấy từ resource hoặc URL)
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap(":/images/" + trip.getTripName().toLower().replace(" ", "_") + ".jpg")
                              .scaled(200, 150, Qt::KeepAspectRatio));

    // Thông tin chuyến đi
    QLabel *nameLabel = new QLabel("<b>" + trip.getTripName() + "</b>", this);
    QLabel *priceLabel = new QLabel("Price: $" + QString::number(trip.getPrice()), this);
    QLabel *difficultyLabel = new QLabel("Difficulty: " + trip.getDifficulty(), this);

    // Các nút
    QPushButton *detailsBtn = new QPushButton("Details", this);
    QPushButton *bookBtn = new QPushButton("Book Now", this);

    // Thêm vào layout
    layout->addWidget(imageLabel);
    layout->addWidget(nameLabel);
    layout->addWidget(priceLabel);
    layout->addWidget(difficultyLabel);
    layout->addWidget(detailsBtn);
    layout->addWidget(bookBtn);

    // Kết nối signals
    connect(bookBtn, &QPushButton::clicked, [this]() {
        emit bookClicked(_tripId);
    });

    connect(detailsBtn, &QPushButton::clicked, [this]() {
        emit detailsClicked(_tripId);
    });

    // Style thêm nếu cần
    this->setStyleSheet("TripCard { border: 1px solid #ddd; border-radius: 8px; padding: 10px; }");
}
*/
