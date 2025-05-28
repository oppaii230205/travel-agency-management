// TripDetailDialog.cpp
#include "TripDetailDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFile>
#include <QFrame>

TripDetailDialog::TripDetailDialog(const Trip& trip,
                                   QSharedPointer<ReviewService> reviewService,
                                   QWidget *parent)
    : QDialog(parent), _trip(trip), _reviewService(reviewService)
{
    _networkManager = new QNetworkAccessManager(this);
    setWindowTitle("Trip Details - " + trip.getTripName());
    setMinimumSize(800, 600); // 600 - 500

    setupUI();
    loadStyles();
}

void TripDetailDialog::setupUI()
{
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Scroll area để xử lý nội dung dài
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    QWidget *scrollContent = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(scrollContent);

    // Hiển thị ảnh lớn
    // _imageLabel = new QLabel(scrollContent);
    // QPixmap pixmap(_trip.getImagePath().isEmpty() ? ":/images/default-trip.jpg" : _trip.getImagePath());
    // _imageLabel->setPixmap(pixmap.scaledToWidth(500, Qt::SmoothTransformation));
    // _imageLabel->setAlignment(Qt::AlignCenter);
    // contentLayout->addWidget(_imageLabel);

    _imageLabel = new QLabel(scrollContent);
    if (_trip.getImagePath().startsWith("http", Qt::CaseInsensitive)) {
        loadImageFromUrl(_trip.getImagePath(), _imageLabel);
    } else {
        QPixmap pixmap(_trip.getImagePath().isEmpty() ? ":/images/default-trip.jpg" : _trip.getImagePath());
        _imageLabel->setPixmap(pixmap.scaledToWidth(500, Qt::SmoothTransformation));
    }
    _imageLabel->setAlignment(Qt::AlignCenter);
    contentLayout->addWidget(_imageLabel);

    // Thông tin chính
    QFrame *infoFrame = new QFrame(scrollContent);
    infoFrame->setFrameShape(QFrame::StyledPanel);
    QVBoxLayout *infoLayout = new QVBoxLayout(infoFrame);

    _titleLabel = new QLabel("<h1>" + _trip.getTripName() + "</h1>", infoFrame);
    _titleLabel->setObjectName("titleLabel");

    // Thông tin meta (giá, độ khó, thời gian)
    QWidget *metaWidget = new QWidget(infoFrame);
    QHBoxLayout *metaLayout = new QHBoxLayout(metaWidget);
    metaLayout->setContentsMargins(0, 0, 0, 0);

    _priceLabel = new QLabel("💵 <b>Price:</b> $" + QString::number(_trip.getPrice()), metaWidget);
    _priceLabel->setObjectName("priceLabel");

    _difficultyLabel = new QLabel("🧗 <b>Difficulty:</b> " + _trip.getDifficulty(), metaWidget);
    _difficultyLabel->setObjectName("difficultyLabel");

    _durationLabel = new QLabel("⏱️ <b>Duration:</b> " + QString::number(_trip.getDuration()) + " days", metaWidget);
    _durationLabel->setObjectName("durationLabel");

    metaLayout->addWidget(_priceLabel);
    metaLayout->addWidget(_difficultyLabel);
    metaLayout->addWidget(_durationLabel);
    metaLayout->addStretch();

    // Mô tả
    _summaryLabel = new QLabel(_trip.getSummary(), infoFrame);
    _summaryLabel->setObjectName("summaryLabel");
    _summaryLabel->setWordWrap(true);

    _descriptionLabel = new QLabel(_trip.getDescription(), infoFrame);
    _descriptionLabel->setObjectName("descriptionLabel");
    _descriptionLabel->setWordWrap(true);

    infoLayout->addWidget(_titleLabel);
    infoLayout->addWidget(metaWidget);
    infoLayout->addSpacing(15);
    infoLayout->addWidget(_summaryLabel);
    infoLayout->addSpacing(10);
    infoLayout->addWidget(_descriptionLabel);

    contentLayout->addWidget(infoFrame);
    contentLayout->addStretch();

    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);

    // Nút đóng
    QPushButton *closeButton = new QPushButton("Close", this);
    closeButton->setObjectName("closeButton");
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeButton, 0, Qt::AlignRight);

    // Thêm form review sau phần description
    setupReviewForm();

    // Thêm container cho các review hiện có
    _reviewsContainer = new QWidget(scrollContent);
    _reviewsContainer->setObjectName("reviewsContainer");
    QVBoxLayout* reviewsLayout = new QVBoxLayout(_reviewsContainer);

    QLabel* reviewsTitle = new QLabel("<h3>Reviews</h3>", _reviewsContainer);
    reviewsLayout->addWidget(reviewsTitle);

    // Load các review hiện có
    loadExistingReviews();

    contentLayout->addWidget(_reviewsContainer);
}

