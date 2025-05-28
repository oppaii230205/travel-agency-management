#include "AddTripDialog.h"
#include "ui_AddTripDialog.h"
#include <QIntValidator>
#include <QPropertyAnimation>
#include <QScreen>
#include <QGuiApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "CustomMessageBox.h"
#include <QFormLayout>
#include <QLabel>
#include <QFileDialog>
#include <QRandomGenerator>

AddTripDialog::AddTripDialog(QSharedPointer<TripService> tripService, QSharedPointer<AzureStorageService> storageService, QWidget* parent)
    : QDialog(parent),
    ui(new Ui::AddTripDialog),
    _tripService(tripService),
    _storageService(storageService)
{
    ui->setupUi(this);
    setWindowTitle("Add Trip");

    // Thiết lập kích thước dựa trên màn hình
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = qMin(500, static_cast<int>(screenGeometry.width() * 0.35));
    int height = qMin(600, static_cast<int>(screenGeometry.height() * 0.6));
    setMinimumSize(width, height);
    resize(width, height);

    // Gọi hàm setup giao diện
    setupUI();

    // Thiết lập validator cho các field
    ui->linePrice->setValidator(new QIntValidator(0, 10000000, this));

    // Thêm các mức độ khó
    ui->comboDifficulty->addItem("Easy");
    ui->comboDifficulty->addItem("Medium");
    ui->comboDifficulty->addItem("Difficult");

    // Hiệu ứng fade in khi mở cửa sổ
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    connect(_storageService.data(), &AzureStorageService::uploadCompleted,
            this, &AddTripDialog::onImageUploaded);

    // Thiết lập ban đầu cho label ảnh
    ui->labelImage->setText("No image selected");
    ui->labelImage->setStyleSheet("color: #666666; font-style: italic;");

    // Thiết lập nút chọn ảnh
    ui->btnChooseImage->setText("Choose Image");
    ui->btnChooseImage->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border: none;"
        "   padding: 5px 10px;"
        "   border-radius: 4px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        );
}

void AddTripDialog::setupUI()
{
    // Xóa layout hiện tại nếu có
    if (layout()) delete layout();

    // Layout chính
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(40, 30, 40, 30);

    /* ===== PHẦN THÔNG TIN CHUYẾN ĐI ===== */
    QGroupBox *tripGroup = new QGroupBox("Trip Information");
    tripGroup->setStyleSheet(R"(
        QGroupBox {
            color: white;
            font-size: 14px;
            border: 1px solid #3498db;
            border-radius: 5px;
            margin-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 3px;
        }
    )");

    // Sử dụng QGridLayout thay vì QFormLayout để kiểm soát tốt hơn
    QGridLayout *formLayout = new QGridLayout();
    formLayout->setSpacing(15);
    formLayout->setHorizontalSpacing(20);
    formLayout->setVerticalSpacing(15);

    // Thiết lập cột label có chiều rộng cố định
    formLayout->setColumnMinimumWidth(0, 120); // Cột label
    formLayout->setColumnStretch(1, 1);        // Cột input có thể mở rộng

    // Tạo các QLabel riêng thay vì dùng QFormLayout tự động
    QLabel *lblName = new QLabel("Trip Name:");
    QLabel *lblDuration = new QLabel("Duration:");
    QLabel *lblGroupSize = new QLabel("Group Size:");
    QLabel *lblDifficulty = new QLabel("Difficulty:");
    QLabel *lblPrice = new QLabel("Price:");
    QLabel *lblSummary = new QLabel("Summary:");
    QLabel *lblDescription = new QLabel("Description:");

    // Thiết lập style cho label
    QString labelStyle = "QLabel { color: white; font-size: 14px; }";
    lblName->setStyleSheet(labelStyle);
    lblDuration->setStyleSheet(labelStyle);
    lblGroupSize->setStyleSheet(labelStyle);
    lblDifficulty->setStyleSheet(labelStyle);
    lblPrice->setStyleSheet(labelStyle);
    lblSummary->setStyleSheet(labelStyle);
    lblDescription->setStyleSheet(labelStyle);

    // Thêm các widget vào grid layout
    formLayout->addWidget(lblName, 0, 0);
    formLayout->addWidget(ui->lineName, 0, 1);

    formLayout->addWidget(lblDuration, 1, 0);
    formLayout->addWidget(ui->spinDuration, 1, 1);

    formLayout->addWidget(lblGroupSize, 2, 0);
    formLayout->addWidget(ui->spinGroupSize, 2, 1);

    formLayout->addWidget(lblDifficulty, 3, 0);
    formLayout->addWidget(ui->comboDifficulty, 3, 1);

    formLayout->addWidget(lblPrice, 4, 0);
    formLayout->addWidget(ui->linePrice, 4, 1);

    formLayout->addWidget(lblSummary, 5, 0, Qt::AlignTop);
    formLayout->addWidget(ui->textSummary, 5, 1);

    formLayout->addWidget(lblDescription, 6, 0, Qt::AlignTop);
    formLayout->addWidget(ui->textDescription, 6, 1);

    // Thêm phần chọn ảnh vào formLayout
    QLabel *lblImage = new QLabel("Trip Image:");
    lblImage->setStyleSheet(labelStyle);
    formLayout->addWidget(lblImage, 7, 0);

    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addWidget(ui->btnChooseImage);
    imageLayout->addWidget(ui->labelImage, 1); // Cho label mở rộng
    formLayout->addLayout(imageLayout, 7, 1);

    // Thiết lập size policy cho các widget input
    ui->lineName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->spinDuration->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->spinGroupSize->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->comboDifficulty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->linePrice->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->textSummary->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    ui->textDescription->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);

    // Thiết lập kích thước tối thiểu cho các widget
    ui->textSummary->setMinimumHeight(50);
    ui->textDescription->setMinimumHeight(50);

    tripGroup->setLayout(formLayout);

    /* ===== PHẦN NÚT ===== */
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(0, 15, 0, 0);
    buttonLayout->addStretch();

    // Thiết lập style cho các nút
    ui->btnSave->setStyleSheet(R"(
        QPushButton {
            background-color: #2ecc71;
            color: white;
            min-width: 120px;
            min-height: 35px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #27ae60;
        }
    )");

    ui->btnCancel->setStyleSheet(R"(
        QPushButton {
            background-color: #e74c3c;
            color: white;
            min-width: 120px;
            min-height: 35px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #c0392b;
        }
    )");

    buttonLayout->addWidget(ui->btnSave);
    buttonLayout->addWidget(ui->btnCancel);

    /* ===== TỔNG HỢP LAYOUT ===== */
    mainLayout->addWidget(tripGroup);
    mainLayout->addLayout(buttonLayout);

    // Style sheet cho cửa sổ
    this->setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                      stop:0 #3498db, stop:1 #2c3e50);
            font-family: 'Segoe UI', Arial, sans-serif;
        }
        QLabel {
            color: white;
            font-size: 14px;
            min-width: 100px;
        }
        QTextEdit {
            min-width: 300px;
        }
    )");
}

