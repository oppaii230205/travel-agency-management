#include "TripCard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QColor>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QEvent>

TripCard::TripCard(const Trip& trip, QWidget *parent)
    : QWidget(parent), _tripId(trip.getTripId())
{
    _networkManager = new QNetworkAccessManager(this);

    this->setObjectName("tripCard");
    this->setProperty("class", "trip-card"); // Thêm property

    this->setAttribute(Qt::WA_StyledBackground, true);

    this->setAttribute(Qt::WA_Hover);  // Quan trọng: Bật khả năng nhận hover
    this->installEventFilter(this); // Cài đặt bộ lọc sự kiện
    this->setMouseTracking(true);      // Theo dõi chuột ngay cả khi không nhấn

    this->setAttribute(Qt::WA_AcceptTouchEvents, false); // Tắt touch events nếu không cần
    this->setFocusPolicy(Qt::StrongFocus); // Thiết lập focus policy

    this->setAttribute(Qt::WA_NoMousePropagation, false); // Cho phép sự kiện chuột lan tỏa

    // shadowing
    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(48);
    shadowEffect->setOffset(0, 5);

    // Set rgba color
    QColor color;
    color.setRgbF(0,0,0,0.075);
    shadowEffect->setColor(color); // TODO
    this->setGraphicsEffect(shadowEffect);

    this->setProperty("yPos", 0); // Khởi tạo property

    // Thiết lập kích thước cơ bản
    setMinimumSize(280, 350);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    // Setup layout và các thành phần UI
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Hình ảnh (có thể lấy từ resource hoặc URL)
    // QLabel *imageLabel = new QLabel(this);

    // QString pathToImage = !trip.getImagePath().isEmpty() ? trip.getImagePath() : ":/images/default-trip.jpg";

    // QPixmap pixmap(pathToImage);

    // if (pixmap.isNull()) {
    //     qWarning() << "Failed to load image:" << pathToImage;
    //     pixmap.load(":/images/default-trip.jpg");
    // }

    // // Tính toán kích thước giữ nguyên tỷ lệ
    // QPixmap scaledPixmap = pixmap.scaledToWidth(350, Qt::SmoothTransformation);
    // // Hoặc nếu muốn cố định cả chiều cao:
    // // QPixmap scaledPixmap = pixmap.scaled(200, 150, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // imageLabel->setPixmap(scaledPixmap);
    // imageLabel->setAlignment(Qt::AlignCenter);
    // // imageLabel->setMinimumSize(200, 150);
    // // imageLabel->setMaximumSize(200, 150);
    // imageLabel->setObjectName("imageLabel");

    // Thay thế phần code hiện tại bằng:
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setObjectName("imageLabel");
    imageLabel->setAlignment(Qt::AlignCenter);

    // Kiểm tra nếu có URL ảnh từ trip
    if (!trip.getImagePath().isEmpty() && trip.getImagePath().startsWith("http")) {
        // Nếu là URL thì tải từ mạng
        loadImageFromUrl(trip.getImagePath(), imageLabel);
    } else {
        // Nếu là đường dẫn local hoặc không có ảnh
        QString pathToImage = !trip.getImagePath().isEmpty() ? trip.getImagePath() : ":/images/default-trip.jpg";
        QPixmap pixmap(pathToImage);

        if (pixmap.isNull()) {
            loadDefaultImage(imageLabel);
        } else {
            QPixmap scaledPixmap = pixmap.scaledToWidth(350, Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
        }
    }

    // Thông tin chuyến đi
    QLabel *nameLabel = new QLabel("<b>" + trip.getTripName() + "</b>", this);
    nameLabel->setObjectName("nameLabel"); // Quan trọng để CSS nhận diện

    QLabel *priceLabel = new QLabel("💵 <b>Price:</b> $" + QString::number(trip.getPrice()), this);
    priceLabel->setObjectName("priceLabel");

    QLabel *difficultyLabel = new QLabel("🧗 <b>Difficulty:</b> " + trip.getDifficulty(), this);
    difficultyLabel->setObjectName("difficultyLabel");

    QLabel *durationLabel = new QLabel("⏱️ <b>Duration:</b> " + QString::number(trip.getDuration()) + " days", this);
    durationLabel->setObjectName("durationLabel");


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
    layout->addWidget(durationLabel);
    layout->addWidget(detailsBtn);
    layout->addWidget(bookBtn);

    // Kết nối signals
    connect(bookBtn, &QPushButton::clicked, [this]() {
        emit bookClicked(_tripId);
    });

    connect(detailsBtn, &QPushButton::clicked, [this]() {
        emit detailsClicked(_tripId);
    });
}

bool TripCard::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this) {
        auto shadowEffect = qobject_cast<QGraphicsDropShadowEffect*>(this->graphicsEffect());
        int transitionTime = 150; //ms

        if (event->type() == QEvent::HoverEnter) {
            // Hiệu ứng di chuyển
            QPropertyAnimation *posAnim = new QPropertyAnimation(this, "pos");
            posAnim->setDuration(transitionTime);
            posAnim->setEasingCurve(QEasingCurve::OutQuad);
            posAnim->setStartValue(this->pos());
            posAnim->setEndValue(this->pos() + QPoint(0, -5));
            posAnim->start(QAbstractAnimation::DeleteWhenStopped);
            
            // Hiệu ứng đổ bóng (nếu có)
            if (shadowEffect) {
                QPropertyAnimation *shadowAnim = new QPropertyAnimation(shadowEffect, "offset");
                shadowAnim->setDuration(transitionTime);
                shadowAnim->setEasingCurve(QEasingCurve::OutQuad);
                shadowAnim->setStartValue(shadowEffect->offset());
                shadowAnim->setEndValue(QPointF(0, 10));
                shadowAnim->start(QAbstractAnimation::DeleteWhenStopped);
            }
            
            return true;
        }
        else if (event->type() == QEvent::HoverLeave) {
            // Hiệu ứng di chuyển
            QPropertyAnimation *posAnim = new QPropertyAnimation(this, "pos");
            posAnim->setDuration(transitionTime);
            posAnim->setEasingCurve(QEasingCurve::OutQuad);
            posAnim->setStartValue(this->pos());
            posAnim->setEndValue(this->pos() + QPoint(0, 5));
            posAnim->start(QAbstractAnimation::DeleteWhenStopped);
            
            // Hiệu ứng đổ bóng (nếu có)
            if (shadowEffect) {
                QPropertyAnimation *shadowAnim = new QPropertyAnimation(shadowEffect, "offset");
                shadowAnim->setDuration(transitionTime);
                shadowAnim->setEasingCurve(QEasingCurve::OutQuad);
                shadowAnim->setStartValue(shadowEffect->offset());
                shadowAnim->setEndValue(QPointF(0, 10));
                shadowAnim->start(QAbstractAnimation::DeleteWhenStopped);
            }
            
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}


void TripCard::loadImageFromUrl(const QString &url, QLabel *imageLabel)
{
    const QSize targetSize(350, 0); // Chiều rộng cố định 350, chiều cao tự động

    QNetworkRequest request(url);
    QNetworkReply *reply = _networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, imageLabel, targetSize]() {
        if (reply->error() == QNetworkReply::NoError) {
            QPixmap src;
            if (src.loadFromData(reply->readAll())) {
                // Scale ảnh giữ nguyên tỷ lệ với chiều rộng cố định
                QPixmap scaled = src.scaledToWidth(targetSize.width(), Qt::SmoothTransformation);

                imageLabel->setPixmap(scaled);
                imageLabel->setAlignment(Qt::AlignCenter);
            } else {
                qWarning() << "Failed to load image from downloaded data";
                loadDefaultImage(imageLabel);
            }
        } else {
            qWarning() << "Network error:" << reply->errorString() << "URL:" << reply->url().toString();
            loadDefaultImage(imageLabel);
        }
        reply->deleteLater();
    });
}

void TripCard::loadDefaultImage(QLabel *imageLabel)
{
    QPixmap defaultPixmap(":/images/default-trip.jpg");
    if (!defaultPixmap.isNull()) {
        QPixmap scaled = defaultPixmap.scaledToWidth(350, Qt::SmoothTransformation);
        imageLabel->setPixmap(scaled);
        imageLabel->setAlignment(Qt::AlignCenter);
    } else {
        imageLabel->setText("No Image Available");
    }
}
