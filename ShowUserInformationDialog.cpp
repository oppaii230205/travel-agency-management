// ShowUserInformationDialog.cpp
#include "ShowUserInformationDialog.h"
#include "ui_ShowUserInformationDialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QDebug>
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

    connect(ui->ptnSave, &QPushButton::clicked, this, &ShowUserInformationDialog::on_btnSave_clicked);
    connect(ui->ptnCancel, &QPushButton::clicked, this, &ShowUserInformationDialog::on_btnCancel_clicked);
    //connect(ui->btnSelectAvatar, &QPushButton::clicked, this, &ShowUserInformationDialog::on_btnSelectAvatar_clicked);
    connect(_storageService.data(), &AzureStorageService::uploadCompleted,
            this, &ShowUserInformationDialog::onImageUploaded);

    loadUserData();

    ui->lineEditEmail->setReadOnly(true);
    ui->lineEditRole->setReadOnly(true);
    ui->avatarLabel->setAlignment(Qt::AlignCenter);
    ui->avatarLabel->setStyleSheet("border: 1px solid #ccc;");
}

ShowUserInformationDialog::~ShowUserInformationDialog()
{
    delete ui;
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