AddTripDialog::~AddTripDialog() {
    delete ui;
}

void AddTripDialog::on_btnSave_clicked()
{
    if (ui->lineName->text().isEmpty()) {
        CustomMessageBox::show("Lỗi", "Vui lòng nhập tên chuyến đi");
        return;
    }

    if (!_tempImagePath.isEmpty() && _uploadedImageUrl.isEmpty()) {
        CustomMessageBox::show("Warning", "Please wait for image upload to complete");
        return;
    }

    Trip newTrip(
        0, // ID sẽ được DB tự sinh
        ui->lineName->text(),
        ui->spinDuration->value(),
        ui->spinGroupSize->value(),
        ui->comboDifficulty->currentText(),
        ui->linePrice->text().toInt(),
        ui->textSummary->toPlainText(),
        ui->textDescription->toPlainText(),
        _uploadedImageUrl
        );

    if (_tripService->createTrip(newTrip)) {
        accept(); // Đóng dialog nếu thành công
    } else {
        CustomMessageBox::show("Lỗi", "Không thể thêm chuyến đi mới");
    }
}

void AddTripDialog::on_btnCancel_clicked()
{
    reject(); // Đóng dialog và trả về QDialog::Rejected
}

void AddTripDialog::on_btnChooseImage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(
        this,
        "Select Trip Image",
        QDir::homePath(),
        "Image Files (*.png *.jpg *.jpeg *.bmp)"
        );

    if (!imagePath.isEmpty()) {
        _tempImagePath = imagePath;
        QFileInfo fileInfo(imagePath);
        ui->labelImage->setText("Uploading: " + fileInfo.fileName());
        ui->labelImage->setStyleSheet("color: black; font-style: normal;");

        // Tạo tên file unique cho blob storage
        QString blobName = QString("trip_%1_%2.%3")
                               .arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"))
                               .arg(QRandomGenerator::global()->bounded(1000))
                               .arg(fileInfo.suffix().toLower());

        // Bắt đầu upload
        qDebug() << imagePath;
        _storageService->uploadImage(imagePath, blobName);
    }
}

void AddTripDialog::onImageUploaded(const QString &imageUrl)
{
    // Lưu URL ảnh vào biến tạm để sử dụng khi save
    _uploadedImageUrl = imageUrl;

    // Có thể thêm thông báo hoặc cập nhật UI nếu cần
    ui->labelImage->setText("Image uploaded: " + QFileInfo(imageUrl).fileName());
}
