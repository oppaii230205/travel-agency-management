#include "loginwindow.h"
#include "ui_login_window.h"
#include "signupwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QSharedPointer<AuthService> authService, QWidget *parent)
    : QDialog(parent), ui(new Ui::QDialog), m_authService(authService) {
    ui->setupUi(this);
    setWindowTitle("Đăng Nhập");
    connect(m_authService.data(), &AuthService::loginSuccess,
            this, &LoginWindow::handleLoginSuccess);
    connect(m_authService.data(), &AuthService::loginFailed,
            this, &LoginWindow::handleLoginFailed);
    connect(this, &QDialog::rejected, this, &LoginWindow::onLoginRejected);

    // Ẩn mk
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_loginButton_clicked() {
    QString email = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập đầy đủ email và mật khẩu");
        return;
    }

    m_authService->login(email, password);
}

void LoginWindow::on_signupButton_clicked() {
    SignupWindow *signupWindow = new SignupWindow(m_authService);
    signupWindow->show();
    this->hide();

    connect(signupWindow, &SignupWindow::backToLogin, this, [this]() {
        this->show();
    });
}

void LoginWindow::handleLoginSuccess() {
    // TODO: Mở cửa sổ chính của ứng dụng
    // Định gọi MainWindow nhưng đưa ra main rồi =))
    qDebug() << "User logged in:" << m_authService->getCurrentUser()->name();

    disconnect(this, &QDialog::rejected, this, &LoginWindow::onLoginRejected);
    emit loginSuccess();
    this->accept();
}

void LoginWindow::handleLoginFailed(const QString& reason) {
    QMessageBox::critical(this, "Lỗi đăng nhập", reason);
}

void LoginWindow::onLoginRejected() {
    emit loginAborted();  // Phát tín hiệu khi người dùng nhấn tắt bảng đăng nhập
    qDebug() << "Người dùng đã hủy đăng nhập";
}
