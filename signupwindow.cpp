#include "signupwindow.h"
#include "ui_signup_window.h"
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QFontDatabase>
#include <QScreen>
#include <QGuiApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRegularExpression>
#include "CustomMessageBox.h"

SignupWindow::SignupWindow(QSharedPointer<AuthService> authService, QWidget* parent)
    : QDialog(parent), ui(new Ui::SignupWindow), _authService(authService) {
    ui->setupUi(this);
    setWindowTitle("Đăng Ký Tài Khoản");

    // Tính toán kích thước dựa trên màn hình
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = qMin(400, static_cast<int>(screenGeometry.width() * 0.3));
    int height = qMin(550, static_cast<int>(screenGeometry.height() * 0.6));

    // Thiết lập kích thước cửa sổ với giá trị tối thiểu
    setMinimumSize(width, height);
    resize(width, height);

    // Gọi hàm setup giao diện
    setupUI();

    connect(_authService.data(), &AuthService::signupSuccess,
            this, &SignupWindow::handleSignupSuccess);
    connect(_authService.data(), &AuthService::signupFailed,
            this, &SignupWindow::handleSignupFailed);

    // Ẩn mk và thiết lập kích thước tối thiểu cho các ô nhập
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    ui->emailEdit->setMinimumSize(250, 35);
    ui->passwordEdit->setMinimumSize(250, 35);
    ui->confirmPasswordEdit->setMinimumSize(250, 35);
    ui->nameEdit->setMinimumSize(250, 35);

    // Hiệu ứng fade in khi mở cửa sổ
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

void SignupWindow::setupUI() {
    // Xóa layout hiện tại nếu có
    if (this->layout()) {
        delete this->layout();
    }

    // 1. Tạo layout chính với khoảng cách và lề hợp lý
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);  // Khoảng cách giữa các widget
    mainLayout->setContentsMargins(40, 30, 40, 30);  // Lề xung quanh (left, top, right, bottom)

    // 2. Tạo layout cho form nhập liệu
    QVBoxLayout *formLayout = new QVBoxLayout();
    formLayout->setSpacing(12);

    // 3. Thêm các widget vào form layout
    if (ui->nameEdit) {
        formLayout->addWidget(ui->nameEdit);
    }
    if (ui->emailEdit) {
        formLayout->addWidget(ui->emailEdit);
    }
    if (ui->passwordEdit) {
        formLayout->addWidget(ui->passwordEdit);
    }
    if (ui->confirmPasswordEdit) {
        formLayout->addWidget(ui->confirmPasswordEdit);
    }

    // 4. Tạo layout cho các nút
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(0, 15, 0, 0);  // Thêm margin phía trên

    // Kiểm tra và thêm các nút nếu tồn tại
    if (ui->signupButton) {
        buttonLayout->addWidget(ui->signupButton);
    }
    if (ui->backButton) {
        buttonLayout->addWidget(ui->backButton);
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

        QPushButton#signupButton {
            background-color: #2ecc71;
            color: white;
        }

        QPushButton#signupButton:hover {
            background-color: #27ae60;
        }

        QPushButton#signupButton:pressed {
            background-color: #219653;
        }

        QPushButton#backButton {
            background-color: transparent;
            border: 1px solid white;
            color: white;
        }

        QPushButton#backButton:hover {
            background-color: rgba(255, 255, 255, 0.1);
        }
    )");

    // 7. Thiết lập size policy cho các widget
    if (ui->nameEdit) {
        ui->nameEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    }
    if (ui->emailEdit) {
        ui->emailEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    }
    if (ui->passwordEdit) {
        ui->passwordEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    }
    if (ui->confirmPasswordEdit) {
        ui->confirmPasswordEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    }
    if (ui->signupButton) {
        ui->signupButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    }
    if (ui->backButton) {
        ui->backButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    }
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
    if (email.isEmpty() || password.isEmpty() || name.isEmpty()) {
        CustomMessageBox::show("Lỗi", "Vui lòng nhập đầy đủ thông tin");
        return;
    }

    if (password != confirmPassword) {
        CustomMessageBox::show("Lỗi", "Mật khẩu không khớp");
        return;
    }

    if (password.length() < Constants::MIN_PASSWORD_LENGTH) {
        CustomMessageBox::show("Lỗi", "Mật khẩu phải có ít nhất 6 ký tự");
        return;
    }

    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!emailRegex.match(email).hasMatch()) {
        CustomMessageBox::show("Lỗi", "Email không hợp lệ");
        return;
    }

    _authService->signup(email, password, name);
}

void SignupWindow::on_backButton_clicked() {
    emit backToLogin();
    this->close();
}

void SignupWindow::handleSignupSuccess() {
    CustomMessageBox::show("Thành công", "Đăng ký thành công!");
    emit backToLogin();
    this->close();
}

void SignupWindow::handleSignupFailed(const QString& reason) {
    CustomMessageBox::show("Lỗi đăng ký", reason);
}
