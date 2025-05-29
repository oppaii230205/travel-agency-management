// ShowUserInformationDialog.cpp
#include "ShowUserInformationDialog.h"
#include "ui_ShowUserInformationDialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QDebug>
#include "CustomMessageBox.h"

#include "ShowUserInformationDialog.h"
#include "ui_ShowUserInformationDialog.h"
#include <QFileDialog>
#include <QPixmap>
#include <QNetworkReply>
#include <QPropertyAnimation>
#include <QScreen>
#include <QGuiApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include "CustomMessageBox.h"

ShowUserInformationDialog::ShowUserInformationDialog(QSharedPointer<UserService> userService,
                                                     QSharedPointer<AzureStorageService> storageService,
                                                     const QString& email,
                                                     QWidget* parent)
    : QDialog(parent),
    ui(new Ui::ShowUserInformationDialog),
    _userService(userService),
    _storageService(storageService),
    _networkManager(new QNetworkAccessManager(this)),
    _email(email)
{
    ui->setupUi(this);
    setWindowTitle("Thông tin người dùng");

    // Thiết lập kích thước
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = qMin(500, static_cast<int>(screenGeometry.width() * 0.35));
    int height = qMin(600, static_cast<int>(screenGeometry.height() * 0.6));
    setMinimumSize(width, height);
    resize(width, height);

    // Gọi hàm setup giao diện
    setupUI();

    connect(ui->ptnSave, &QPushButton::clicked, this, &ShowUserInformationDialog::on_btnSave_clicked);
    connect(ui->ptnCancel, &QPushButton::clicked, this, &ShowUserInformationDialog::on_btnCancel_clicked);
    connect(_storageService.data(), &AzureStorageService::uploadCompleted,
            this, &ShowUserInformationDialog::onImageUploaded);

    // Hiệu ứng fade in
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    loadUserData();

    ui->avatarLabel->setCursor(Qt::PointingHandCursor);
    connect(ui->avatarLabel, &QLabel::linkActivated, this, &ShowUserInformationDialog::onAvatarClicked);
}

