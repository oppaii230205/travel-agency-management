/**
 * @file BookingService.h
 * @brief Service xử lý các thao tác đặt chỗ trong hệ thống
 */

#ifndef BOOKINGSERVICE_H
#define BOOKINGSERVICE_H

#include "BookingRepository.h"
#include "TripService.h"
#include "AuthService.h"

#include "Observable.h"
#include "TripBookedEvent.h"

#include <QObject>

/**
 * @brief Class cung cấp các dịch vụ quản lý đặt chỗ
 * 
 * Class này xử lý các thao tác liên quan đến đặt chỗ:
 * - Đặt chỗ cho một chuyến đi
 * - Quản lý danh sách đặt chỗ của người dùng
 * - Hủy đặt chỗ
 * - Thông báo các sự kiện đặt chỗ
 * 
 * Sử dụng mô hình Observer để thông báo các thay đổi về đặt chỗ
 */
class BookingService : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor cho BookingService
     * 
     * @param bookingRepo Repository xử lý dữ liệu đặt chỗ
     * @param tripService Service quản lý thông tin chuyến đi
     * @param authService Service xác thực người dùng
     * @param parent QObject cha (mặc định là nullptr)
     */
    explicit BookingService(QSharedPointer<BookingRepository> bookingRepo,
                            QSharedPointer<TripService> tripService,
                            QSharedPointer<AuthService> authService,
                            QObject* parent = nullptr);

    /**
     * @brief Đặt chỗ cho một chuyến đi
     * @param tripId ID của chuyến đi cần đặt chỗ
     * @return true nếu đặt chỗ thành công, false nếu thất bại
     */
    Q_INVOKABLE bool bookTrip(int tripId);

    /**
     * @brief Lấy danh sách đặt chỗ của người dùng hiện tại
     * @return Danh sách các đặt chỗ của người dùng
     */
    Q_INVOKABLE QList<Booking> getUserBookings() const;

    /**
     * @brief Kiểm tra người dùng đã đặt chỗ cho chuyến đi cụ thể chưa
     * @param tripId ID của chuyến đi cần kiểm tra
     * @return true nếu người dùng đã đặt chỗ, false nếu chưa
     */
    Q_INVOKABLE bool hasUserBooked(int tripId) const;

    /**
     * @brief Hủy đặt chỗ cho một chuyến đi
     * @param tripId ID của chuyến đi cần hủy
     * @return true nếu hủy thành công, false nếu thất bại
     */
    Q_INVOKABLE bool cancelBooking(int tripId);

    /**
     * @brief Đăng ký observer để nhận thông báo về các sự kiện đặt chỗ
     * @param observer Con trỏ đến observer cần đăng ký
     */
    void subscribe(QSharedPointer<IObserver> observer);
    
    /**
     * @brief Hủy đăng ký observer
     * @param observer Con trỏ đến observer cần hủy đăng ký
     */
    void unsubscribe(QSharedPointer<IObserver> observer);

signals:
    /**
     * @brief Signal được phát khi đặt chỗ thành công
     * @param message Thông báo thành công
     */
    void bookingSuccess(const QString& message);

    /**
     * @brief Signal được phát khi đặt chỗ thất bại
     * @param error Thông báo lỗi
     */
    void bookingFailed(const QString& error);

    /**
     * @brief Signal được phát khi danh sách đặt chỗ có thay đổi
     */
    void bookingsUpdated();

private:
    QSharedPointer<Observable> _observable;      ///< Đối tượng quản lý observers
    QSharedPointer<BookingRepository> _bookingRepo; ///< Repository xử lý dữ liệu đặt chỗ
    QSharedPointer<TripService> _tripService;    ///< Service quản lý thông tin chuyến đi
    QSharedPointer<AuthService> _authService;    ///< Service xác thực người dùng
};

#endif // BOOKINGSERVICE_H
