/**
 * @file signupwindow.h
 * @brief Cửa sổ đăng ký tài khoản mới cho ứng dụng
 * 
 * Cửa sổ này cung cấp giao diện để:
 * - Nhập thông tin đăng ký tài khoản mới
 * - Xử lý quá trình đăng ký
 * - Hiển thị thông báo kết quả
 * - Điều hướng về màn hình đăng nhập
 */

#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>
#include "authservice.h"
#include "constants.h"

namespace Ui {
class SignupWindow;
}

/**
 * @brief Class quản lý cửa sổ đăng ký tài khoản
 * 
 * Class này cung cấp:
 * - Form nhập thông tin đăng ký
 * - Validation dữ liệu nhập
 * - Xử lý đăng ký thông qua AuthService
 * - Thông báo kết quả đăng ký
 * - Điều hướng giữa các màn hình
 */
class SignupWindow : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructor với AuthService
     * 
     * @param authService Service xử lý xác thực người dùng
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit SignupWindow(QSharedPointer<AuthService> authService, QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~SignupWindow();

signals:
    /**
     * @brief Signal được phát khi người dùng muốn quay lại màn hình đăng nhập
     * 
     * Signal này được kết nối với slot thích hợp trong LoginWindow
     * để thực hiện việc chuyển màn hình
     */
    void backToLogin();

private slots:
    /**
     * @brief Xử lý sự kiện click nút đăng ký
     * 
     * - Validate dữ liệu nhập
     * - Gọi AuthService để đăng ký
     * - Hiển thị thông báo kết quả
     */
    void on_signupButton_clicked();

    /**
     * @brief Xử lý sự kiện click nút quay lại
     * 
     * Phát signal backToLogin để chuyển về màn hình đăng nhập
     */
    void on_backButton_clicked();

    /**
     * @brief Xử lý khi đăng ký thành công
     * 
     * - Hiển thị thông báo thành công
     * - Chuyển về màn hình đăng nhập
     */
    void handleSignupSuccess();

    /**
     * @brief Xử lý khi đăng ký thất bại
     * 
     * @param reason Lý do thất bại
     * 
     * Hiển thị thông báo lỗi với lý do cụ thể
     */
    void handleSignupFailed(const QString& reason);

private:
    Ui::SignupWindow* ui;                    ///< Con trỏ đến giao diện người dùng
    QSharedPointer<AuthService> _authService; ///< Service xử lý xác thực

    /**
     * @brief Thiết lập giao diện người dùng
     * 
     * - Khởi tạo các widget
     * - Thiết lập style
     * - Kết nối signals và slots
     * - Thiết lập validators cho các trường nhập liệu
     */
    void setupUI();
};

#endif // SIGNUPWINDOW_H
