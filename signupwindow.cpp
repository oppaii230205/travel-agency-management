#include "signupwindow.h"
#include "ui_signup_window.h"
#include <QMessageBox>
#include <QRegularExpression>

SignupWindow::SignupWindow(QSharedPointer<AuthService> authService, QWidget* parent)
    : QDialog(parent), ui(new Ui::SignupWindow), _authService(authService) {
    ui->setupUi(this);
    setWindowTitle("Đăng ký tài khoản");

    connect(_authService.data(), &AuthService::signupSuccess,
            this, &SignupWindow::handleSignupSuccess);
    connect(_authService.data(), &AuthService::signupFailed,
            this, &SignupWindow::handleSignupFailed);

    // Ẩn mk
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordEdit->setEchoMode(QLineEdit::Password);
}

SignupWindow::~SignupWindow() {
    delete ui;
}

void SignupWindow::on_signupButton_clicked() {
    QString email = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();
    QString name = ui->nameEdit->text();

    // Validate input
    if ((email.isEmpty()) || (password.isEmpty()) || (name.isEmpty())) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập đầy đủ thông tin");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Lỗi", "Mật khẩu không khớp");
        return;
    }

    if (password.length() < minPasswordLength) {
        QMessageBox::warning(this, "Lỗi", "Mật khẩu phải có ít nhất 6 ký tự");
        return;
    }

    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Lỗi", "Email không hợp lệ");
        return;
    }

    _authService->signup(email, password, name);
}

void SignupWindow::on_backButton_clicked() {
    emit backToLogin();
    this->close();
}

void SignupWindow::handleSignupSuccess() {
    QMessageBox::information(this, "Thành công", "Đăng ký thành công!");
    emit backToLogin();
    this->close();
}

void SignupWindow::handleSignupFailed(const QString& reason) {
    QMessageBox::critical(this, "Lỗi đăng ký", reason);
}
