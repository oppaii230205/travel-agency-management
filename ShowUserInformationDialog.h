// ShowUserInformationDialog.h
#ifndef SHOWUSERINFORMATIONDIALOG_H
#define SHOWUSERINFORMATIONDIALOG_H

#include <QDialog>
#include <QSharedPointer>
#include "UserService.h"
#include "AzureStorageService.h"

namespace Ui {
class ShowUserInformationDialog;
}

class ShowUserInformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowUserInformationDialog(QSharedPointer<UserService> userService,
                                       QSharedPointer<AzureStorageService> storageService,
                                       const QString& email,
                                       QWidget* parent = nullptr);
    ~ShowUserInformationDialog();

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();
    void on_btnSelectAvatar_clicked();
    void onImageUploaded(const QString &imageUrl);
    //void onAvatarDownloaded();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void loadUserData();
    void updateAvatarPreview(const QString &imagePath);
    void loadAvatarFromUrl(const QString &url);
    void setupUI();
    void onAvatarClicked();

    Ui::ShowUserInformationDialog* ui;
    QSharedPointer<UserService> _userService;
    QSharedPointer<AzureStorageService> _storageService;
    QNetworkAccessManager* _networkManager;
    QString _email;
    QString _tempAvatarPath;
};

#endif // SHOWUSERINFORMATIONDIALOG_H
