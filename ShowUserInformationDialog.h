#ifndef SHOWUSERINFORMATIONDIALOG_H
#define SHOWUSERINFORMATIONDIALOG_H

#include <QDialog>
#include <QSharedPointer>
#include "UserService.h"


namespace Ui {
class ShowUserInformationDialog;
}

class ShowUserInformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowUserInformationDialog(QSharedPointer<UserService> userService, const QString& email, QWidget* parent = nullptr);
    ~ShowUserInformationDialog();

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();

private:
    void loadUserData();
    Ui::ShowUserInformationDialog* ui;
    QSharedPointer<UserService> _userService;
    QString _email;
};

#endif // SHOWUSERINFORMATIONDIALOG_H
