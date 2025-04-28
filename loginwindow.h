#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "authservice.h"

namespace Ui {
class QDialog;
}

class LoginWindow : public QDialog {
    Q_OBJECT

public:
    explicit LoginWindow(QSharedPointer<AuthService> authService, QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccess();
    void loginAborted();

private slots:
    void on_loginButton_clicked();
    void on_signupButton_clicked();
    void handleLoginSuccess();
    void handleLoginFailed(const QString& reason);
    void onLoginRejected();

private:
    Ui::QDialog *ui;
    QSharedPointer<AuthService> m_authService;
};

#endif // LOGINWINDOW_H
