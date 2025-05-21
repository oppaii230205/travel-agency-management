#include "TripCard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>

TripCard::TripCard(const Trip& trip, QWidget *parent)
    : QWidget(parent), _tripId(trip.getTripId())
{
    this->setObjectName("tripCard");
    this->setProperty("class", "trip-card"); // Thêm property

    this->setAttribute(Qt::WA_StyledBackground, true);

    this->setAttribute(Qt::WA_Hover);  // Quan trọng: Bật khả năng nhận hover
    this->setMouseTracking(true);      // Theo dõi chuột ngay cả khi không nhấn

    this->setAttribute(Qt::WA_AcceptTouchEvents, false); // Tắt touch events nếu không cần
    this->setFocusPolicy(Qt::StrongFocus); // Thiết lập focus policy

    this->setAttribute(Qt::WA_NoMousePropagation, false); // Cho phép sự kiện chuột lan tỏa

    // shadowing
    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(0, 10);
    shadowEffect->setColor(Qt::gray); // TODO
    this->setGraphicsEffect(shadowEffect);

    this->setProperty("yPos", 0); // Khởi tạo property

    // Thiết lập kích thước cơ bản
    setMinimumSize(280, 350);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    // Setup layout và các thành phần UI
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Hình ảnh (có thể lấy từ resource hoặc URL)
    QLabel *imageLabel = new QLabel(this);

    QString pathToImage = !trip.getImagePath().isEmpty() ? trip.getImagePath() : ":/images/default-trip.jpg";

    QPixmap pixmap(pathToImage);

    if (pixmap.isNull()) {
        qWarning() << "Failed to load image:" << pathToImage;
        pixmap.load(":/images/default-trip.jpg");
    }

    // Tính toán kích thước giữ nguyên tỷ lệ
    QPixmap scaledPixmap = pixmap.scaledToWidth(350, Qt::SmoothTransformation);
    // Hoặc nếu muốn cố định cả chiều cao:
    // QPixmap scaledPixmap = pixmap.scaled(200, 150, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    imageLabel->setPixmap(scaledPixmap);
    imageLabel->setAlignment(Qt::AlignCenter);
    // imageLabel->setMinimumSize(200, 150);
    // imageLabel->setMaximumSize(200, 150);
    imageLabel->setObjectName("imageLabel");

    // Thông tin chuyến đi
    QLabel *nameLabel = new QLabel("<b>" + trip.getTripName() + "</b>", this);
    nameLabel->setObjectName("nameLabel"); // Quan trọng để CSS nhận diện

    QLabel *priceLabel = new QLabel("Price: $" + QString::number(trip.getPrice()), this);
    priceLabel->setObjectName("priceLabel");

    QLabel *difficultyLabel = new QLabel("Difficulty: " + trip.getDifficulty(), this);
    difficultyLabel->setObjectName("difficultyLabel");

    // Các nút
    QPushButton *detailsBtn = new QPushButton("Details", this);
    detailsBtn->setObjectName("detailsBtn");

    QPushButton *bookBtn = new QPushButton("Book Now", this);
    bookBtn->setObjectName("bookBtn");

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
    // this->setStyleSheet("TripCard { border: 1px solid #ddd; border-radius: 8px; padding: 10px; }");
}