void TripDetailDialog::setupReviewForm()
{
    _reviewFormContainer = new QWidget();
    _reviewFormContainer->setObjectName("reviewFormContainer");
    QFormLayout* reviewFormLayout = new QFormLayout(_reviewFormContainer);

    // Chỉ hiển thị form nếu user có thể review
    if (_reviewService->canUserReview(_trip.getTripId())) {
        _ratingComboBox = new QComboBox(_reviewFormContainer);
        for (int i = 1; i <= 5; ++i) {
            _ratingComboBox->addItem(QString::number(i) + " ★", i);
        }
        _ratingComboBox->setCurrentIndex(4); // Mặc định 5 sao

        _reviewTextEdit = new QTextEdit(_reviewFormContainer);
        _reviewTextEdit->setPlaceholderText("Share your experience...");
        _reviewTextEdit->setMaximumHeight(100);

        _submitReviewButton = new QPushButton("Submit Review", _reviewFormContainer);
        _submitReviewButton->setObjectName("submitReviewButton");
        connect(_submitReviewButton, &QPushButton::clicked,
                this, &TripDetailDialog::onSubmitReview);

        reviewFormLayout->addRow("Rating:", _ratingComboBox);
        reviewFormLayout->addRow("Review:", _reviewTextEdit);
        reviewFormLayout->addRow(_submitReviewButton);
    } else {
        QLabel* noReviewLabel = new QLabel(_reviewFormContainer);
        if (_reviewService->canUserReview(_trip.getTripId())) {
            noReviewLabel->setText("<i>You have already reviewed this trip</i>");
        } else {
            noReviewLabel->setText("<i>Book this trip to leave a review</i>");
        }
        reviewFormLayout->addRow(noReviewLabel);
    }

    // Thêm form review vào layout chính (sau description)
    dynamic_cast<QVBoxLayout*>(_descriptionLabel->parentWidget()->layout())
        ->insertWidget(5, _reviewFormContainer);
}

void TripDetailDialog::loadExistingReviews()
{
    QList<Review> reviews = _reviewService->getTripReviews(_trip.getTripId());

    if (reviews.isEmpty()) {
        QLabel* noReviewsLabel = new QLabel("<i>No reviews yet</i>", _reviewsContainer);
        _reviewsContainer->layout()->addWidget(noReviewsLabel);
        return;
    }

    foreach (const Review& review, reviews) {
        QFrame* reviewFrame = new QFrame(_reviewsContainer);
        reviewFrame->setObjectName("reviewFrame");

        QVBoxLayout* reviewLayout = new QVBoxLayout(reviewFrame);

        // Hiển thị rating (sao)
        QLabel* ratingLabel = new QLabel(reviewFrame);
        ratingLabel->setText(QString::number(review.getRating()) + " ★");
        ratingLabel->setObjectName("ratingLabel");

        // Hiển thị comment
        QLabel* commentLabel = new QLabel(review.getComment(), reviewFrame);
        commentLabel->setObjectName("commentLabel");
        commentLabel->setWordWrap(true);

        // Hiển thị người review và ngày
        QLabel* metaLabel = new QLabel(reviewFrame);
        metaLabel->setText("By " + review.getUserEmail() + " on " +
                           review.getCreatedAt().toString("dd/MM/yyyy"));
        metaLabel->setObjectName("metaLabel");

        reviewLayout->addWidget(ratingLabel);
        reviewLayout->addWidget(commentLabel);
        reviewLayout->addWidget(metaLabel);

        _reviewsContainer->layout()->addWidget(reviewFrame);
    }
}

void TripDetailDialog::onSubmitReview()
{
    int rating = _ratingComboBox->currentData().toInt();
    QString comment = _reviewTextEdit->toPlainText();

    if (comment.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter your review comment");
        return;
    }

    if (_reviewService->submitReview(_trip.getTripId(), rating, comment)) {
        QMessageBox::information(this, "Success", "Thank you for your review!");
        updateReviewUI(); // Refresh UI sau khi submit
    }
}

void TripDetailDialog::updateReviewUI()
{
    // Xóa form review cũ
    _reviewFormContainer->deleteLater();
    _reviewsContainer->deleteLater();

    // Tạo lại UI
    setupReviewForm();
    loadExistingReviews();
}

void TripDetailDialog::loadStyles()
{
    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }
}

void TripDetailDialog::loadImageFromUrl(const QString &url, QLabel *imageLabel)
{
    const int targetWidth = 500; // Chiều rộng cố định 500px như trong code hiện tại

    if (url.isEmpty()) {
        loadDefaultImage(imageLabel);
        return;
    }

    QNetworkRequest request(url);
    QNetworkReply *reply = _networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, imageLabel, targetWidth]() {
        QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> replyPtr(reply);

        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Network error:" << reply->errorString() << "URL:" << reply->url().toString();
            loadDefaultImage(imageLabel);
            return;
        }

        QPixmap pixmap;
        if (!pixmap.loadFromData(reply->readAll())) {
            qWarning() << "Failed to load image from downloaded data";
            loadDefaultImage(imageLabel);
            return;
        }

        // Scale ảnh giữ nguyên tỷ lệ với chiều rộng cố định
        QPixmap scaled = pixmap.scaledToWidth(targetWidth, Qt::SmoothTransformation);
        imageLabel->setPixmap(scaled);
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setMinimumWidth(targetWidth); // Đảm bảo label có đủ không gian hiển thị
    });
}

void TripDetailDialog::loadDefaultImage(QLabel *imageLabel)
{
    const int targetWidth = 500;

    QPixmap defaultPixmap(":/images/default-trip.jpg");
    if (defaultPixmap.isNull()) {
        imageLabel->setText("No Image Available");
        imageLabel->setAlignment(Qt::AlignCenter);
        return;
    }

    QPixmap scaled = defaultPixmap.scaledToWidth(targetWidth, Qt::SmoothTransformation);
    imageLabel->setPixmap(scaled);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumWidth(targetWidth);
}