void ShowUserInformationDialog::setupUI()
{
    // Xóa layout hiện tại nếu có
    if (layout()) delete layout();

    // Layout chính
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(40, 30, 40, 30);

    /* ===== PHẦN AVATAR ===== */
    QVBoxLayout *avatarLayout = new QVBoxLayout();
    avatarLayout->setAlignment(Qt::AlignCenter);

    QGroupBox *avatarGroup = new QGroupBox("Ảnh đại diện");
    avatarGroup->setStyleSheet(R"(
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

    QVBoxLayout *avatarGroupLayout = new QVBoxLayout();
    avatarGroupLayout->setAlignment(Qt::AlignCenter);

    // Thiết lập avatarLabel
    ui->avatarLabel->setAlignment(Qt::AlignCenter);
    ui->avatarLabel->setMinimumSize(150, 150);
    ui->avatarLabel->setMaximumSize(150, 150);
    ui->avatarLabel->setStyleSheet(R"(
        QLabel {
            background-color: rgba(255, 255, 255, 0.8);
            border: 2px solid #3498db;
            border-radius: 8px;
        }
        QLabel:hover {
            border: 2px solid #2ecc71;
            cursor: pointer;  /* Hiển thị biểu tượng bàn tay khi hover */
        }
    )");

    ui->avatarLabel->setText("<a href='#' style='text-decoration:none; color:black;'>Ảnh đại diện</a>");
    ui->avatarLabel->setOpenExternalLinks(false);

    // Cho phép nhấn vào label
    ui->avatarLabel->setCursor(Qt::PointingHandCursor);  // Biểu tượng bàn tay
    ui->avatarLabel->installEventFilter(this);  // Bắt sự kiện click

    avatarGroupLayout->addWidget(ui->avatarLabel, 0, Qt::AlignCenter);
    avatarGroup->setLayout(avatarGroupLayout);
    avatarLayout->addWidget(avatarGroup);
    /* ===== PHẦN THÔNG TIN ===== */
    QGroupBox *infoGroup = new QGroupBox("Thông tin cá nhân");
    infoGroup->setStyleSheet(avatarGroup->styleSheet());

    // Sử dụng QGridLayout thay vì QFormLayout để kiểm soát tốt hơn
    QGridLayout *formLayout = new QGridLayout();
    formLayout->setSpacing(15);
    formLayout->setColumnMinimumWidth(0, 100);  // Cố định chiều rộng cột label
    formLayout->setColumnStretch(1, 1);         // Cho phép cột input mở rộng

    // Thiết lập style chung cho label
    QString labelStyle = "QLabel { color: white; font-size: 14px; }";

    // Thêm các trường thông tin
    QLabel *emailLabel = new QLabel("Email:");
    emailLabel->setStyleSheet(labelStyle);
    formLayout->addWidget(emailLabel, 0, 0);
    formLayout->addWidget(ui->lineEditEmail, 0, 1);

    QLabel *nameLabel = new QLabel("Họ tên:");
    nameLabel->setStyleSheet(labelStyle);
    formLayout->addWidget(nameLabel, 1, 0);
    formLayout->addWidget(ui->lineEditName, 1, 1);

    QLabel *passLabel = new QLabel("Mật khẩu:");
    passLabel->setStyleSheet(labelStyle);
    formLayout->addWidget(passLabel, 2, 0);
    formLayout->addWidget(ui->lineEditPass, 2, 1);

    QLabel *roleLabel = new QLabel("Vai trò:");
    roleLabel->setStyleSheet(labelStyle);
    formLayout->addWidget(roleLabel, 3, 0);
    formLayout->addWidget(ui->lineEditRole, 3, 1);

    infoGroup->setLayout(formLayout);

    /* ===== PHẦN NÚT ===== */
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(0, 15, 0, 0);
    buttonLayout->addStretch();

    ui->ptnSave->setFixedWidth(120);  // Cố định chiều rộng nút
    ui->ptnSave->setStyleSheet(R"(
        QPushButton {
            background-color: #2ecc71;
            color: white;
            min-height: 35px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #27ae60;
        }
    )");

    ui->ptnCancel->setFixedWidth(120);  // Cố định chiều rộng nút
    ui->ptnCancel->setStyleSheet(R"(
        QPushButton {
            background-color: #e74c3c;
            color: white;
            min-height: 35px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #c0392b;
        }
    )");

    buttonLayout->addWidget(ui->ptnSave);
    buttonLayout->addWidget(ui->ptnCancel);

    /* ===== TỔNG HỢP LAYOUT ===== */
    mainLayout->addLayout(avatarLayout, 0);  // Thêm stretch factor = 0 để không mở rộng
    mainLayout->addWidget(infoGroup, 1);     // Thêm stretch factor = 1 để chiếm không gian còn lại
    mainLayout->addLayout(buttonLayout, 0);  // Thêm stretch factor = 0

    // Style sheet cho cửa sổ và các thành phần
    this->setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                      stop:0 #3498db, stop:1 #2c3e50);
            font-family: 'Segoe UI', Arial, sans-serif;
        }
        QLineEdit {
            background-color: rgba(255, 255, 255, 0.9);
            border: 2px solid #3498db;
            border-radius: 5px;
            padding: 8px;
            font-size: 14px;
            min-height: 35px;
        }
        QLineEdit:focus {
            border: 2px solid #2ecc71;
        }
        QLineEdit[readOnly="true"] {
            background-color: rgba(255, 255, 255, 0.7);
        }
    )");
    // Đảm bảo các lineEdit có thể mở rộng
    ui->lineEditEmail->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui->lineEditName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui->lineEditPass->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui->lineEditRole->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Thiết lập chiều rộng tối thiểu cho input
    ui->lineEditEmail->setMinimumWidth(250);
    ui->lineEditName->setMinimumWidth(250);
    ui->lineEditPass->setMinimumWidth(250);
    ui->lineEditRole->setMinimumWidth(250);

    // Cho phép dialog có kích thước hợp lý ban đầu
    this->resize(500, 600);
}

ShowUserInformationDialog::~ShowUserInformationDialog()
{
    delete ui;
}

bool ShowUserInformationDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->avatarLabel && event->type() == QEvent::MouseButtonPress) {
        onAvatarClicked();
        return true;
    }
    return QDialog::eventFilter(obj, event);
}

void ShowUserInformationDialog::onAvatarClicked()
{
    QString imagePath = QFileDialog::getOpenFileName(
        this,
        "Chọn ảnh đại diện",
        QDir::homePath(),
        "Hình ảnh (*.png *.jpg *.jpeg *.bmp)"
        );

    if (!imagePath.isEmpty()) {
        _tempAvatarPath = imagePath;
        updateAvatarPreview(imagePath);

        QFileInfo fileInfo(imagePath);
        QString extension = fileInfo.suffix().toLower();

        QString blobName = QString("avatar_%1_%2.%3")
                               .arg(_email.split("@")[0])
                               .arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"))
                               .arg(extension);

        _storageService->uploadImage(imagePath, blobName);
    }
}



