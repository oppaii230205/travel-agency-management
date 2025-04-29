#ifndef SHOWUSERINFOMATIONDIALOG_H
#define SHOWUSERINFOMATIONDIALOG_H

#include <QDialog>
#include <QSharedPointer>
#include "UserService.h"


namespace Ui {
class ShowUserInfomationDialog;
}

class ShowUserInfomationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowUserInfomationDialog(QSharedPointer<UserService> userService, const QString &email, QWidget *parent = nullptr);
    ~ShowUserInfomationDialog();

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    void loadUserData();
    Ui::ShowUserInfomationDialog *ui;
    QSharedPointer<UserService> _userService;
    QString _email;
};

#endif // SHOWUSERINFOMATIONDIALOG_H
