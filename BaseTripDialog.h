/**
 * @file BaseTripDialog.h
 * @brief Dialog cơ sở cho hiển thị danh sách các chuyến đi
 * 
 * Dialog này cung cấp:
 * - Giao diện cơ sở cho việc hiển thị danh sách chuyến đi
 * - Triển khai Template Method Pattern cho các dialog con
 * - Quản lý layout và hiển thị các TripCard
 * - Xử lý các sự kiện resize và hiển thị
 */

#ifndef BASETRIPDIALOG_H
#define BASETRIPDIALOG_H

#include <QDialog>
#include <QScrollArea>
#include <QWidget>
#include <QGridLayout>
#include <QResizeEvent>
#include <QPropertyAnimation>

#include "TripService.h"
#include "BookingService.h"
#include "ReviewService.h"
#include "TripCard.h"

/**
 * @brief Class cơ sở trừu tượng cho các dialog hiển thị danh sách chuyến đi
 * 
 * Class này triển khai Template Method Pattern và cung cấp:
 * - Cấu trúc cơ bản cho việc hiển thị danh sách chuyến đi
 * - Các phương thức trừu tượng để các lớp con tùy chỉnh hành vi
 * - Quản lý layout và hiển thị các TripCard trong grid
 * - Xử lý các sự kiện của dialog
 */
class BaseTripDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor cho BaseTripDialog
     * 
     * @param tripService Service xử lý thông tin chuyến đi
     * @param bookingService Service xử lý đặt chỗ
     * @param reviewService Service xử lý đánh giá
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit BaseTripDialog(QSharedPointer<TripService> tripService,
                            QSharedPointer<BookingService> bookingService,
                            QSharedPointer<ReviewService> reviewService,
                            QWidget *parent = nullptr);

    /**
     * @brief Destructor ảo cho phép kế thừa an toàn
     */
    virtual ~BaseTripDialog() = default;

protected:
    /**
     * @brief Template method khởi tạo dialog
     * 
     * Phương thức này định nghĩa cấu trúc của thuật toán:
     * - Khởi tạo giao diện cơ bản
     * - Thiết lập các thành phần UI bổ sung
     * - Tải danh sách chuyến đi
     * 
     * @note KHÔNG được gọi trong constructor
     */
    void initializeDialog();

    /**
     * @brief Làm mới danh sách chuyến đi
     * 
     * Phương thức này sẽ:
     * - Lấy danh sách chuyến đi mới
     * - Xóa các TripCard cũ
     * - Tạo và hiển thị các TripCard mới
     */
    void refreshTripList();

    /**
     * @brief Lấy tiêu đề cửa sổ
     * @return QString Tiêu đề của dialog
     */
    virtual QString getWindowTitle() const = 0;

    /**
     * @brief Lấy danh sách chuyến đi cần hiển thị
     * @return QList<Trip> Danh sách các chuyến đi
     */
    virtual QList<Trip> getTripsToDisplay() = 0;

    /**
     * @brief Tạo TripCard cho một chuyến đi
     * @param trip Thông tin chuyến đi
     * @return TripCard* Con trỏ đến TripCard mới được tạo
     */
    virtual TripCard* createTripCard(const Trip& trip) = 0;

    /**
     * @brief Hook method được gọi sau khi tạo TripCard
     * @param card Con trỏ đến TripCard vừa được tạo
     * @param trip Thông tin chuyến đi
     */
    virtual void onTripCardCreated(TripCard* card, const Trip& trip) {}

    /**
     * @brief Hook method để thiết lập UI bổ sung
     */
    virtual void setupAdditionalUI() {}

    /**
     * @brief Xử lý sự kiện thay đổi kích thước
     * @param event Con trỏ đến sự kiện resize
     */
    void resizeEvent(QResizeEvent *event) override;

    /**
     * @brief Xử lý sự kiện hiển thị dialog
     * @param event Con trỏ đến sự kiện show
     */
    void showEvent(QShowEvent *event) override;

protected slots:
    /**
     * @brief Slot xử lý khi người dùng click vào nút chi tiết
     * @param tripId ID của chuyến đi được chọn
     */
    void handleDetailsClicked(int tripId);

protected:
    QSharedPointer<TripService> _tripService;      ///< Service xử lý thông tin chuyến đi
    QSharedPointer<BookingService> _bookingService; ///< Service xử lý đặt chỗ
    QSharedPointer<ReviewService> _reviewService;   ///< Service xử lý đánh giá
    QGridLayout* _gridLayout;                       ///< Layout grid để sắp xếp các TripCard
    QScrollArea* _scrollArea;                       ///< Vùng cuộn cho nội dung
    QWidget* _contentWidget;                        ///< Widget chứa nội dung chính

private:
    /**
     * @brief Khởi tạo giao diện người dùng cơ bản
     */
    void initializeUI();

    /**
     * @brief Sắp xếp các TripCard trong grid layout
     */
    void arrangeCardsInGrid();

    bool _initialized;                              ///< Trạng thái khởi tạo của dialog
};

#endif // BASETRIPDIALOG_H
