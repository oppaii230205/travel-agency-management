/**
 * @file mainwindow.h
 * @brief Cửa sổ chính của ứng dụng quản lý đại lý du lịch
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TripService.h"
#include "authservice.h"
#include "UserService.h"
#include "BookingService.h"
#include "ReviewService.h"
#include "loginwindow.h"
#include "AzureStorageService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Class quản lý cửa sổ chính của ứng dụng
 * 
 * Class này cung cấp giao diện chính với các chức năng:
 * - Hiển thị và quản lý các chuyến đi
 * - Quản lý đặt chỗ
 * - Quản lý thông tin người dùng
 * - Xử lý đăng xuất
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor cho MainWindow
     * 
     * @param userService Service quản lý người dùng
     * @param authService Service xác thực
     * @param tripService Service quản lý chuyến đi
     * @param bookingService Service quản lý đặt chỗ
     * @param storageService Service lưu trữ
     * @param reviewService Service quản lý đánh giá
     * @param parent Widget cha (mặc định là nullptr)
     */
    MainWindow(QSharedPointer<UserService> userService,
               QSharedPointer<AuthService> authService,
               QSharedPointer<TripService> tripService,
               QSharedPointer<BookingService> bookingService,
               QSharedPointer<AzureStorageService> storageService,
               QSharedPointer<ReviewService> reviewService,
               QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~MainWindow();

public:
    /**
     * @brief Cập nhật giao diện người dùng
     * 
     * Cập nhật hiển thị dựa trên:
     * - Trạng thái đăng nhập
     * - Quyền của người dùng
     * - Dữ liệu mới nhất từ các service
     */
    void updateUI();

private slots:
    /**
     * @brief Xử lý sự kiện click vào nút thêm chuyến đi mới
     */
    void onLabelAddTripClicked();

    /**
     * @brief Xử lý sự kiện click vào nút đăng xuất
     */
    void onLabelLogOutClicked();

    /**
     * @brief Xử lý sự kiện click vào nút xem danh sách chuyến đi
     */
    void onLabelShowTripsClicked();

    /**
     * @brief Xử lý sự kiện click vào nút xem đặt chỗ của tôi
     */
    void onLabelMyBookingsClicked();

    /**
     * @brief Xử lý sự kiện click vào nút xem thông tin người dùng
     */
    void onLabelShowUserInfoClicked();

    /**
     * @brief Xử lý yêu cầu đăng xuất từ người dùng
     */
    void handleLogoutRequest();

    /**
     * @brief Xử lý khi có chuyến đi mới được thêm vào
     * @param newTrip Thông tin chuyến đi mới
     */
    void onTripAdded(const Trip& newTrip);

    /**
     * @brief Xử lý khi có lỗi xảy ra
     * @param message Thông báo lỗi
     */
    void onErrorOccurred(const QString& message);

    /**
     * @brief Xử lý quá trình đăng xuất
     */
    void handleLogout();

signals:
    /**
     * @brief Signal được phát khi đăng xuất hoàn tất
     */
    void logoutCompleted();

protected:
    /**
     * @brief Override phương thức lọc sự kiện
     * 
     * Xử lý các sự kiện mouse hover và click cho các label
     * 
     * @param obj Đối tượng nhận sự kiện
     * @param event Sự kiện cần xử lý
     * @return true nếu sự kiện đã được xử lý, false nếu chưa
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::MainWindow* ui;                         ///< Con trỏ đến giao diện người dùng
    QSharedPointer<AuthService> _authService;   ///< Service xác thực
    QSharedPointer<TripService> _tripService;   ///< Service quản lý chuyến đi
    QSharedPointer<UserService> _userService;   ///< Service quản lý người dùng
    QSharedPointer<BookingService> _bookingService; ///< Service quản lý đặt chỗ
    QSharedPointer<AzureStorageService> _storageService; ///< Service lưu trữ
    QSharedPointer<ReviewService> _reviewService; ///< Service quản lý đánh giá

    /**
     * @brief Thiết lập giao diện người dùng
     * 
     * Khởi tạo và cấu hình:
     * - Layout và các widget
     * - Kết nối signals và slots
     * - Style và giao diện
     * - Event filters
     */
    void setupUI();
};

#endif // MAINWINDOW_H