void ShowUserInformationDialog::loadUserData()
{
    auto user = _userService->getUserByEmail(_email);
    if(user)
    {
        ui->lineEditEmail->setText(user->email());
        ui->lineEditName->setText(user->name());
        ui->lineEditPass->clear();
        ui->lineEditRole->setText(user->role());
        // Hiển thị ảnh đại diện nếu có
        if (!user->avatarUrl().isEmpty()) {
            loadAvatarFromUrl(user->avatarUrl());
        } else {
            ui->avatarLabel->setText("Chưa có ảnh đại diện");
        }

    }
}



void ShowUserInformationDialog::loadAvatarFromUrl(const QString &url)
{
    const QSize targetSize(141, 141);

    QNetworkRequest request(url);
    QNetworkReply *reply = _networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, targetSize]() {
        if (reply->error() == QNetworkReply::NoError) {
            QPixmap src;
            if (src.loadFromData(reply->readAll())) {

                /* 1) Phóng thu sao cho ảnh phủ kín khung 141×141
                   2) Qt::KeepAspectRatioByExpanding có thể làm ảnh lớn hơn khung,
                      nên ta sẽ cắt phần thừa ở giữa.
                */
                QPixmap scaled = src.scaled(
                    targetSize,                      // 141×141
                    Qt::KeepAspectRatioByExpanding,  // giữ tỉ lệ, phủ kín
                    Qt::SmoothTransformation);

                // 3) Cắt chính giữa về đúng 141×141
                QRect cropRect(
                    (scaled.width()  - targetSize.width())  / 2,
                    (scaled.height() - targetSize.height()) / 2,
                    targetSize.width(),
                    targetSize.height());

                QPixmap avatar = scaled.copy(cropRect);

                ui->avatarLabel->setPixmap(avatar);
                ui->avatarLabel->setFixedSize(targetSize);   // đảm bảo nhãn đúng 141×141
            } else {
                ui->avatarLabel->setText("Không thể đọc dữ liệu ảnh");
                qDebug() << "Failed to load image from downloaded data";
            }
        } else {
            ui->avatarLabel->setText("Lỗi tải ảnh");
            qDebug() << "Network error:" << reply->errorString()
                     << "URL:" << reply->url().toString();
        }
        reply->deleteLater();
    });
}


void ShowUserInformationDialog::on_btnSave_clicked()
{
    QString newName = ui->lineEditName->text();
    QString newPassword = ui->lineEditPass->text();

    if(newName.isEmpty())
    {
        CustomMessageBox::show("Error", "Name cannot be empty");
        return;
    }

    if (newPassword.length() < Constants::MIN_PASSWORD_LENGTH) {
        CustomMessageBox::show("Lỗi", "Mật khẩu phải có ít nhất 6 ký tự");
        return;
    }

    if (!_tempAvatarPath.isEmpty()) {
        // Nếu có ảnh mới chọn nhưng chưa upload xong
        CustomMessageBox::show("Warning", "Please wait for avatar upload to complete");
        return;
    }

    if(_userService->updateUser(_email, newPassword, newName))
    {
        CustomMessageBox::show("Success", "User information updated");
        accept();
    }
    else
    {
        CustomMessageBox::show("Error", "Failed to update user");
    }
}

void ShowUserInformationDialog::on_btnCancel_clicked()
{
    reject();
}



void ShowUserInformationDialog::on_btnSelectAvatar_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(
        this,
        "Chọn ảnh đại diện",
        QDir::homePath(),
        "Hình ảnh (*.png *.jpg *.jpeg *.bmp)"
        );

    if (!imagePath.isEmpty()) {
        _tempAvatarPath = imagePath;
        updateAvatarPreview(imagePath);

        QFileInfo fileInfo(imagePath);
        QString extension = fileInfo.suffix().toLower();

        QString blobName = QString("avatar_%1_%2.%3")
                               .arg(_email.split("@")[0])
                               .arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"))
                               .arg(extension);

        _storageService->uploadImage(imagePath, blobName);

    }
}

void ShowUserInformationDialog::onImageUploaded(const QString &imageUrl)
{
    // Lưu URL ảnh vào user
    if (_userService->updateUserAvatar(_email, imageUrl)) {
        CustomMessageBox::show("Thành công", "Ảnh đại diện đã được cập nhật");
        loadUserData(); // Refresh hiển thị
    } else {
        CustomMessageBox::show("Lỗi", "Không thể cập nhật ảnh đại diện");
    }

    _tempAvatarPath.clear();

}

void ShowUserInformationDialog::updateAvatarPreview(const QString &imagePath)
{
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        ui->avatarLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        ui->avatarLabel->setText("Không thể tải ảnh");
    }
}
