/**
 * @file loginwindow.h
 * @brief Dialog cung cấp giao diện đăng nhập cho người dùng
 */

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QSharedPointer>
#include "authservice.h"

namespace Ui {
class QDialog;
}

/**
 * @brief Class quản lý cửa sổ đăng nhập
 * 
 * Class này cung cấp giao diện người dùng cho:
 * - Đăng nhập vào hệ thống
 * - Chuyển hướng đến form đăng ký
 * - Xử lý các phản hồi từ AuthService
 */
class LoginWindow : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructor cho LoginWindow
     * 
     * @param authService Con trỏ thông minh đến service xác thực
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit LoginWindow(QSharedPointer<AuthService> authService, QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~LoginWindow();

signals:
    /**
     * @brief Signal được phát khi đăng nhập thành công
     * 
     * Signal này được kết nối với main window để chuyển đến
     * giao diện chính của ứng dụng.
     */
    void loginSuccess();

    /**
     * @brief Signal được phát khi người dùng hủy đăng nhập
     * 
     * Signal này được phát khi:
     * - Người dùng đóng cửa sổ đăng nhập
     * - Người dùng hủy quá trình đăng nhập
     */
    void loginAborted();

private slots:
    /**
     * @brief Xử lý sự kiện click nút đăng nhập
     * 
     * Kiểm tra thông tin đăng nhập và gọi AuthService
     * để xác thực người dùng.
     */
    void on_loginButton_clicked();

    /**
     * @brief Xử lý sự kiện click nút đăng ký
     * 
     * Mở cửa sổ đăng ký tài khoản mới.
     */
    void on_signupButton_clicked();

    /**
     * @brief Xử lý khi đăng nhập thành công
     * 
     * Đóng cửa sổ đăng nhập và phát signal loginSuccess.
     */
    void handleLoginSuccess();

    /**
     * @brief Xử lý khi đăng nhập thất bại
     * 
     * Hiển thị thông báo lỗi cho người dùng.
     * 
     * @param reason Lý do đăng nhập thất bại
     */
    void handleLoginFailed(const QString& reason);

    /**
     * @brief Xử lý khi đăng nhập bị từ chối
     * 
     * Được gọi khi:
     * - Người dùng hủy đăng nhập
     * - Xảy ra lỗi xác thực
     */
    void onLoginRejected();

private:
    Ui::QDialog* ui;                         ///< Con trỏ đến giao diện người dùng
    QSharedPointer<AuthService> _authService; ///< Service xử lý xác thực

    /**
     * @brief Thiết lập giao diện người dùng
     * 
     * Khởi tạo và cấu hình:
     * - Layout và các widget
     * - Kết nối signals và slots
     * - Style và giao diện
     */
    void setupUI();
};

#endif // LOGINWINDOW_H
