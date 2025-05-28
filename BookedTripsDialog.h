/**
 * @file BookedTripsDialog.h
 * @brief Dialog hiển thị danh sách các chuyến đi đã đặt
 * 
 * Dialog này cung cấp:
 * - Hiển thị danh sách các chuyến đi người dùng đã đặt
 * - Cho phép xem chi tiết và hủy đặt chỗ
 * - Tự động cập nhật khi có thay đổi trong danh sách đặt chỗ
 */

#ifndef BOOKEDTRIPSDIALOG_H
#define BOOKEDTRIPSDIALOG_H

#include "BaseTripDialog.h"
#include "BookedTripCard.h"
#include "Booking.h"

/**
 * @brief Dialog hiển thị và quản lý các chuyến đi đã đặt của người dùng
 * 
 * Class này kế thừa từ BaseTripDialog và:
 * - Hiển thị danh sách các chuyến đi đã đặt
 * - Cho phép người dùng hủy đặt chỗ
 * - Tự động cập nhật UI khi có thay đổi
 * - Quản lý trạng thái đặt chỗ của người dùng
 */
class BookedTripsDialog : public BaseTripDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor cho BookedTripsDialog
     * 
     * @param tripService Service xử lý thông tin chuyến đi
     * @param bookingService Service xử lý đặt chỗ
     * @param reviewService Service xử lý đánh giá
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit BookedTripsDialog(QSharedPointer<TripService> tripService,
                               QSharedPointer<BookingService> bookingService,
                               QSharedPointer<ReviewService> reviewService,
                               QWidget *parent = nullptr);

protected:
    /**
     * @brief Lấy tiêu đề cho cửa sổ dialog
     * @return QString Tiêu đề của dialog
     */
    QString getWindowTitle() const override;

    /**
     * @brief Lấy danh sách các chuyến đi đã đặt
     * @return QList<Trip> Danh sách các chuyến đi
     */
    QList<Trip> getTripsToDisplay() override;

    /**
     * @brief Tạo card hiển thị cho một chuyến đi đã đặt
     * @param trip Thông tin chuyến đi
     * @return TripCard* Con trỏ đến BookedTripCard mới được tạo
     */
    TripCard* createTripCard(const Trip& trip) override;

    /**
     * @brief Xử lý sau khi tạo TripCard
     * 
     * Hook method này:
     * - Kết nối signals/slots cho việc hủy đặt chỗ
     * - Thiết lập thông tin đặt chỗ cho card
     * 
     * @param card Con trỏ đến TripCard vừa được tạo
     * @param trip Thông tin chuyến đi
     */
    void onTripCardCreated(TripCard* card, const Trip& trip) override;

    /**
     * @brief Thiết lập các thành phần UI bổ sung
     * 
     * Hook method này:
     * - Thêm các widget đặc thù cho dialog đặt chỗ
     * - Thiết lập kết nối để cập nhật tự động
     */
    void setupAdditionalUI() override;

private slots:
    /**
     * @brief Xử lý khi người dùng nhấn nút hủy đặt chỗ
     * @param tripId ID của chuyến đi cần hủy
     */
    void handleCancelClicked(int tripId);

    /**
     * @brief Cập nhật UI khi danh sách đặt chỗ thay đổi
     */
    void onBookingsUpdated();

private:
    /**
     * @brief Tìm thông tin đặt chỗ cho một chuyến đi
     * @param tripId ID của chuyến đi cần tìm
     * @return Booking Thông tin đặt chỗ của chuyến đi
     */
    Booking findBookingForTrip(int tripId) const;

    QList<Booking> _userBookings;    ///< Danh sách các đặt chỗ của người dùng
};

#endif // BOOKEDTRIPSDIALOG_H
