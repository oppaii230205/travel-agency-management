#include "loginwindow.h"
#include "ui_login_window.h"
#include "signupwindow.h"
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QFontDatabase>
#include <QScreen>
#include <QGuiApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "CustomMessageBox.h"

LoginWindow::LoginWindow(QSharedPointer<AuthService> authService, QWidget* parent)
    : QDialog(parent), ui(new Ui::QDialog), _authService(authService) {
    ui->setupUi(this);
    setWindowTitle("Đăng Nhập");

    // Tính toán kích thước dựa trên màn hình
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = qMin(400, static_cast<int>(screenGeometry.width() * 0.3));
    int height = qMin(500, static_cast<int>(screenGeometry.height() * 0.5));

    // Thiết lập kích thước cửa sổ với giá trị tối thiểu
    setMinimumSize(width, height);
    resize(width, height);

    // Gọi hàm setup giao diện
    setupUI();

    connect(_authService.data(), &AuthService::loginSuccess,
            this, &LoginWindow::handleLoginSuccess);
    connect(_authService.data(), &AuthService::loginFailed,
            this, &LoginWindow::handleLoginFailed);
    connect(this, &QDialog::rejected, this, &LoginWindow::onLoginRejected);

    // Ẩn mk và thiết lập kích thước tối thiểu cho các ô nhập
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->emailEdit->setMinimumSize(250, 35);
    ui->passwordEdit->setMinimumSize(250, 35);

    // Hiệu ứng fade in khi mở cửa sổ
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

void LoginWindow::setupUI() {
    // Xóa layout hiện tại nếu có
    if (this->layout()) {
        delete this->layout();
    }

    // 1. Tạo layout chính với khoảng cách và lề hợp lý
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);  // Khoảng cách giữa các widget
    mainLayout->setContentsMargins(40, 40, 40, 40);  // Lề xung quanh (left, top, right, bottom)

    // 2. Tạo layout cho form nhập liệu
    QVBoxLayout *formLayout = new QVBoxLayout();
    formLayout->setSpacing(15);

    // 3. Thêm các widget vào form layout
    // Kiểm tra và thêm emailEdit nếu tồn tại
    if (ui->emailEdit) {
        formLayout->addWidget(ui->emailEdit);
    }

    // Kiểm tra và thêm passwordEdit nếu tồn tại
    if (ui->passwordEdit) {
        formLayout->addWidget(ui->passwordEdit);
    }

    // 4. Tạo layout cho các nút
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(0, 10, 0, 0);  // Thêm margin phía trên

    // Kiểm tra và thêm các nút nếu tồn tại
    if (ui->loginButton) {
        buttonLayout->addWidget(ui->loginButton);
    }
    if (ui->signupButton) {
        buttonLayout->addWidget(ui->signupButton);
    }

    // 5. Thêm stretch và các layout vào layout chính
    mainLayout->addStretch(1);  // Khoảng trống phía trên
    mainLayout->addLayout(formLayout);  // Thêm form layout
    mainLayout->addLayout(buttonLayout);  // Thêm button layout
    mainLayout->addStretch(1);  // Khoảng trống phía dưới

    // 6. Thiết lập CSS
    this->setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                      stop:0 #3498db, stop:1 #2c3e50);
            font-family: 'Segoe UI', Arial, sans-serif;
        }

        QLineEdit {
            background-color: rgba(255, 255, 255, 0.9);
            border: 2px solid #3498db;
            border-radius: 8px;
            padding: 12px;
            font-size: 14px;
            min-width: 250px;
            min-height: 40px;
        }

        QLineEdit:focus {
            border: 2px solid #2ecc71;
        }

        QPushButton {
            min-width: 120px;
            min-height: 40px;
            padding: 10px 15px;
            font-size: 14px;
            border-radius: 8px;
        }

        QPushButton#loginButton {
            background-color: #2ecc71;
            color: white;
        }

        QPushButton#loginButton:hover {
            background-color: #27ae60;
        }

        QPushButton#loginButton:pressed {
            background-color: #219653;
        }

        QPushButton#signupButton {
            background-color: transparent;
            border: 1px solid white;
            color: white;
        }

        QPushButton#signupButton:hover {
            background-color: rgba(255, 255, 255, 0.1);
        }
    )");

    // 7. Thiết lập size policy cho các widget
    if (ui->emailEdit) {
        ui->emailEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    }
    if (ui->passwordEdit) {
        ui->passwordEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    }
    if (ui->loginButton) {
        ui->loginButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    }
    if (ui->signupButton) {
        ui->signupButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    }
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_loginButton_clicked() {
    QString email = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();

    if ((email.isEmpty()) || (password.isEmpty())) {
       CustomMessageBox::show("Lỗi", "Vui lòng nhập đầy đủ email và mật khẩu");
        return;
    }

    _authService->login(email, password);
}

void LoginWindow::on_signupButton_clicked() {
    SignupWindow *signupWindow = new SignupWindow(_authService);
    signupWindow->show();
    this->hide();

    connect(signupWindow, &SignupWindow::backToLogin, this, [this]() {
        this->show();
    });
}

void LoginWindow::handleLoginSuccess() {
    qDebug() << "User logged in:" << _authService->getCurrentUser()->name();

    disconnect(this, &QDialog::rejected, this, &LoginWindow::onLoginRejected);
    emit loginSuccess();
    this->accept();
}

void LoginWindow::handleLoginFailed(const QString& reason) {
    CustomMessageBox::show("Lỗi đăng nhập", reason);
}

void LoginWindow::onLoginRejected() {
    emit loginAborted();
    qDebug() << "Người dùng đã hủy đăng nhập";
}
