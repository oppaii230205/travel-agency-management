/**
 * @file BookedTripCard.h
 * @brief Card hiển thị thông tin chuyến đi đã đặt
 * 
 * Class này cung cấp:
 * - Giao diện hiển thị cho các chuyến đi đã được đặt
 * - Nút hủy đặt chỗ cho chuyến đi
 * - Kế thừa từ TripCard và bổ sung thông tin đặt chỗ
 */

#ifndef BOOKEDTRIPCARD_H
#define BOOKEDTRIPCARD_H

#include "TripCard.h"
#include "Booking.h"

/**
 * @brief Class hiển thị thông tin chi tiết của một chuyến đi đã đặt
 * 
 * Class này kế thừa từ TripCard và:
 * - Hiển thị thông tin chi tiết của booking
 * - Cung cấp nút để hủy đặt chỗ
 * - Phát signal khi người dùng muốn hủy đặt chỗ
 */
class BookedTripCard : public TripCard
{
    Q_OBJECT

public:
    /**
     * @brief Constructor cho BookedTripCard
     * 
     * @param trip Thông tin chuyến đi
     * @param booking Thông tin đặt chỗ của chuyến đi
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit BookedTripCard(const Trip& trip, const Booking& booking, QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal được phát khi người dùng nhấn nút hủy đặt chỗ
     * @param tripId ID của chuyến đi cần hủy đặt chỗ
     */
    void cancelClicked(int tripId);

private:
    /**
     * @brief Thiết lập nút hủy đặt chỗ
     * 
     * Phương thức này:
     * - Tạo và cấu hình nút hủy
     * - Kết nối signal/slot cho nút
     * - Thêm nút vào layout của card
     */
    void setupCancelButton();

    Booking _booking;    ///< Thông tin đặt chỗ của chuyến đi
};

#endif // BOOKEDTRIPCARD_H
