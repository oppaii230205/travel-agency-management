#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>
#include "authservice.h"

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QDialog {
    Q_OBJECT

public:
    explicit SignupWindow(QSharedPointer<AuthService> authService, QWidget *parent = nullptr);
    ~SignupWindow();

signals:
    void backToLogin();

private slots:
    void on_signupButton_clicked();
    void on_backButton_clicked();
    void handleSignupSuccess();
    void handleSignupFailed(const QString& reason);

private:
    Ui::SignupWindow *ui;
    QSharedPointer<AuthService> m_authService;
};


#endif // SIGNUPWINDOW_H
