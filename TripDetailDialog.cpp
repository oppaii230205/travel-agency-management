// TripDetailDialog.cpp
#include "TripDetailDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFile>
#include <QFrame>

TripDetailDialog::TripDetailDialog(const Trip& trip, QWidget *parent)
    : QDialog(parent), _trip(trip)
{
    setWindowTitle("Trip Details - " + trip.getTripName());
    setMinimumSize(600, 500);

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
    _imageLabel = new QLabel(scrollContent);
    QPixmap pixmap(_trip.getImagePath().isEmpty() ? ":/images/default-trip.jpg" : _trip.getImagePath());
    _imageLabel->setPixmap(pixmap.scaledToWidth(500, Qt::SmoothTransformation));
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
